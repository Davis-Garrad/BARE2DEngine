#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <vector>

#define FIRST_PRINTABLE_CHAR ((char)32)
#define LAST_PRINTABLE_CHAR ((char)126)
#define MAX_TEXTURE_RES 4096

namespace BARE2D {

	/**
	 * @class CharacterGlyph
	 * @brief Represents a render glyph, modified for fonts!
	 */
	struct CharacterGlyph {
		char character;
		glm::vec4 uvRect;
		glm::vec2 size;
	};

	/**
	 * @class Font
	 * @brief Essentially just a wrapper for the SDL TTF_Font type.
	 */
	class Font
	{
	public:
		Font();
		~Font();

		/**
		 * @brief Creates font resources
		 * @param fontFile The file to load the font from. Should be .ttf
		 * @param size The size of the font (in points)
		 */
		void init(const char* fontFile, int size);
		
		/**
		 * @brief Destroys font resources
		 */
		void dispose();
		
		unsigned int getHeight() const {
			return m_height;
		}
		
		/**
		 * @brief Gets a character glyph. Does no checking to make sure it exists!
		 * @param index The index of the glyph
		 * @return A pointer to the glyph.
		 */
		CharacterGlyph* getGlyph(int& index) {
			return &(m_characterGlyphs[index]);
		}
		
		/**
		 * @return The GL-provided texture ID 
		 */
		GLuint getTextureID() const {
			return m_textureID;
		}
		
		/**
		 * @return The number of characters in the font. Generally LAST_PRINTABLE_CHAR - FIRST_PRINTABLE_CHAR 
		 */
		unsigned int getCharacters() const {
			return m_regLength;
		}
		
		/**
		 * @brief Measures the dimensions of some given text
		 * @param s The text to be measured
		 * @return The dimensions of the text
		 */
		glm::vec2 measure(const char* s);
		
	private:
		static std::vector<int>* createRows(glm::ivec4* rectangles, int rectanglesLength, int rows, int padding, int& width);
	
		// The texture which holds the font graphics
		GLuint m_textureID = 0;
		
		// The height of the font
		unsigned int m_height;
		
		// The start and length values of the possible characters displayed
		unsigned int m_regStart, m_regLength;
		
		// The rendering glyphs (for ease of use in the FontRenderer)
		CharacterGlyph* m_characterGlyphs = nullptr;
	};

}
