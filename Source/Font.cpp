#include "Font.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "BAREErrors.hpp"
#include "GLContextManager.hpp"

int closestPow2(int i)
{
    // Do some wacky shit to find the closest power of 2 to `i`
    i--;
    int pi = 1;
    while(i > 0)
	{
	    i >>= 1;
	    pi <<= 1;
	}
    return pi;
}

namespace BARE2D {

Font::Font()
{}

Font::~Font()
{}

void Font::init(const char* fontFile, int size)
{
    // Initialize some font.
    // Make sure that we initialize the TTF extension of SDL
    if(!TTF_WasInit())
	{
	    TTF_Init();
    }

    // Now that we know for sure we can make a font!
    TTF_Font* font = TTF_OpenFont(fontFile, size);

    // Check to make sure it was loaded properly
    if(font == nullptr)
	{
	    throwFatalError(BAREError::FONT_FAILURE, "Failed to load font " + std::string(fontFile));
    }

    // Initialize some member variables.
    m_height = TTF_FontHeight(font);

    m_regStart = FIRST_PRINTABLE_CHAR;
    m_regLength = LAST_PRINTABLE_CHAR - FIRST_PRINTABLE_CHAR + 1;

    // Set the padding variable between letters.
    int padding = size / 8;

    // Measure all glyphs separately
    // To hold all glyph metrics given by TTF_GlyphMetrics
    glm::ivec4* glyphRectangles = new glm::ivec4[m_regLength];
    // Some incremental variables.
    int i = 0;

    // Loop through every character
    for(char c = m_regStart; (unsigned int)c < m_regStart + m_regLength; c++)
	{
	    // Get the metrics for the character
	    const char str[2] = {c, '\0'};

	    // Gets the size of a piece of text with the font, with a null-terminated c_str.
	    TTF_SizeText(font, str, &glyphRectangles[i].z, &glyphRectangles[i].w);
	    i++;
	}

    unsigned int bestWidth = 0, bestHeight = 0, bestRows = 0;
    std::vector<int>* bestPartition = nullptr;

    {
	// Now that we have the sizes of all the glyphs, figure out which is the best partitioning sequence
	// Various variables for optimization
	unsigned int rows = 1;
	int width, height, area = MAX_TEXTURE_RES * MAX_TEXTURE_RES;
	// Gradually try more and more rows until we reach optimal partitioning
	while(rows <= m_regLength)
	    {
		// Set the height of the texture
		height = rows * (padding + m_height) + padding;

		// Create a partition using the createRows function to determine if it's good!
		// Also, record the minimum texture width we need (the maximum character width)
		std::vector<int>* trialPartition = createRows(glyphRectangles, m_regLength, rows, padding, width);

		// Set width and height of final texture to the next highest power of two. OpenGL is going to do this
		// anyways in memory so its equivalent for optimization
		width = closestPow2(width);
		height = closestPow2(height);

		// First check if the texture breaks our restrictions
		if(width > MAX_TEXTURE_RES || height > MAX_TEXTURE_RES)
		    {
			// Obviously this is not going to work. Try again with one more row.
			rows++;
			delete[] trialPartition;
			continue;
		}

		// We are within our restrictions, now check if it's optimal. We want the least area (data) that we can
		// possibly accomodate all the letters with.
		if(area >= width * height)
		    {
			// This trial's area is smaller than our current best - that's good!
			// Get rid of the old best
			if(bestPartition)
			    delete[] bestPartition;

			// Set the best to this one
			bestPartition = trialPartition;
			bestWidth = width;
			bestHeight = height;
			bestRows = rows;
			area = bestWidth * bestHeight;

			// Now keep searching for a better one!
			rows++;
		} else
		    {
			// This trial is discarded as we already know of a better one.
			delete[] trialPartition;

			// We can actually just break out of the loop if our optimization yields a worse result than the
			// last feasible.
			break;
		    }
	    }

	// Now we know how our glyphs should be arranged in the texture, so let's do that.

	// First, check if a font can be made at all
	if(!bestPartition)
	    {
		// We never actually found a feasible font arrangement
		throwFatalError(BAREError::FONT_FAILURE, "Failed to create font texture. Try a lower resolution.");
	}
    }

    // Create the actual texture.
    glGenTextures(1, &m_textureID);
    GLContextManager::getContext()->bindTexture(GL_TEXTURE_2D, m_textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bestWidth, bestHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, nullptr);

    // Now just draw all the individual glyphs onto that texture!
    // For convenience
    SDL_Color foreground = {255, 255, 255, 255};

    // The y offset sustains throughout all loops
    int yOff = padding;
    // Loop through every column in every row
    for(unsigned int row = 0; row < bestRows; row++)
	{
	    // The x offset should reset for each row
	    int xOff = padding;
	    for(unsigned int column = 0; column < bestPartition[row].size(); column++)
		{
		    // The integer in the partition corresponds with a certain glyph ID
		    int glyph = bestPartition[row][column];

		    // Get what SDL gives us for the actual rendering surface
		    SDL_Surface* glyphSurface =
		        TTF_RenderGlyph_Blended(font, (unsigned int)(FIRST_PRINTABLE_CHAR + glyph), foreground);

		    // Now set some arduously-researched values
		    // The width is pitch / sizeof(unsigned int), as glyphSurface->w is NOT the width of the pixels
		    // memory block. Instead, pitch is defined as the size of a row in the block. Therefore, divide by
		    // the size of the type.
		    unsigned int glyph_width = glyphSurface->pitch / sizeof(unsigned int);
		    // The height is for some reason true. Ask the SDL2 devs.
		    unsigned int glyph_height = glyphSurface->h;

		    unsigned char* pixel_data = (unsigned char*)glyphSurface->pixels;
		    // Number of pixels, times 4 for RGBA
		    // The memory buffer size is actually pitch*height, not
		    unsigned int num_pixel_data = glyph_width * glyph_height;
		    // Pre-multiplication. This just takes the alpha, and multiplies it in and grayscales.
		    for(unsigned int i = 0; i < num_pixel_data; i += 4)
			{
			    float alpha = pixel_data[i + 3] / 255.0f;
			    // Calculate the grayscale intensity
			    float gray = (unsigned char)((float)pixel_data[i] * alpha);

			    pixel_data[i] = gray;
			    pixel_data[i + 1] = gray;
			    pixel_data[i + 2] = gray;
			}

		    // Upload to the texture
		    glTexSubImage2D(GL_TEXTURE_2D, 0, xOff, bestHeight - yOff - 1 - glyphSurface->h, glyph_width,
		                    glyph_height, GL_BGRA, GL_UNSIGNED_BYTE, pixel_data);

		    // Update coordinates to what they are in the texture
		    glyphRectangles[glyph].x = xOff;
		    glyphRectangles[glyph].y = yOff;
		    glyphRectangles[glyph].z = glyphSurface->w;
		    glyphRectangles[glyph].w = glyphSurface->h;

		    // Free the memory!
		    SDL_FreeSurface(glyphSurface);
		    glyphSurface = nullptr;

		    xOff += glyphRectangles[glyph].z + padding;
		}
	    yOff += m_height + padding;
	}

    // Add in an "unsupported" glyph to symbolize any OOB characters
    int zero_index = padding - 1;
    int* pureWhiteSquare = new int[zero_index * zero_index];

    // Actually set the memory of the first character's spot
    memset(pureWhiteSquare, 0xffffffff, zero_index * zero_index * sizeof(int));

    // Upload to the texture
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, zero_index, zero_index, GL_RGBA, GL_UNSIGNED_BYTE, pureWhiteSquare);

