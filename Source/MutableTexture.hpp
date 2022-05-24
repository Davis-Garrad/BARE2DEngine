#pragma once

#include <GL/glew.h>

#include "Texture.hpp"

namespace BARE2D {

	/**
	 * @class MutableTexture
	 * @brief A child of Texture which allows (and gives helpful functions for) mutation.
	 */
	struct MutableTexture : public Texture {
		/**
		 * @brief Sets the data of the mutable texture, as well as updates the OpenGL context's texture data for it (uses glTextureSubImage2D).
		 * @param data The data (formatted R0,G0,B0,A0,R1,G1,B1,A0,etc.). Assumes width and height of data are equal to that of the texture.
		 * @param format The format of the data. Must follow OpenGL Formats (GL_RED, GL_RG, etc.). Defaults to GL_RGBA
		 */
		void setData(unsigned char* data);

		/**
		 * @brief Sets the data of the mutable texture, as well as updates the OpenGL context's texture data for it (uses glTextureSubImage2D).
		 * @param data The data (default formatted R0,G0,B0,A0,R1,G1,B1,A0,etc.).
		 * @param xOffset How far in from the x side the texture should be overwritten
		 * @param yOffset How far in from the y side the texture should be overwritten
		 * @param width The width of the data
		 * @param height The height of the data
		 * @param format The format of the data. Must follow OpenGL Formats (GL_RED, GL_RG, etc.). Defaults to GL_RGBA
		 */
		void setData(unsigned char* data,
					 unsigned int	xOffset,
					 unsigned int	yOffset,
					 unsigned int	subWidth,
					 unsigned int	subHeight);

		GLenum		 format	  = GL_RGBA;
		unsigned int channels = 4;
	};

} // namespace BARE2D
