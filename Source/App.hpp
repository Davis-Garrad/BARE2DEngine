#pragma once

#include <memory>

#include "BAREErrors.hpp"
#include "ScreenList.hpp"

namespace BARE2D
{
	class InputManager;
	class Window;
	
	/**
	 * @class App
	 * @file App.h
	 * @brief The App class embodies the entire application. It controls the GL settings, the window, the screens, input, FPS - in whole, the entire overarching input-output cycle.
	 */
	class App
	{
	public:
		App();
		~App();
		
		/**
		 * @brief Runs the program! Starts the update-draw loop.
		 */
		void run();
		
		/**
		 * @brief Returns the screen list, where the program can add more screens, set entry points, etc.
		 */
		ScreenList* getScreenList();
		
		/**
		 * @return Returns a pointer to the window, so that the client can change its size, title, etc.
		 */
		Window* getWindow();
	
	private:
		bool m_isGameRunning = false;
		bool m_isInited = false;
		
		std::unique_ptr<ScreenList> m_screenList;
		
		InputManager* m_inputManager = nullptr;
		
		Window* m_window = nullptr;

		/**
		 * @brief Initializes the applet and engine. Creates a window, held within this App. Only for internal use.
		 */
		void init();
		
		/**
		 * @brief Updates input, output, etc. Only for internal use.
		 */
		void update();
		
		/**
		 * @brief Draws the current screen, based on that screen's drawing protocol.
		 */
		void draw();
		
		/**
		 * @brief Updates any input, and throws it down the pipeline!
		 */
		void updateInput();
		
		/**
		 * @brief Polls inputs from SDL and updates the inputmanager as appropriate.
		 */
		void pollSDLInput();
		
		/**
		 * @brief Calls the screen's exit function, and then cleans this class up for destruction.
		 */
		void exitApp();
	};

}

