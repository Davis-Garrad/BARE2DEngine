#include "BAREErrors.hpp"

#include <iostream>
#include <iomanip>
#include <SDL2/SDL.h>
#include <GL/glew.h>

void GLAPIENTRY MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
	
}

namespace BARE2D {
	std::vector<BAREError> thrownErrors;
	
	std::string getErrString(BAREError err) {
		switch(err) {
			case BAREError::SDL_FAILURE:
				return "EC SDL_FAILURE - SDL Failure to initialize. SDL_GetError() yields the following: \n\n" + std::string(SDL_GetError());
			case BAREError::DOUBLE_INIT:
				return "EC DOUBLE_INIT - There was an attempted double-initialization in the program. Not too serious, but fix it anyways, nerd.";
			case BAREError::GLEW_FAILURE:
				return "EC GLEW_FAILURE - GLEW could not be initialized!";
			case BAREError::GL_FAILURE_VERSION:
				return "EC GL_FAILURE_VERSION - GL Version is not good enough.";
			case BAREError::TEXTURE_FAILURE:
				return "EC TEXTURE_FAILURE - Texture could not be loaded from file or created.";
			case BAREError::VERTEX_SHADER_FAILURE:
				return "EC VERTEX_SHADER_FAILURE";
			case BAREError::FRAGMENT_SHADER_FAILURE:
				return "EC FRAGMENT_SHADER_FAILURE";
			case BAREError::UNIFORM_NOT_FOUND:
				return "EC UNIFORM_NOT_FOUND";
			case BAREError::SHADER_COMPILE_FAILURE:
				return "EC SHADER_COMPILE_FAILURE";
			case BAREError::SHADER_LINK_FAILURE:
				return "EC SHADER_LINK_FAILURE";
			case BAREError::GLSL_PROGRAM_FAILURE:
				return "EC GLSL_PROGRAM_FAILURE";
			case BAREError::FONT_FAILURE:
				return "EC FONT_FAILURE";
			case BAREError::FBO_FAILURE:
				return "EC FBO_FAILURE";
			case BAREError::LOGGER_FAILURE:
				return "EC LOGGER_FAILURE";
			default:
				return "EC DNE - Unknown error.";
		}
	}
	
	void throwFatalError(BAREError err, std::string message) {
		std::cout << "\n";
		std::cout << std::setfill('#') << std::setw(50) << "\n";
		std::cout << "FATAL ERROR: " << "\n";
		std::cout << std::setfill('#') << std::setw(50) << "\n\n";
		throwError(err, message);
		displayErrors();
		exit(EXIT_FAILURE);
	}

	void throwError(BAREError err, std::string message)
	{
		thrownErrors.push_back(err);
		// We use std::cout just in case the Logger never actually got inited.
		if(message != "") {
			std::cout << std::setfill('-') << std::setw(50) << "\n";
			std::cout << "Error: " << message << std::endl;
			std::cout << thrownErrors.size()-1 << ": " << getErrString(err) << std::endl;
			std::cout << std::setfill('-') << std::setw(50) << "\n";
		}
	}

	void displayErrors()
	{
		std::cout << std::endl << "Thrown Errors: " << std::endl;
		std::cout << std::setfill('-') << std::setw(50) << "\n";
		for(unsigned int i = 0; i < thrownErrors.size(); i++) {
			std::cout << i << ": " << getErrString(thrownErrors[i]) << std::endl;
			std::cout << std::setfill('-') << std::setw(50) << "\n";
		}
		thrownErrors.clear();
	}
	
	void initGLErrorCallback() {
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);
	}
}
