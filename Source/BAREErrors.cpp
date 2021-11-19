#include "BAREErrors.hpp"

#include <iostream>
#include <SDL2/SDL.h>

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
			default:
				return "EC DNE - Unknown error.";
		}
	}
	
	void throwFatalError(std::string message) {
		std::cout << std::endl << std::endl << "FATAL ERROR:" << std::endl << message << std::endl;
		exit(EXIT_FAILURE);
	}
	
	void throwFatalError(BAREError err) {
		std::cout << std::endl << std::endl << "FATAL ERROR:" << std::endl;
		throwError(err);
		displayErrors();
		exit(EXIT_FAILURE);
	}

	void throwError(BAREError err)
	{
		thrownErrors.push_back(err);
	}

	void displayErrors()
	{
		std::cout << std::endl << "Thrown Errors: " << std::endl;
		for(unsigned int i = 0; i < thrownErrors.size(); i++) {
			std::cout << getErrString(thrownErrors[i]) << std::endl;
		}
		thrownErrors.clear();
	}
}
