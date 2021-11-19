#include "GLContextManager.hpp"

namespace BARE2D {

	GLContext::GLContext() {
		m_boundTextureIDs = new GLuint[GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS];
	}
	
	GLContext::~GLContext() {
		delete[] m_boundTextureIDs;
	}
	
	void GLContext::setActiveTexture(GLenum texture)
	{
		// If we already have the same texture active, why bother OpenGL?
		if(m_activeTexture != texture) {
			m_activeTexture = texture;
			glActiveTexture(texture);
		}
	}

	void GLContext::bindTexture(GLenum target, GLenum texture)
	{
		// Make sure that the active texture's slot doesn't already have `texture` active
		unsigned int index = (unsigned int)(m_activeTexture - GL_TEXTURE0);
		if(m_boundTextureIDs[index] != texture) {
			m_boundTextureIDs[index] = texture;
			glBindTexture(target, texture);
		}
	}
	
	GLuint GLContext::getBoundTexture() {
		unsigned int index = (unsigned int)(m_activeTexture - GL_TEXTURE0);
		return m_boundTextureIDs[index];
	}

	GLContext* GLContextManager::m_context = nullptr;
	
	GLContext* GLContextManager::getContext()
	{
		if(m_context) {
			return m_context;
		} else {
			m_context = new GLContext();
			return m_context;
		}
	}

}
