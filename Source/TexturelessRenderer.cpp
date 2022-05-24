#include "TexturelessRenderer.hpp"

#include "GLContextManager.hpp"

namespace BARE2D {

	TexturelessRenderer::TexturelessRenderer(std::string& fragShader,
											 std::string& vertShader,
											 unsigned int perspectiveWidth,
											 unsigned int perspectiveHeight) :
		Renderer(),
		m_fragShader(fragShader), m_vertShader(vertShader) {
		m_camera = std::make_shared<Camera2D>();
		m_camera->init(perspectiveWidth, perspectiveHeight);
	}

	TexturelessRenderer::~TexturelessRenderer() {
	}

	void TexturelessRenderer::init() {
		m_shader.compileShaders(m_vertShader.c_str(), m_fragShader.c_str());

		link({"vertexPosition", "vertexColour", "vertexUV"});

		Renderer::init(); // Initializes the VAO, so we can add attributes.

		m_vertexArrayObject.addVertexAttribute(3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		m_vertexArrayObject.addVertexAttribute(4,
											   GL_UNSIGNED_BYTE,
											   GL_TRUE,
											   sizeof(Vertex),
											   (void*)offsetof(Vertex, colour));
		m_vertexArrayObject.addVertexAttribute(2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		// Create our blank texture
		glGenTextures(1, &m_texture);
		// Now bind the texture to its slot
		GLContextManager::getContext()->bindTexture(GL_TEXTURE_2D, m_texture);

		// all white
		unsigned char* data = new unsigned char[4];
		data[0]				= 255;
		data[1]				= 255;
		data[2]				= 255;
		data[3]				= 255;

		glTexImage2D(GL_TEXTURE_2D,
					 0,
					 GL_RGBA,
					 1, // x size
					 1, // y size
					 0,
					 GL_RGBA,
					 GL_UNSIGNED_BYTE,
					 &data[0]);

		// OpenGL copies data, we can delete
		delete[] data;

		// Give the texture some more basic settings.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float backColour[] = {0.0f, 0.0f, 0.0f, 0.0f}; // Fully transparent
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, backColour);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Now that its attached, we can unbind the texture
		GLContextManager::getContext()->bindTexture(GL_TEXTURE_2D, 0);
	}

	void TexturelessRenderer::setCamera(std::shared_ptr<Camera2D> camera) {
		m_camera = camera;
	}

	std::shared_ptr<Camera2D> TexturelessRenderer::getCamera() {
		return m_camera;
	}

	void TexturelessRenderer::preRender() {
		m_camera->update();

		glm::mat4 projectionMatrix = m_camera->getCameraMatrix();
		m_shader.setUniformMatrix<glm::mat4>("projectionMatrix", GL_FALSE, &projectionMatrix);
	}

	void TexturelessRenderer::draw(glm::vec4 destRect,
								   float	 depth,
								   Colour	 colour /*255, 255, 255, 255*/,
								   float	 angle /* = 0.0f*/,
								   glm::vec2 COR /*=glm::vec2(0.5f)*/) {
		// Make sure it's actually in the scene.
		if(!m_camera->isRectInViewspace(destRect))
			return;

		// At this point we can just scale the size (the position should be translated in the shader) and draw it

		glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

		// Just add the glyph
		m_glyphs.push_back(new Glyph(destRect, uv, m_texture, depth, colour, angle, COR));
	}

	void TexturelessRenderer::createRenderBatches() {
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
		m_batches.emplace_back(offset, 6, m_texture);
		vertices[vertex++] = m_glyphs[0]->topLeft;
		vertices[vertex++] = m_glyphs[0]->bottomLeft;
		vertices[vertex++] = m_glyphs[0]->bottomRight;
		vertices[vertex++] = m_glyphs[0]->bottomRight;
		vertices[vertex++] = m_glyphs[0]->topRight;
		vertices[vertex++] = m_glyphs[0]->topLeft;

		// Set the offset appropriately for 6 vertices of data.
		offset += 6;

		// Add the rest of the glyphs
		for(unsigned int glyph = 1; glyph < m_glyphs.size(); glyph++) {
			// We have no different textures, as we are rendering just blank empty squares.
			m_batches.back().numVertices += 6;

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

} // namespace BARE2D
