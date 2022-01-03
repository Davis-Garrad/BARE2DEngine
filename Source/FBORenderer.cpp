#include "FBORenderer.hpp"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "GLContextManager.hpp"

#include "BAREErrors.hpp"
#include "Vertex.hpp"

namespace BARE2D
{

	FBORenderer::FBORenderer(std::string& fragShader,
	                         std::string& vertShader,
	                         unsigned int windowWidth,
	                         unsigned int windowHeight,
	                         glm::vec2 size,
	                         unsigned int numColourAttachments)
		: m_fragmentShaderPath(fragShader)
		, m_vertexShaderPath(vertShader)
		, m_size(size)
	{
		m_camera = std::make_unique<Camera2D>();
		m_camera->init(windowWidth, windowHeight);
		m_camera->offsetPosition(glm::vec2(-1.0f, -1.0f));

		m_numTextures = numColourAttachments + 1; // n colour attachments, one depth/stencil attachment
	}

	FBORenderer::~FBORenderer()
	{
		delete[] m_textureIDs;
	}

	void FBORenderer::setCamera(std::shared_ptr<Camera2D>& cam)
	{
		m_camera = cam;
	}

	std::shared_ptr<Camera2D> FBORenderer::getCamera()
	{
		return m_camera;
	}

	void FBORenderer::init()
	{
		// Actually initialize our shader
		m_shader.compileShaders(m_vertexShaderPath.c_str(), m_fragmentShaderPath.c_str());

		m_shader.linkShaders({ "vertexPosition", "vertexColour", "vertexUV" });

		Renderer::init(); // Initializes the VAO, so we can add attributes

		m_vertexArrayObject.addVertexAttribute(3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		m_vertexArrayObject.addVertexAttribute(
		    4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));
		m_vertexArrayObject.addVertexAttribute(2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		// Create the actual textures and FBO
		createFBO();

		m_shader.use();

		initUniforms();

		m_shader.unuse();

		bind();

		// This call specifies which buffers should be drawn to - in our case, it's just the colour attachment for the FBO
		// This essentially means that the output from the fragment shader goes directly into the FBO's attached colour
		// texture! Please note that the Framebuffer object actually stores a lot of state information, such as draw
		// buffers. That's why this is in the init. Here we just generate all the colour attachments from 0 to
		// (m_numColourAttachments-1).
		std::vector<GLenum> m_colourAttachments;
		for(unsigned int i = 0; i < m_numTextures - 1;
		        i++)   // Remember that the number of colour attachments will always be number of textures - 1
		{
			m_colourAttachments.push_back(GL_COLOR_ATTACHMENT0 + i);
		}
		glDrawBuffers(m_numTextures - 1, m_colourAttachments.data());

		unbind();
	}

	void FBORenderer::initUniforms()
	{
		// Now, for convenience, set the uniforms of the FBO shader program
		for(unsigned int i = 0; i < m_numTextures - 1; i++)
		{
			GLint colourTexture = i;
			m_shader.setUniform("colourTexture" + std::to_string(i), &colourTexture);
		}

		m_shaderHasDepth = m_shader.doesUniformExist("depthTexture");
		if(m_shaderHasDepth)
		{
			GLint depthTexture = m_numTextures - 1;
			m_shader.setUniform("depthTexture", &depthTexture);
		}
	}

	void FBORenderer::destroy()
	{
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
		// Blend pretty normally for transparency stuff (according to the docs for glBlendFunc, this is the best
		// transparency blending config)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_shader.use();

		// Now we will not unbind until the end() call, after all the draw calls that actually populate the FBO's textures'
		// data.
	}

	void FBORenderer::end()
	{
		m_shader.unuse();

		// All we need to do is unbind the FBO and associated textures.
		unbind();
	}

	void FBORenderer::preRender()
	{
		// Make sure that the FBO is written as a single texture, essentially - not depth-tested by parts.
		glDisable(GL_DEPTH_TEST);

		// Pre-render is going to be pretty bare, as our shader just needs to be called for the uploading of texture data
		// (in createRenderBatches()), and the only uniforms used are constants.
		// glm::mat4 matrix = m_camera->getCameraMatrix();
		// m_shader.setUniformMatrix("projectionMatrix", GL_FALSE, matrix);
		/// The camera should only be used to actually draw the FBO.

		// Set GL_TEXTURE's
		GLContext* context = GLContextManager::getContext();
		for(int i = m_numTextures - 1; i >= 0; i--)
		{
			context->setActiveTexture(GL_TEXTURE0 + i);
			context->bindTexture(GL_TEXTURE_2D, m_textureIDs[i]);
		}

		m_camera->update();
	}

	void FBORenderer::createRenderBatches()
	{
		// We need to now create the "renderbatches", which in our case are just going to be two triangles (for a
		// full-screen quad) Easiest way to do this is just to create a glyph, then follow how BasicRenderer did it! Why
		// re-invent the wheel?
		glm::vec2 position = m_camera->getPosition();
		glm::vec2 size = m_camera->getScreenSizeFromViewedSize(m_size);

		glm::vec4 destRect(position.x, position.y, size.x, size.y);
		glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
		float depth = 0.0f;
		Colour col = Colour(255, 255, 255, 255);
		Glyph fullscreen(destRect, uvRect, m_textureIDs[0], depth, col);

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

	void FBORenderer::render()
	{
		// Ensure that we're actually using the shader for the glDrawArrays call!
		m_shader.use();

		// Make sure we're in the regular rendering texture (arbitrarily set to texture0, just for consistency)
		GLContext* glContext = GLContextManager::getContext();
		glContext->setActiveTexture(GL_TEXTURE0);

		// First we must bind the vertex array object and vertex buffer object
		m_vertexArrayObject.bind();

		preRender();

		// Create RenderBatches (uploading the vertex data to the bound texture, so that we can actually draw the textures
		// next.)
		createRenderBatches();

		// Now we can render each renderbatch, uploading their texture data respectively.
		for(unsigned int i = 0; i < m_batches.size();
		        i++)   // regularly, there will only be one - to the full screen... but you never know!
		{
			// Bind the texture information to the texture "slot"
			// This method of binding the textures decreases speed slightly for completely random textures, but if we are
			// rendering a lot of the same texture, this is similar (if not identical) to instance rendering

			// Upload the data
			glDrawArrays(GL_TRIANGLES, (GLint)m_batches[i].offset, (GLsizei)m_batches[i].numVertices);
		}

		// Unbind for safety!
		m_vertexArrayObject.unbind();

		// Release the shader
		m_shader.unuse();
	}

	void FBORenderer::createTextures()
	{
		// Time to actually create the textures for the colour and depth to be stored into.
		// Create array for handles
		m_textureIDs = new GLuint[m_numTextures];

		// Create the texture instances and get the handles
		glGenTextures(m_numTextures, &m_textureIDs[0]);

		// Now, for each texture we need to bind it, define it, then attach it to the FBO
		for(unsigned int i = 0; i < m_numTextures; i++)
		{
			// first, set the active texture to that of GL_TEXTURE0 + i, so each attachment gets its own "spot"
			GLContextManager::getContext()->setActiveTexture(GL_TEXTURE0 + i);

			// Now bind the texture to its slot
			GLContextManager::getContext()->bindTexture(GL_TEXTURE_2D, m_textureIDs[i]);

			// Just define the texture's basic properties - how it stores data, its size, etc. No data is added here.
			GLenum attachmentType = (i == m_numTextures - 1) ? GL_DEPTH_ATTACHMENT : (GL_COLOR_ATTACHMENT0 + i);
			switch(attachmentType)
			{
				case GL_DEPTH_ATTACHMENT:
					// Set the texture's type to 32 total bits, with 8 reserved for the stencil.
					glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_size.x, m_size.y, 0, GL_DEPTH_STENCIL,
					             GL_UNSIGNED_INT_24_8, nullptr);
					break;
				default:
					// Just a regular texture.
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.x, m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
					break;
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

	void FBORenderer::createFBO()
	{
		// Tell OpenGL we want to create an FBO, and store its handle
		glGenFramebuffers(1, &m_fboID);

		// Bind it
		glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);

		// Create all of its "child" textures
		createTextures();

		// Check to make sure it worked.
		GLint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if(status != GL_FRAMEBUFFER_COMPLETE)
		{
			throwFatalError(BAREError::FBO_FAILURE);
			// Set the fbo handle to 0 to make sure we show its borked
			m_fboID = 0;
		}

		// Finally, unbind it
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FBORenderer::bind()
	{
		// First, the FBO
		glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);

		// Now the textures.
		GLContext* context = GLContextManager::getContext();
		for(unsigned int i = 0; i < m_numTextures - 1; i++)
		{
			context->setActiveTexture(GL_TEXTURE0 + i);
			context->bindTexture(GL_TEXTURE_2D, m_textureIDs[i]);
		}
	}

	void FBORenderer::unbind()
	{
		// First, unbind the textures
		for(unsigned int i = 0; i < m_numTextures; i++)
			GLContextManager::getContext()->unbindTexture(GL_TEXTURE_2D, GL_TEXTURE0 + i);

		// Now, unbind the FBO
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}
