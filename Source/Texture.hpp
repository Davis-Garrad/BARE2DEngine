#pragma once

#include <GL/glew.h>
#include <string>

namespace BARE2D {

	/**
	 * @struct Texture
	 * @brief The texture struct holds very basic stuff - the filepath, width, height, and ID, 
	 */
	struct Texture
	{
		std::string filepath = "";
		GLuint id;
		int width = 0; // width in pixels
		int height = 0; // height in pixels
	};

}

