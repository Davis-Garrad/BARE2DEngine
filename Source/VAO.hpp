#pragma once

#include <GL/glew.h>

namespace BARE2D {

	/**
	 * @class VAO
	 * @brief A wrapper class for OpenGL's VAO, as well as its associated VBO and attributes
	 */
	class VAO
	{
	public:
		VAO();
		~VAO();
		
		/**
		 * @brief Initializes the necessary components, combining the VBO and VAO
		 */
		void init();
		
		/**
		 * @brief Releases necessary memory.
		 */
		void destroy();
		
		/**
		 * @brief Binds this vertex array object.
		 */
		void bind();
		
		/**
		 * @brief Binds the VAO's VBO
		 */
		void bindVBO();
		
		/**
		 * @brief Unbinds the vao.
		 */
		void unbind();
		
		/**
		 * @brief Unbinds this VAO's VBO
		 */
		void unbindVBO();
		
		/**
		 * @brief Wrapper for glVertexAttribPointer - Adds an attribute to the VBO - each vertex data slot will gain some attribute.
		 * @param size Number of components per attribute (1-4)
		 * @param type Type of data - GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, etc. See docs
		 * @param normalized Should the data be normalized or converted directly? (GL_TRUE/GL_FALSE)
		 * @param stride Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
		 * @param data Specifies a offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
		 */
		void addVertexAttribute(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* data);
		
	private:
		unsigned int m_numAttributes; // How many attributes we've added so far.
		
		GLuint m_vaoHandle; // The GL-provided handle for the VAO
		GLuint m_vboHandle; // The GL-provided handle for the VBO (Yes, there's only one. Each 'vertex' in the vertex buffer object combines all the data)

	};

}

