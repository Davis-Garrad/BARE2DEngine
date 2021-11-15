#include "App.h"

#include <SDL2/SDL.h>
#include <GL/gl.h>

#include "BARE2DEngine.h"
#include "InputManager.h"
#include "Screen.h"
#include "Window.h"

namespace BARE2D {

	App::App()
	{
		BAREError err = init();
		if(err != BAREError::NONE) {
			throwFatalError(getErrString(err));
		}
	}

	App::~App()
	{
		if(m_isGameRunning) {
			exitApp();
		}
	}

	void App::run()
	{
		// Init if we haven't already
		if(!m_isInited) {
			BAREError err = init();
			if(err != BAREError::NONE) {
				throwFatalError(getErrString(err));
			}
		}
		
		// Start the gameloop!
		m_isGameRunning = true;
		
		// Make sure to actually "enter" the entry screen
		m_screenList->getCurrentScreen()->onEntry();
		
		// Gameloop
		while(m_isGameRunning) {
			update();
			draw();
			m_window->swapBuffer();
		}
	}
	
	
	ScreenList* App::getScreenList() {
		return m_screenList.get();
	}
	
	
	Window* App::getWindow() {
		return m_window;
	}


	BAREError App::init()
	{
		// Make sure not to init twice
		if(m_isInited) return BAREError::DOUBLE_INIT;
		
		// Init the screen list
		m_screenList = std::make_unique<ScreenList>();
		
		// Init the engine
		BAREError err = BARE2D::init();
		if(err != BAREError::NONE) return err; // Error has occured!
		
		// Uncomment this to require hardware acceleration: (defaults to allow accelerated OR accept non-accelerated)
		// SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		
		// Init the input manager
		m_inputManager = new InputManager();
		
		// Init the window
		m_window = new Window();
		err = m_window->create(0);
		if(err != BAREError::NONE) return err; // Error has occured!
		
		// Make sure we don't double init by setting this var to true
		m_isInited = true;
		return BAREError::NONE; // No err
	}

	void App::update()
	{
		// Update everything
		updateInput();
		
		switch(m_screenList->getCurrentScreen()->getState()) {
			case ScreenState::RUNNING:
				m_screenList->getCurrentScreen()->update();
				break;
			case ScreenState::CHANGE_NEXT:
				m_screenList->moveToNextScreen();
				break;
			case ScreenState::CHANGE_PREV:
				m_screenList->moveToPreviousScreen();
			case ScreenState::EXIT_APPLICATION:
				exitApp();
				break;
			default:
				break;
		}
	}

	void App::draw()
	{
		// Reset the viewport to the full window, just in case the window changed sizes or the viewport had been changed by, for example, an FBO
		glViewport(0, 0, m_window->getWidth(), m_window->getHeight());
		
		// If the current screen is running, draw according to its protocols
		if(m_screenList->getCurrentScreen()->getState() == ScreenState::RUNNING) m_screenList->getCurrentScreen()->draw();
	}

	void App::updateInput()
	{
		m_inputManager->update();
		
		pollSDLInput();
	}
	
	void App::pollSDLInput() {
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					exitApp();
					break;
				case SDL_MOUSEMOTION:
					m_inputManager->setMousePosition((float)event.motion.x, (float)event.motion.y);
					break;
				case SDL_KEYDOWN:
					m_inputManager->pressKey(event.key.keysym.sym);
					break;
				case SDL_KEYUP:
					m_inputManager->releaseKey(event.key.keysym.sym);
					break;
				case SDL_MOUSEBUTTONDOWN:
					m_inputManager->pressKey(event.button.button);
					break;
				case SDL_MOUSEBUTTONUP:
					m_inputManager->releaseKey(event.button.button);
					break;
				case SDL_MOUSEWHEEL:
					m_inputManager->setMouseScrollwheelPosition(event.wheel.y);
					break;
			}
		}
	}

	void App::exitApp()
	{
		if(m_screenList) {
			m_screenList->getCurrentScreen()->onExit();
			m_screenList.reset(); // Destroy the screenList
		}
		m_isGameRunning = false;
	}

}
