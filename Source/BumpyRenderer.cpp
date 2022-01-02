#include "BumpyRenderer.hpp"

#include "GLContextManager.hpp"

namespace BARE2D {
	
	BumpyGlyph::BumpyGlyph(glm::vec4& destRect, glm::vec4& uvRect, GLuint& Texture, GLuint& Bumpmap, float& Depth, Colour& colour, float& angle, glm::vec2& COR)
		: Glyph(destRect, uvRect, Texture, Depth, colour, angle, COR), bumpmap(Bumpmap) {
		
	}

	BumpyRenderer::BumpyRenderer(std::string& fragShader, std::string& vertShader, unsigned int perspectiveWidth, unsigned int perspectiveHeight)
		: BasicRenderer(fragShader, vertShader, perspectiveWidth, perspectiveHeight) {
	}

	BumpyRenderer::~BumpyRenderer()
	{
	}
	
	void BumpyRenderer::initUniforms() {
		GLint textureUniform = 0;
		m_shader.setUniform("textureSampler", &textureUniform);
		
		GLint bumpUniform = 1;
		m_shader.setUniform("bumpmapSampler", &bumpUniform);
	}

	void BumpyRenderer::preRender()
	{
		// We need to define a texture sampler for textures AND bumpmaps!
		m_camera->update();
		
		glm::mat4 projectionMatrix = m_camera->getCameraMatrix();
		m_shader.setUniformMatrix<glm::mat4>("projectionMatrix", GL_FALSE, &projectionMatrix);
	}
	
	void BumpyRenderer::render() {
		// Ensure that we're actually using the shader for the glDrawArrays call!
		m_shader.use();
		
		// Make sure we're in the regular rendering texture (arbitrarily set to texture0, just for consistency)
		GLContext* glContext = GLContextManager::getContext();
		glContext->setActiveTexture(GL_TEXTURE0);
		
		// First we must bind the vertex array object and vertex buffer object
		m_vertexArrayObject.bind();
		
		preRender();
		
		// Create RenderBatches (uploading them to the bound texture, so that we can actually draw them next.
		createRenderBatches();
		
		// Now we can render each renderbatch, uploading their texture data respectively.
		for(unsigned int i = 0; i < m_batches.size(); i++) {
			// Bind the texture information to the texture "slot" 
			// This method of binding the textures decreases speed slightly for completely random textures, but if we are rendering a lot of the same texture, this is similar (if not identical) to instance rendering.
			
			glContext->setActiveTexture(GL_TEXTURE1);
			glContext->bindTexture(GL_TEXTURE_2D, m_batchBumpmaps[i]);
			
			glContext->setActiveTexture(GL_TEXTURE0);
			glContext->bindTexture(GL_TEXTURE_2D, m_batches[i].textureID);
			
			// Upload the data
			glDrawArrays(GL_TRIANGLES, (GLint)m_batches[i].offset, (GLsizei)m_batches[i].numVertices);
		}
		
		// Unbind for safety!
		m_vertexArrayObject.unbind();
		
		// Release the shader
		m_shader.unuse();
	}

	void BumpyRenderer::draw(glm::vec4 destRect, glm::vec4 uvRect, GLuint texture, float depth, Colour colour/* = Colour(255, 255, 255, 255)*/, float angle/* = 0.0f*/, glm::vec2 COR/* = glm::vec2(0.5f)*/) {
		throwFatalError(BAREError::UNINITIALIZED_FUNCTION, "BumpyRenderer drawing without bumpmap texture! Fix your program!");
	}

	void BumpyRenderer::draw(glm::vec4 destRect, glm::vec4 uvRect, GLuint texture, GLuint bumpmap, float depth, Colour colour/* = Colour(255, 255, 255, 255)*/, float angle/* = 0.0f*/, glm::vec2 COR/* = glm::vec2(0.5f)*/)
	{
		// Make sure it's actually in the scene.
		if(!m_camera->isRectInScene(destRect))
			return;
		
		// Just add the glyph (as a bumpy glyph!)
		m_glyphs.push_back(new BumpyGlyph(destRect, uvRect, texture, bumpmap, depth, colour, angle, COR));
	}
	
	void BumpyRenderer::createRenderBatches() {
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
		
		// Make way for new bumpmaps.
		m_batchBumpmaps.clear();
		
		// 'Draw' two triangles from the 6 vertices. 
		m_batches.emplace_back(offset, 6, m_glyphs[0]->texture);
		vertices[vertex++] = m_glyphs[0]->topLeft;
		vertices[vertex++] = m_glyphs[0]->bottomLeft;
		vertices[vertex++] = m_glyphs[0]->bottomRight;
		vertices[vertex++] = m_glyphs[0]->bottomRight;
		vertices[vertex++] = m_glyphs[0]->topRight;
		vertices[vertex++] = m_glyphs[0]->topLeft;
		m_batchBumpmaps.push_back(static_cast<BumpyGlyph*>(m_glyphs[0])->bumpmap);
		
		// Set the offset appropriately for 6 vertices of data.
		offset += 6;
		
		// Add the rest of the glyphs
		for(unsigned int glyph = 1; glyph < m_glyphs.size(); glyph++) {
			// Check if this can just be part of the current batch (instancing essentially)
			// They must have both the same texture AND the same bumpmap for this to work properly.
			if((m_glyphs[glyph]->texture != m_glyphs[glyph - 1]->texture) || (static_cast<BumpyGlyph*>(m_glyphs[glyph])->bumpmap != static_cast<BumpyGlyph*>(m_glyphs[glyph - 1])->bumpmap)) {
				// It can't be part of the same batch, so create a new one
				m_batches.emplace_back(offset, 6, m_glyphs[glyph]->texture);
				// Add the corresponding bumpmap to the batch bumpmaps vector.
				m_batchBumpmaps.push_back(static_cast<BumpyGlyph*>(m_glyphs[glyph])->bumpmap);
			} else {
				// If its part of the current batch, just increase numVertices. It'll reuse the texture, but nothing more.
				m_batches.back().numVertices += 6;
			}
			// 'Draw' two triangles.
			vertices[vertex++] = m_glyphs[glyph]->topLeft;
			vertices[vertex++] = m_glyphs[glyph]->bottomLeft;
			vertices[vertex++] = m_glyphs[glyph]->bottomRight;
			vertices[vertex++] = m_glyphs[glyph]->bottomRight;
			vertices[vertex++] = m_glyphs[glyph]->topRight;
			vertices[vertex++] = m_glyphs[glyph]->topLeft;
			
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
