#include "Window.h"

#include <GL/glew.h>

#include "Logger.h"

namespace BARE2D {

	Window::Window()
	{
	}

	Window::~Window()
	{
	}
	
	BAREError Window::create(unsigned int flags) {
		// Since we are creating an OpenGL application, this is mandatory.
		Uint32 windowFlags = SDL_WINDOW_OPENGL;
		
		windowFlags |= flags;
		
		// Set some SDL attributes, such as the minimum version required, if core profiles are enabled, etc.
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3.2); // Sets the OpenGL context attribute (minimum version) to 3.2
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4.5); // Sets the OpenGL context attribute (maximum version) to 4.5
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // Set the OpenGL context to be the core version
		
		// Actually create the window (or tell SDL to create it, anyways)
		m_SDLWindow = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, windowFlags);
		
		// Check if creation was successful
		if(m_SDLWindow == nullptr) {
			return BAREError::SDL_FAILURE;
		}
		
		// This enables glew's experimental mode, where we can use core profiles, etc.
		glewExperimental = GL_TRUE;
		
		// Now create the GL context
		m_GLContext = SDL_GL_CreateContext(m_SDLWindow);
		
		// Check if creation was successful
		if(m_GLContext == nullptr) {
			return BAREError::SDL_FAILURE;
		}
		
		// Now that we actually have a GL context, we need to set it up - done with the help of GLEW!
		GLenum err = glewInit();
		
		// Check for errors
		if(err != GLEW_OK) {
			return BAREError::GLEW_FAILURE;
		}
		
		// Now log the OpenGL verion used, just a useful piece of info
        std::printf("***   OpenGL Version: %s   ***\n", glGetString(GL_VERSION));
		
		// Clear it, baby
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		
		// Set VSync on 
		SDL_GL_SetSwapInterval(0);
		
		// Enable alpha blend
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		return BAREError::NONE;
	}

	void Window::setTitle(std::string newTitle) {
		m_title = newTitle;
		SDL_SetWindowTitle(m_SDLWindow, newTitle.c_str());
	}
	
	void Window::setSize(unsigned int width, unsigned int height) {
		m_width = width;
		m_height = height;
		if(m_SDLWindow) {
			SDL_SetWindowSize(m_SDLWindow, width, height);
			
			// Reset the viewport to the full window
			glViewport(0, 0, width, height);
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	void Window::swapBuffer() {
		SDL_GL_SwapWindow(m_SDLWindow);
	}

	unsigned int Window::getWidth() const {
		return m_width;
	}
	
	unsigned int Window::getHeight() const {
		return m_height;
	}

}

