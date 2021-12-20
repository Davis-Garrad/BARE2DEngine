#include "DebugRenderer.hpp"

#include "GLContextManager.hpp"

#define CIRCLE_LINES 90

const char* fragShaderSource = 
"#version 130\n"
"in vec3 fragmentPosition;\n"
"in vec4 fragmentColour;\n"
"out vec4 colour;\n"
"void main() {\n"
"	colour = fragmentColour;\n"
"}\n"
"\0";

const char* vertShaderSource = 
"#version 130\n"
"in vec3 vertexPosition;\n"
"in vec4 vertexColour;\n"
"out vec3 fragmentPosition;\n"
"out vec4 fragmentColour;\n"
"void main() {\n"
"	gl_Position = vec4(vertexPosition.xyz, 1.0);\n"
"	fragmentPosition = vertexPosition;\n"
"	fragmentColour = vertexColour;\n"
"}\n"
"\0";

namespace BARE2D {
	
	void Line::construct(glm::vec2 p0, glm::vec2 p1, float& thick, Colour& col) {
		point0 = p0;
		point1 = p1;
		thickness = thick;
		colour = col;
	}
	
	void Circle::construct(glm::vec2& p0, float& lineThick, float& radius, Colour& fillCol) {
		origin = p0;
		
		float lastX = 0;
		float lastY = radius;
		
		for(unsigned int i = 1; i < CIRCLE_LINES+1.0f; i++) {
			float radians = 2.0f*M_PI*((float)i/((float)CIRCLE_LINES-2.0f));
			float x0 = std::sin(radians)*radius;
			float y0 = std::cos(radians)*radius;
			
			// Construct a new line from last to here
			Line l;
			glm::vec2 newPoint0 = glm::vec2(lastX, lastY) + p0, newPoint1 = glm::vec2(x0, y0) + p0;
			l.construct(newPoint0, newPoint1, lineThick, fillCol);
			lines.push_back(l);
			
			lastX = x0;
			lastY = y0;
		}
	}
	
	void Rectangle::construct(glm::vec4& posSize, float& lineThick, Colour& fillCol) {
		destRect = posSize;
		
		glm::vec2 pos(posSize.x, posSize.y), size(posSize.z, posSize.w);
		
		lines[0].construct(pos, pos + size * glm::vec2(0.0f, 1.0f), lineThick, fillCol);
		lines[1].construct(pos + size * glm::vec2(1.0f, 0.0f), pos + size * glm::vec2(1.0f, 1.0f), lineThick, fillCol);
	}

	DebugRenderer::DebugRenderer()
	{
	}

	DebugRenderer::~DebugRenderer()
	{
	}

	void DebugRenderer::init()
	{
		// Make shaders lol
		m_shader.compileShadersFromSource(vertShaderSource, fragShaderSource);
		
		m_shader.linkShaders({"vertexPosition", "vertexColour"});
		
		Renderer::init();
		
		m_vertexArrayObject.addVertexAttribute(3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		m_vertexArrayObject.addVertexAttribute(4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));
	}

	void DebugRenderer::begin() {
		Renderer::begin();
		
		m_lines.clear();
		m_circles.clear();
		m_rectangles.clear();
	}

	void DebugRenderer::drawLine(glm::vec2 point0, glm::vec2 point1, float thickness, Colour colour)
	{
		m_lines.emplace_back();
		m_lines.back().construct(point0, point1, thickness, colour);
	}

	void DebugRenderer::drawCircle(glm::vec2 centre, float lineThickness, float radius, Colour fillColour)
	{
		m_circles.emplace_back();
		m_circles.back().construct(centre, lineThickness, radius, fillColour);
	}

	void DebugRenderer::drawRectangle(glm::vec4 destRect, float lineThickness, Colour fillColour)
	{
		m_rectangles.emplace_back();
		m_rectangles.back().construct(destRect, lineThickness, fillColour);
	}