    // Free the memory we just sent to OpenGL
    delete[] pureWhiteSquare;
    pureWhiteSquare = nullptr;

    // Set the texture's basic parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Create character glyphs for the font renderer.
    m_characterGlyphs = new CharacterGlyph[m_regLength + 1];  // all characters + unsupported character

    for(unsigned int i = 0; (unsigned int)i < m_regLength; i++)
	{
	    // Set every glyph's basic characteristics
	    m_characterGlyphs[i].character = (char)((FIRST_PRINTABLE_CHAR) + i);
	    m_characterGlyphs[i].size = glm::vec2(glyphRectangles[i].z, glyphRectangles[i].w);
	    m_characterGlyphs[i].uvRect = glm::vec4(
	        (float)glyphRectangles[i].x / (float)bestWidth, (float)glyphRectangles[i].y / (float)bestHeight,
	        (float)glyphRectangles[i].z / (float)bestWidth, (float)glyphRectangles[i].w / (float)bestHeight);
	}

    // Set the very end one, the unsupported one
    m_characterGlyphs[m_regLength].character = ' ';
    m_characterGlyphs[m_regLength].size = m_characterGlyphs[0].size;
    m_characterGlyphs[m_regLength].uvRect =
        glm::vec4(0.0f, 0.0f, (float)zero_index / (float)bestWidth, (float)zero_index / (float)bestHeight);

