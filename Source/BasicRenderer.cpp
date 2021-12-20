#include "BasicRenderer.hpp"

namespace BARE2D {

	BasicRenderer::BasicRenderer(std::string& fragShader, std::string& vertShader, unsigned int perspectiveWidth, unsigned int perspectiveHeight) : Renderer(), m_fragShader(fragShader), m_vertShader(vertShader)
	{
		m_camera = std::make_shared<Camera2D>();
		m_camera->init(perspectiveWidth, perspectiveHeight);
	}

	BasicRenderer::~BasicRenderer()
	{
	}
	
	void BasicRenderer::init() {
		m_shader.compileShaders(m_vertShader.c_str(), m_fragShader.c_str());
		
		m_shader.linkShaders({"vertexPosition", "vertexColour", "vertexUV"});
		
		Renderer::init(); // Initializes the VAO, so we can add attributes.
		
		m_vertexArrayObject.addVertexAttribute(3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		m_vertexArrayObject.addVertexAttribute(4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));
		m_vertexArrayObject.addVertexAttribute(2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	}
	
	void BasicRenderer::setCamera(std::shared_ptr<Camera2D> camera) {
		m_camera = camera;
	}
	
	std::shared_ptr<Camera2D> BasicRenderer::getCamera() {
		return m_camera;
	}
	
	void BasicRenderer::preRender() {
		// We also need to define a texture sampler for textures!
		
		m_camera->update();
		
		GLint textureUniform = 0;
		m_shader.setUniform("textureSampler", textureUniform);
		glm::mat4 projectionMatrix = m_camera->getCameraMatrix();
		m_shader.setUniformMatrix<glm::mat4>("projectionMatrix", GL_FALSE, projectionMatrix);
	}
	
	void BasicRenderer::draw(glm::vec4 destRect, glm::vec4 uvRect, GLuint texture, float depth) {
		// Make sure it's actually in the scene.
		if(!m_camera->isRectInScene(destRect))
			return;
		
		// At this point we can just scale the size (the position should be translated in the shader) and draw it
		glm::vec2 size = m_camera->getScreenSizeFromViewedSize(glm::vec2(destRect.z, destRect.w));
		
		// Just add the glyph
		m_glyphs.emplace_back(destRect, uvRect, texture, depth, Colour(255, 255, 255, 255));
	}
	
	void BasicRenderer::draw(glm::vec4 destRect, glm::vec4 uvRect, GLuint texture, float depth, Colour colour) {
		// Make sure it's actually in the scene.
		if(!m_camera->isRectInScene(destRect))
			return;
		
		// At this point we can just scale the size (the position should be translated in the shader) and draw it
		glm::vec2 size = m_camera->getScreenSizeFromViewedSize(glm::vec2(destRect.z, destRect.w));
		
		// Just add the glyph
		m_glyphs.emplace_back(destRect, uvRect, texture, depth, colour);
	}
	
	void BasicRenderer::createRenderBatches() {
		// Create all the render batches (based on the draw()'n glyphs) for rendering
		// THey're going to end up as vertices
		std::vector<Vertex> vertices;
		
		// We already know that the glyphs represent 6 vertices by design.
		vertices.resize(m_glyphs.size() * 6);
		
		// Check if we even have anything to draw
		if(m_glyphs.size() == 0) {
			return; // Don't need to do much.
		}
		
		int offset = 0;
		int vertex = 0;
		
		// 'Draw' two triangles from the 6 vertices. 
		m_batches.emplace_back(offset, 6, m_glyphs[0].texture);
		vertices[vertex++] = m_glyphs[0].topLeft;
		vertices[vertex++] = m_glyphs[0].bottomLeft;
		vertices[vertex++] = m_glyphs[0].bottomRight;
		vertices[vertex++] = m_glyphs[0].bottomRight;
		vertices[vertex++] = m_glyphs[0].topRight;
		vertices[vertex++] = m_glyphs[0].topLeft;
		
		// Set the offset appropriately for 6 vertices of data.
		offset += 6;
		
		// Add the rest of the glyphs
		for(unsigned int glyph = 1; glyph < m_glyphs.size(); glyph++) {
			// Check if this can just be part of the current batch (instancing essentially)
			if(m_glyphs[glyph].texture != m_glyphs[glyph - 1].texture) {
				// It can't be part of the same batch, so create a new one
				m_batches.emplace_back(offset, 6, m_glyphs[glyph].texture);
			} else {
				// If its part of the current batch, just increase numVertices. It'll reuse the texture, but nothing more.
				m_batches.back().numVertices += 6;
			}
			// 'Draw' two triangles.
			vertices[vertex++] = m_glyphs[glyph].topLeft;
			vertices[vertex++] = m_glyphs[glyph].bottomLeft;
			vertices[vertex++] = m_glyphs[glyph].bottomRight;
			vertices[vertex++] = m_glyphs[glyph].bottomRight;
			vertices[vertex++] = m_glyphs[glyph].topRight;
			vertices[vertex++] = m_glyphs[glyph].topLeft;
			
			// Push data offset forward 6 vertices.
			offset += 6;
		}
		
		// Done with the glyphs, we can clear em
		m_glyphs.clear();
		
		// Now that render batches are created, we can upload the information to OpenGL
		
		// Bind the VBO
		m_vertexArrayObject.bindVBO();
		
		// Orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		
		// Actually upload the data to the buffer.
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		
		// Unbind the VBO again for safety
		m_vertexArrayObject.unbindVBO();
	}

}

