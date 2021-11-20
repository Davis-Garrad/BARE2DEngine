#include "VAO.hpp"

namespace BARE2D {

	VAO::VAO()
	{
		m_numAttributes = 0;
	}

	VAO::~VAO()
	{
	}

	void VAO::init()
	{
		// Generate VAO, VBO, and connect em up
		// Generate VAO
		glGenVertexArrays(1, &m_vaoHandle);
		
		// Now bind it so the VBO is created as a part of it
		bind();
		
		// Generate VBO inside of the VAO
		glGenBuffers(1, &m_vboHandle);
		
		// Bind the VBO to the VAO
		glBindBuffer(GL_ARRAY_BUFFER, m_vboHandle);
		
		// Unbind, we're done for now.
		unbind();
	}

	void VAO::destroy()
	{
		// Unbind first!
		unbind();
		
		// Disable all vertex attributes
		for(unsigned int i = 0; i < m_numAttributes; i++) {
			glDisableVertexAttribArray(i);
		}
		
		// Delete buffers
		glDeleteBuffers(1, &m_vboHandle);
		glDeleteVertexArrays(1, &m_vaoHandle);
	}

	void VAO::bind()
	{
		glBindVertexArray(m_vaoHandle);
	}
	
	void VAO::unbind() {
		glBindVertexArray(0);
	}

	void VAO::bindVBO()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vboHandle);
	}
	
	void VAO::unbindVBO() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VAO::addVertexAttribute(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* data)
	{
		// Bind first - It doesn't matter that this is inefficient because we're only calling this like 3 times in the whole program
		bind();
		bindVBO();
		
		// Tell OpenGL what kind of data goes in that array
		glVertexAttribPointer(m_numAttributes, size, type, normalized, stride, data);
		// Enable the array
		glEnableVertexAttribArray(m_numAttributes);
		
		// Increment our number of attributes to reflect reality.
		m_numAttributes++;
		
		// Unbind for safety!
		unbind();
	}

}
