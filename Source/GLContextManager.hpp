#pragma once

#include <GL/gl.h>

namespace BARE2D {

	class GLContext {
	public:
		GLContext();
		~GLContext();
		/**
		 * @brief Sets the active texture "slot". This can be GL_TEXTURE0 to GL_TEXTURE8 (I think. Check the literature)
		 * @param texture The texture slot to tell OpenGL is "active"
		 */
		void setActiveTexture(GLenum texture);
		
		/**
		 * @brief Binds a texture to target in the currently active texture slot
		 * @param target The target to bind to 
		 * @param texture The id of a texture.
		 */
		void bindTexture(GLenum target, GLenum texture);
		
		/**
		 * @brief Unbinds a texture
		 * @param target The target (GL_TEXTURE_2D generally)
		 * @param textureslot The texture to be unbound (GL_TEXTURE0-8)
		 */
		void unbindTexture(GLenum target, GLenum textureslot);
		
		GLuint getBoundTexture();

	private:
		// The active texture "slot"
		GLenum m_activeTexture = GL_TEXTURE0;
		
		// Holds a bound texture for each texture "slot" there is in OpenGL (1 for GL_TEXTURE0, 1 for GL_TEXTURE1, etc.)
		GLuint* m_boundTextureIDs = nullptr;
	};


	class GLContextManager
	{
	public:
		static GLContext* getContext();
		
	private:
		static GLContext* m_context;

	};

}

