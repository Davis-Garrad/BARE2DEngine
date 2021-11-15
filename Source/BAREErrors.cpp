#include "BAREErrors.h"

#include <iostream>
#include <SDL2/SDL.h>

namespace BARE2D {
	std::string getErrString(BAREError err) {
		switch(err) {
			case BAREError::SDL_FAILURE:
				return "EC SDL_FAILURE - SDL Failure to initialize. SDL_GetError() yields the following: \n\n" + std::string(SDL_GetError());
			case BAREError::DOUBLE_INIT:
				return "EC DOUBLE_INIT - There was an attempted double-initialization in the program. Not too serious, but fix it anyways, nerd.";
			case BAREError::GLEW_FAILURE:
				return "EC GLEW_FAILURE - GLEW could not be initialized!";
			default:
				return "EC 0 - No error.";
		}
	}
	
	void throwFatalError(std::string message) {
		std::cout << std::endl << std::endl << "FATAL ERROR:" << std::endl << message << std::endl;
		exit(EXIT_FAILURE);
	}
}
