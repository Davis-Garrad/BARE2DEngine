#include "FBORenderer.hpp"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "GLContextManager.hpp"

#include "Vertex.hpp"
#include "BAREErrors.hpp"

namespace BARE2D {

	FBORenderer::FBORenderer(std::string& fragShader, std::string& vertShader, unsigned int windowWidth, unsigned int windowHeight, glm::vec2 size) : m_fragmentShaderPath(fragShader),
																								m_vertexShaderPath(vertShader), m_size(size)
	{
		m_camera = new Camera2D();
		m_camera->init(windowWidth, windowHeight);
		m_camera->offsetPosition(glm::vec2(-1.0f, -1.0f));
	}

	FBORenderer::~FBORenderer()
	{
	}
	
	Camera2D* FBORenderer::getCamera() {
		return m_camera;
	}

	void FBORenderer::init()
	{
		// Actually initialize our shader
		m_shader.compileShaders(m_vertexShaderPath.c_str(), m_fragmentShaderPath.c_str());
		
		m_shader.linkShaders({"vertexPosition", "vertexColour", "vertexUV"});
		
		Renderer::init(); // Initializes the VAO, so we can add attributes
		
		m_vertexArrayObject.addVertexAttribute(3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		m_vertexArrayObject.addVertexAttribute(4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));
		m_vertexArrayObject.addVertexAttribute(2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
		
		// Create the actual textures and FBO
		createFBO();
		
		m_shader.use();
		
		// Now, for convenience, set the uniforms of the FBO shader program
		GLint colourTexture = 0, depthTexture = 1;
		m_shader.setUniform("colourTexture", colourTexture);
		
		m_shaderHasDepth = m_shader.doesUniformExist("depthTexture");
		if(m_shaderHasDepth) {
			m_shader.setUniform("depthTexture", depthTexture);
		}
		
		m_shader.unuse();
		
		bind();
		
		// This call specifies which buffers should be drawn to - in our case, it's just the colour attachment for the FBO
		// This essentially means that the output from the fragment shader goes directly into the FBO's attached colour texture!
		// Please note that the Framebuffer object actually stores a lot of state information, such as draw buffers. That's why this is in the init.
		GLenum buffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, buffers);
		
		unbind();
	}
	
	void FBORenderer::destroy() {
		glDeleteFramebuffers(1, &m_fboID);
		m_fboID = 0;
		glDeleteTextures(m_numTextures, &m_textureIDs[0]);
		delete[] m_textureIDs;
		m_textureIDs = nullptr;
		
		Renderer::destroy();
	}
	
