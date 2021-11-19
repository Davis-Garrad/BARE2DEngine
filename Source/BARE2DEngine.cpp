#include "BARE2DEngine.hpp"

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "BAREErrors.hpp"

namespace BARE2D {

	void init() {
		// Initialize all of SDL
		int err = SDL_Init(SDL_INIT_EVERYTHING);
		// Get error from SDL
		if(err != 0) {
			throwFatalError(BAREError::SDL_FAILURE);
		}
		
		// Tell SDL to create a double buffered window, to avoid flickering.
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);
	}

}
