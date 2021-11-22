#pragma once

#include "Font.hpp"
#include "BasicRenderer.hpp"

namespace BARE2D {
	
	/**
	 * @class Justification
	 * @brief An enum for text justification
	 */
	enum class Justification {
		RIGHT,
		MIDDLE,
		LEFT
	};
	
	/**
	 * @class FontRenderer
	 * @brief The FontRenderer... renders fonts. It is just a very basic extension of the BasicRenderer, so it works the same.
	 */
	class FontRenderer : public BasicRenderer
	{
	public:
		FontRenderer(std::string& fragShader, std::string& vertShader);
		~FontRenderer();
		
		virtual void draw(Font& font, glm::vec2 scaling, glm::vec4 destRect, const char* text, float depth, Colour tint, Justification just = Justification::LEFT, glm::vec4 uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		
	};

}