	void DebugRenderer::createRenderBatches()
	{
		// Create all vertices for each line, circle, and rectangle
		std::vector<Vertex> lineVertices;
		lineVertices.resize(m_lines.size() * 2); // 2 vertices/line
		
		std::vector<Vertex> circleVertices;
		circleVertices.resize(m_circles.size() * CIRCLE_LINES); // we only actually use one vertex per line, as OpenGL fills in the rest.
		
		std::vector<Vertex> rectangleVertices;
		rectangleVertices.resize(m_rectangles.size() * 4); // OpenGL uses 4 vertices for a polygon, so that's what we'll do.
		
		// Set up line vertices
		for(unsigned int i = 0; i < m_lines.size(); i++) {
			// Set the positions
			lineVertices[2*i].setPosition(m_lines[i].point0.x, m_lines[i].point0.y, 0.0f);
			lineVertices[2*i+1].setPosition(m_lines[i].point1.x, m_lines[i].point1.y, 0.0f);
			
			// Set the colours
			lineVertices[2*i].colour = m_lines[i].colour;
			lineVertices[2*i+1].colour = m_lines[i].colour;
			
			// No UV. 
		}
		
		// Set up circle vertices
		for(unsigned int i = 0; i < m_circles.size(); i++) {
			circleVertices[i*CIRCLE_LINES].setPosition(m_circles[i].origin.x, m_circles[i].origin.y, 0.0f);
			circleVertices[i*CIRCLE_LINES].colour = m_circles[i].lines[0].colour;
			for(unsigned int vertex = 1; vertex < CIRCLE_LINES; vertex++) {
				// Set the position
				circleVertices[vertex+CIRCLE_LINES*i].setPosition(m_circles[i].lines[vertex].point0.x, m_circles[i].lines[vertex].point0.y, 0.0f);
				
				// Set the colours
				circleVertices[vertex+CIRCLE_LINES*i].colour = m_circles[i].lines[0].colour;
				
				// No UV.
			}
		}
		
		// Set up the rectangle vertices
		for(unsigned int i = 0; i < m_rectangles.size(); i++) {
			// Set the positions
			rectangleVertices[4*i].setPosition(m_rectangles[i].lines[0].point0.x, m_rectangles[i].lines[0].point0.y, 0.0f);
			rectangleVertices[4*i+1].setPosition(m_rectangles[i].lines[0].point1.x, m_rectangles[i].lines[0].point1.y, 0.0f);
			rectangleVertices[4*i+2].setPosition(m_rectangles[i].lines[1].point0.x, m_rectangles[i].lines[1].point0.y, 0.0f);
			rectangleVertices[4*i+3].setPosition(m_rectangles[i].lines[1].point1.x, m_rectangles[i].lines[1].point1.y, 0.0f);
			
			// Set the colours
			rectangleVertices[4*i].colour = m_rectangles[i].lines[0].colour;
			rectangleVertices[4*i+1].colour = m_rectangles[i].lines[0].colour;
			rectangleVertices[4*i+2].colour = m_rectangles[i].lines[0].colour;
			rectangleVertices[4*i+3].colour = m_rectangles[i].lines[0].colour;
			
			// No UV.
		}
		
		// Now actually upload the data!
		// Bind the VBO
		m_vertexArrayObject.bindVBO();
		
		// Combine vectors
		std::vector<Vertex> verticesTotal;
		verticesTotal.reserve(lineVertices.size() + circleVertices.size() + rectangleVertices.size());
		verticesTotal.insert(verticesTotal.end(), lineVertices.begin(), lineVertices.end());
		verticesTotal.insert(verticesTotal.end(), circleVertices.begin(), circleVertices.end());
		verticesTotal.insert(verticesTotal.end(), rectangleVertices.begin(), rectangleVertices.end());
		
		// upload data
		glBufferData(GL_ARRAY_BUFFER, verticesTotal.size() * sizeof(Vertex), verticesTotal.data(), GL_DYNAMIC_DRAW);
	}
	
	void DebugRenderer::render() {
		m_shader.use();
		
		GLContextManager::getContext()->setActiveTexture(GL_TEXTURE0);
		
		m_vertexArrayObject.bind();
		
		GLint offset = 0;
		
		// Draw lines
		// Draw two vertices, then step the data forward two vertices for each line.
		for(unsigned int i = 0; i < m_lines.size(); i++) {
			glLineWidth(m_lines[i].thickness);
			glDrawArrays(GL_LINES, offset, (GLsizei)2);
			offset += 2;
		}
		
		// Draw circles
		for(unsigned int i = 0; i < m_circles.size(); i++) {
			glDrawArrays(GL_TRIANGLE_FAN, offset, (GLsizei)CIRCLE_LINES);
			offset += CIRCLE_LINES;
		}
		
		// Draw rectangles
		for(unsigned int i = 0; i < m_rectangles.size(); i++) {
			glDrawArrays(GL_TRIANGLE_STRIP, offset, (GLsizei)4);
			offset += 4;
		}
		
		// Unbind and exit!
		m_vertexArrayObject.unbind();
		
		m_shader.unuse();
	}

}
