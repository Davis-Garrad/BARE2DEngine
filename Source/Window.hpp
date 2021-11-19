#pragma once

#include <SDL2/SDL.h>

#include "BAREErrors.hpp"

namespace BARE2D {

	/**
	 * @class Window
	 * @brief It's a graphical window, holds the contexts for GL and SDL.
	 */
	class Window
	{
	public:
		Window();
		~Window();
		
		/**
		 * @brief This is a graphical window. It holds information about the GL context, as well as the SDL window context. Takes some flags on creation (SDL_WindowFlags):
		 * - SDL_WINDOW_FULLSCREEN
		 * - 			FULLSCREN_DESKTOP
		 * - 			OPENGL
		 * -			VULKAN
		 * -			SHOWN
		 * -			HIDDEN
		 * - 			BORDERLESS
		 * - 			RESIZABLE
		 * - 			MIN/MAXIMIZED
		 * - 			INPUT_GRABBED
		 * - 			INPUT_FOCUS
		 * - 			MOUSE_FOCUS
		 * -			FOREIGN
		 * - 			ALLOW_HIGHDPI
		 * - 			MOUSE_CAPTURE
		 * - 			ALWAYS_ON_TOP
		 * - 			SKIP_TASKBAR
		 * - 			UTILITY
		 * - 			TOOLTIP
		 * - 			POPUP_MENU
		 * These can be ORed together to transfer them to this function
		 * @return Returns an error (if one is created)
		 */
		void create(unsigned int flags);
		
		/**
		 * @brief Sets the title of the window.
		 * @param newTitle The new title to be set!
		 */
		void setTitle(std::string newTitle);
		
		/**
		 * @brief Sets the size of the window (defaults to 600x400)
		 * @param width
		 * @param height
		 */
		void setSize(unsigned int width, unsigned int height);
		
		/**
		 * @brief Swaps the buffer of the SDL window - used to draw to one while the other displays, so no flickering is seen
		 */
		void swapBuffer();
		
		/**
		 * @brief Returns the width of the window 
		 */
		unsigned int getWidth() const;
		
		/**
		 * @brief Returns the height of the window. 
		 */
		unsigned int getHeight() const;
		
	private:
		SDL_Window* m_SDLWindow = nullptr;
		SDL_GLContext m_GLContext = nullptr;
	
		unsigned int m_width = 600, m_height = 400;
		std::string m_title = "BARE2D Window";
	};
}