	void FBORenderer::begin() 
	{
		Renderer::begin();
		
		// This begin function actually should bind the FBO and set the necessary settings
		
		// First, obviously bind the FBO & attached textures.
		bind();
		
		// Make sure that we clear the actual buffer objects
		glClearColor(1.0, 0.0f, .863f, 0.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		
		// Enable writing to the depth attachment
		glEnable(GL_DEPTH_TEST);
		// Set a normalized depth variable
		glDepthMask(GL_TRUE);
		// Set it so that closer depths are smaller numbers (0.0 appears in front of 0.5 which appears in front of 1.0, etc)
		glDepthFunc(GL_LESS);
		
		// Make sure that we blend the alpha channels on each texture
		glEnable(GL_BLEND);
		// Blend pretty normally for transparency stuff (according to the docs for glBlendFunc, this is the best transparency blending config)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		// Now we will not unbind until the end() call, after all the draw calls that actually populate the FBO's textures' data.
	}

	void FBORenderer::end()
	{
		// All we need to do is unbind the FBO and associated textures.
		unbind();
	}
	
	void FBORenderer::preRender() {
		// Make sure that the FBO is written as a single texture, essentially - not depth-tested by parts.
		glDisable(GL_DEPTH_TEST);
		
		// Pre-render is going to be pretty bare, as our shader just needs to be called for the uploading of texture data (in createRenderBatches()), and the only uniforms used are constants.
		//glm::mat4 matrix = m_camera->getCameraMatrix();
		//m_shader.setUniformMatrix("projectionMatrix", GL_FALSE, matrix);
		/// The camera should only be used to actually draw the FBO.
		
		// Set GL_TEXTURE1 & GL_TEXTURE0
		GLContextManager::getContext()->setActiveTexture(GL_TEXTURE1);
		GLContextManager::getContext()->bindTexture(GL_TEXTURE_2D, m_textureIDs[1]);
		GLContextManager::getContext()->setActiveTexture(GL_TEXTURE0);
		GLContextManager::getContext()->bindTexture(GL_TEXTURE_2D, m_textureIDs[0]);
		
		m_camera->update();
	}

	void FBORenderer::createRenderBatches()
	{
		// We need to now create the "renderbatches", which in our case are just going to be two triangles (for a full-screen quad)
		// Easiest way to do this is just to create a glyph, then follow how BasicRenderer did it! Why re-invent the wheel?
		glm::vec2 position = m_camera->getPosition();
		glm::vec2 size = m_camera->getScreenSizeFromViewedSize(m_size);
		
		glm::vec4 destRect(position.x, position.y, size.x, size.y);
		glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
		Glyph fullscreen(destRect, uvRect, m_textureIDs[0], 0.0f, Colour(255, 255, 255, 255));
		
		// Our collection of 6 vertices (for a square)
		std::vector<Vertex> vertices;
		vertices.resize(6);
		
		// Actually add the texture to the render batches
		m_batches.emplace_back(0, 6, fullscreen.texture);
		
		// Set up the vertices
		vertices[0] = fullscreen.topLeft;
		vertices[1] = fullscreen.bottomLeft;
		vertices[2] = fullscreen.bottomRight;
		vertices[3] = fullscreen.bottomRight;
		vertices[4] = fullscreen.topRight;
		vertices[5] = fullscreen.topLeft;
		
		// Bind the VBO
		m_vertexArrayObject.bindVBO();
		
		// Upload the data to the VBO
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
		
		// Unbind the VBO once again
		m_vertexArrayObject.unbindVBO();
		
	}

	void FBORenderer::createTextures()
	{
		// Time to actually create the textures for the colour and depth to be stored into.
		// Create array for handles
		m_textureIDs = new GLuint[m_numTextures];
		
		// Create the texture instances and get the handles
		glGenTextures(m_numTextures, &m_textureIDs[0]);
		
		// Now, for each texture we need to bind it, define it, then attach it to the FBO
		for(unsigned int i = 0; i < m_numTextures; i++) {
			// first, set the active texture to that of GL_TEXTURE0 + i, so each attachment gets its own "spot"
			GLContextManager::getContext()->setActiveTexture(GL_TEXTURE0 + i);
			
			// Now bind the texture to its slot
			GLContextManager::getContext()->bindTexture(GL_TEXTURE_2D, m_textureIDs[i]);
			
			// Just define the texture's basic properties - how it stores data, its size, etc. No data is added here.
			GLenum attachmentType;
			switch(i) {
				case 0:
					// Just a regular texture.
					attachmentType = GL_COLOR_ATTACHMENT0;
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.x, m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
					break;
				case 1:
					// Set the texture's type to 32 total bits, with 8 reserved for the stencil.
					attachmentType = GL_DEPTH_ATTACHMENT;
					glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_size.x, m_size.y, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
					break;
				default:
					throwFatalError(BAREError::FBO_FAILURE, "Too many attachments: " + std::to_string(i));
			}
			
			// Give the texture some more basic settings.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			float backColour[] = { 0.0f, 0.0f, 0.0f, 0.0f }; // Fully transparent
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, backColour);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			
			// Now that we've defined the texture, we need to attach it to the FBO!
			// Attaches either a color or depth attachment of type texture2D with 0 mipmapping levels.
			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, m_textureIDs[i], 0);
			
			// Now that its attached, we can unbind the texture
			GLContextManager::getContext()->bindTexture(GL_TEXTURE_2D, 0);
		}
	}
	
	void FBORenderer::createFBO() {
		// Tell OpenGL we want to create an FBO, and store its handle
		glGenFramebuffers(1, &m_fboID);
		
		// Bind it
		glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);
		
		// Create all of its "child" textures
		createTextures();
		
		// Check to make sure it worked.
		GLint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if(status != GL_FRAMEBUFFER_COMPLETE) {
			throwFatalError(BAREError::FBO_FAILURE);
			// Set the fbo handle to 0 to make sure we show its borked
			m_fboID = 0;
		}
		
		// Finally, unbind it
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	
	void FBORenderer::bind() {
		// First, the FBO
		glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);
		
		// Now the textures.
		// First, the colour texture in texture0
		GLContextManager::getContext()->setActiveTexture(GL_TEXTURE0);
		GLContextManager::getContext()->bindTexture(GL_TEXTURE_2D, m_textureIDs[0]);
		// Next, the depth+stencil texture in texture1
		GLContextManager::getContext()->setActiveTexture(GL_TEXTURE1);
		GLContextManager::getContext()->bindTexture(GL_TEXTURE_2D, m_textureIDs[1]);
	}
	
	void FBORenderer::unbind() {
		// First, unbind the textures
		GLContextManager::getContext()->unbindTexture(GL_TEXTURE_2D, GL_TEXTURE1);
		GLContextManager::getContext()->unbindTexture(GL_TEXTURE_2D, GL_TEXTURE0);
		
		// Now, unbind the FBO
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}
