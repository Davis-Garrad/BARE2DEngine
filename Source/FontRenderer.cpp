#include "FontRenderer.hpp"

namespace BARE2D {

	FontRenderer::FontRenderer(std::string& fragShader, std::string& vertShader, unsigned int perspectiveWidth, unsigned int perspectiveHeight) : BasicRenderer(fragShader, vertShader, perspectiveWidth, perspectiveHeight)
	{
	}

	FontRenderer::~FontRenderer()
	{
	}

	void FontRenderer::draw(Font& font, glm::vec2 scaling, glm::vec4 destRect, const char* text, float depth, Colour tint, Justification just /**= Justification::LEFT*/, glm::vec4 uvRect /**= glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)*/) {
		// Apply the justification setting
		glm::vec2 newPosition = destRect;
		if(just == Justification::MIDDLE) {
			newPosition -= font.measure(text).x * scaling.x / 2.0f;
		} else if(just == Justification::RIGHT) {
			newPosition += font.measure(text).x * scaling.x;
		}
		
		// Map out the individual glyphs and add em to the renderer.
		for(int characterIndex = 0; text[characterIndex] != 0; characterIndex++) {
			char c = text[characterIndex];
			// First, check on a character-by-character basis where this character should be
			if(c == '\n') {
				// New line, set the position one line down
				newPosition.y += font.getHeight() * scaling.y;
				// We should also set back to the first space.
				newPosition.x = destRect.x;
			} else {
				// Check to make sure we have the glyph in the font
				int glyphIndex = c - FIRST_PRINTABLE_CHAR;
				if(glyphIndex < 0 || glyphIndex > font.getCharacters()) {
					// We don't support this character, set the index to the "unsupported" glyph
					glyphIndex = font.getCharacters();
				}
				
				// Get the actual glyph for data!
				CharacterGlyph* glyph = font.getGlyph(glyphIndex);
				
				// initialize the glyph's placement
				glm::vec4 destRect(newPosition, glyph->size * scaling);
				glm::vec4 uvRectFinal(glyph->uvRect.x + uvRect.x * glyph->uvRect.z, 
									  glyph->uvRect.y + uvRect.y * glyph->uvRect.w,
									  glyph->uvRect.z * uvRect.z,
									  glyph->uvRect.w * uvRect.w);
				
				// Actually draw the texture!
				BasicRenderer::draw(destRect, uvRectFinal, font.getTextureID(), depth);
				
				// Move the 'cursor' over to the next character slot
				newPosition.x += glyph->size.x * scaling.x;
			}
		}
	}

}

