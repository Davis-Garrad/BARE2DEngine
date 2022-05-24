#include "MutableTexture.hpp"

#include "GLContextManager.hpp"

#include "Logger.hpp"

namespace BARE2D {

	void MutableTexture::setData(unsigned char* data) {
		setData(data, 0, 0, width, height);
	}

	void MutableTexture::setData(unsigned char* data,
								 unsigned int	xOffset,
								 unsigned int	yOffset,
								 unsigned int	subWidth,
								 unsigned int	subHeight) {
		GLContextManager::getContext()->bindTexture(GL_TEXTURE_2D, id);

		if(channels != 4)
			glPixelStorei(GL_UNPACK_ALIGNMENT, channels);

		glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, subWidth, subHeight, format, GL_UNSIGNED_BYTE, data);

		if(channels != 4)
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		GLContextManager::getContext()->bindTexture(GL_TEXTURE_2D, 0);
	}

} // namespace BARE2D
