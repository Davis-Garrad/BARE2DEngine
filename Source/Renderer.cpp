#include "Renderer.hpp"

#include "GLContextManager.hpp"

namespace BARE2D {

	Renderer::Renderer() {
	}

	Renderer::~Renderer() {
	}

	void Renderer::begin() {
		// Clears renderbatches to make space for new ones!
		m_batches.clear();

		m_shader.use();
	}

	void Renderer::end() {
		// Nothing special really needs to be done here.
		m_shader.unuse();
	}

	void Renderer::init() {
		// Set depth range so that we can actually write depth values.
		glDepthRange(0.0f, 1.0f);

		m_vertexArrayObject.init();

		// We must have an activated shader to find/set uniforms in it.
		m_shader.use();

		// Set the uniforms (in)
		initUniforms();

		m_shader.unuse();
	}

	void Renderer::initUniforms() {
	}

	void Renderer::destroy() {
		m_vertexArrayObject.destroy();
		m_shader.destroy();
	}

	void Renderer::render() {
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
			// This method of binding the textures decreases speed slightly for completely random textures, but if we are rendering a lot of the same texture, this is similar (if not identical) to instance rendering
			glContext->bindTexture(GL_TEXTURE_2D, m_batches[i].textureID);

			// Upload the data
			glDrawArrays(GL_TRIANGLES, (GLint)m_batches[i].offset, (GLsizei)m_batches[i].numVertices);
		}

		// Unbind for safety!
		m_vertexArrayObject.unbind();

		// Release the shader
		m_shader.unuse();
	}

	ShaderProgram* Renderer::getShader() {
		return &m_shader;
	}

	void Renderer::link(std::initializer_list<std::string> attributes) {
		// Set the locations of all possible output variables (all the colour attachments)
		// This must be done before linking!!!
		GLint maxDrawBuffers = 0;
		glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxDrawBuffers);
		for(int i = 0; i < maxDrawBuffers; i++) {
			m_shader.bindFragOutputLocation("colour" + std::to_string(i), i);
		}

		// Now actually link the shader.
		m_shader.linkShaders(attributes);
	}

} // namespace BARE2D