    // Now clean up! Unbind the texture
    GLContextManager::getContext()->bindTexture(GL_TEXTURE_2D, 0);
    // free memory
    delete[] glyphRectangles;
    delete[] bestPartition;
    // Tell SDL we're done here.
    TTF_CloseFont(font);
}

void Font::dispose()
{
    // Destroy all necessary stuff lol
    // Free texture
    if(m_textureID != 0)
	{
	    glDeleteTextures(1, &m_textureID);
	    m_textureID = 0;
    }
    if(m_characterGlyphs != nullptr)
	{
	    delete[] m_characterGlyphs;
	    m_characterGlyphs = nullptr;
    }
}

glm::vec2 Font::measure(const char* s)
{
    // Measure the text if it were being drawn with this font
    // It is fixed height, so we just need to calculate the x value of the size, plus any newlines that contribute to
    // height
    glm::vec2 size(0, m_height);

    float columnWidth = 0.0f;

    // Loop through every character in the given text
    for(int charIndex = 0; s[charIndex] != 0; charIndex++)
	{
	    char c = s[charIndex];
	    if(c == '\n')
		{
		    // We were given a new line, add to the height and (possibly) set the width of the whole text
		    size.y += m_height;
		    if(size.x < columnWidth)
			{
			    size.x = columnWidth;
		    }

		    // Reset the column width for a new column
		    columnWidth = 0;
	    } else
		{
		    // Check to make sure we actually have this glyph
		    unsigned int glyphIndex = c - m_regStart;
		    if(glyphIndex < 0 || glyphIndex >= m_regLength)
			{
			    // We don't actually have that character in the font, just add the width of the unknown
			    // characer
			    glyphIndex = m_regLength;
		    }
		    columnWidth += m_characterGlyphs[glyphIndex].size.x;
		}
	}

    // One last time, just make sure that our column width is right
    if(size.x < columnWidth)
	size.x = columnWidth;

    return size;
}

std::vector<int>* Font::createRows(glm::ivec4* rectangles, int rectanglesLength, int rows, int padding, int& width)
{
    // Create the returning vector
    std::vector<int>* ret = new std::vector<int>[rows]();

    // initialize some column widths. Initially, just the padding. Adding glyphs adds width obviously
    int* columnWidths = new int[rows]();
    // Set initial values.
    for(int i = 0; i < rows; i++)
	{
	    columnWidths[i] = padding;
	}

    // Loop through every glyph, adding them as necessary
    for(int i = 0; i < rectanglesLength; i++)
	{
	    // Find what row this should be in (the thinnest)
	    int rowIndex = 0;
	    for(int rowIndexTest = 0; rowIndexTest < rows; rowIndexTest++)
		{
		    // Test each row index, search for least wide
		    if(columnWidths[rowIndexTest] < columnWidths[rowIndex])
			rowIndex = rowIndexTest;
		}

	    // Add this glyph to that row (just add its width, and the other side of the padding)
	    columnWidths[rowIndex] += rectangles[i].z + padding;

	    // Actually add the index of the glyph added, for future reference
	    ret[rowIndex].push_back(i);
	}

    // Record the max width, which is put into `width`
    width = 0;
    for(int i = 0; i < rows; i++)
	{
	    if(columnWidths[i] > width)
		width = columnWidths[i];
	}

    delete[] columnWidths;

    return ret;
}

}  // namespace BARE2D
