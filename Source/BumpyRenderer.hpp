#pragma once

#include "BasicRenderer.hpp"

namespace BARE2D {
	
	/**
	 * @class BumpyGlyph
	 * @brief This is a glyph, but with bumpmap (for lighting etc.)
	 */
	class BumpyGlyph : public Glyph {
	public:
		BumpyGlyph(glm::vec4& destRect, glm::vec4& uvRect, GLuint Texture, GLuint Bumpmap, float Depth, Colour colour);
		
		// Bumpmap texture handle
		GLuint bumpmap;
	}
	
	/**
	 * @class BumpyRenderer
	 * @brief This is a BasicRenderer, but it includes the usage of bumpmaps. This can be useful for lighting.
	 */
	class BumpyRenderer : public BasicRenderer
	{
	public:
		BumpyRenderer(std::string& fragShader, std::string& vertShader, unsigned int perspectiveWidth = 2, unsigned int perspectiveHeight = 2);
		~BumpyRenderer();
		
		virtual void preRender() override;
		
		virtual void render() override;
		
		// We need to delete this function, as it is no longer valid - we require a bumpmap.
		virtual void draw(glm::vec4 destRect, glm::vec4 uvRect, GLuint texture, float depth, Colour colour = Colour(255, 255, 255, 255)) = 0;
		virtual void draw(glm::vec4 destRect, glm::vec4 uvRect, GLuint texture, GLuint bumpmap, float depth, Colour colour = Colour(255, 255, 255, 255));
		
	protected:
		virtual void createRenderBatches() override;
		
		// The bumpmaps that correspond to each render batch.
		std::vector<GLuint> m_batchBumpmaps;

	};

}

