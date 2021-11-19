#include "MutableTexture.hpp"

namespace BARE2D {
	
	void MutableTexture::setData(unsigned char* data, GLenum format/** = GL_RGBA*/) {
		setData(data, 0, 0, width, height, format);
	}
	
	void MutableTexture::setData(unsigned char* data, unsigned int xOffset, unsigned int yOffset, unsigned int subWidth, unsigned int subHeight, GLenum format/** = GL_RGBA*/) {
		glTexSubImage2D(id, 0, xOffset, yOffset, subWidth, subHeight, format, GL_TEXTURE_2D, data);
	}

}
