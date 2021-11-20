#pragma once

#include <glm/glm.hpp>

#include "Renderer.hpp"
#include "Vertex.hpp"

namespace BARE2D {
	/**
	 * @class Glyph
	 * @brief The glyph represents a renderbatch's primitive data, which is created from each draw call in the basic renderer.
	 */
	class Glyph {
	public:
		Glyph(glm::vec4& destRect, glm::vec4& uvRect, GLuint Texture, float Depth, Colour colour);
		
		// Texture handle from opengl
		GLuint texture;
		// Depth for depth-culling.
		float depth;
		
		// Vertices prettty much just hold vertex data together. Useful in creating render batches
		Vertex topLeft, bottomLeft, topRight, bottomRight;
	};
	
	class BasicRenderer : public Renderer
	{
	public:
		BasicRenderer(std::string& fragShader, std::string& vertShader);
		~BasicRenderer();
		
		virtual void init() override;
		virtual void begin() override;
		
		virtual void draw(glm::vec4 destRect, glm::vec4 uvRect, GLuint texture, float depth);
	
	protected:
		virtual void createRenderBatches() override;
		
		std::string m_fragShader, m_vertShader;
		
		std::vector<Glyph> m_glyphs;
	};

}
