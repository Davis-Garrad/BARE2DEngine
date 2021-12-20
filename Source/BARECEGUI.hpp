#pragma once

#include <GL/glew.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <glm/glm.hpp>
#include <SDL2/SDL_events.h>

namespace BARE2D {

	struct CEGUIContextWrapper {
		CEGUI::OpenGL3Renderer* renderer = nullptr;
		CEGUI::GUIContext* context = nullptr;
		CEGUI::Window* rootWindow = nullptr;
	};

	class BARECEGUI
	{
	public:
		/**
		 * @brief Initializes all of the necessary stuff to use CEGUI!
		 * @param resourceDirectory The directory that all of the resources lie in. Should follow CEGUI's specs.
		 * @param numContexts The number of different contexts to create. Each context has the ability to handle input differently.
		 */
		void init(std::string& resourceDirectory, unsigned int numContexts);
		/**
		 * @brief Frees all necessary memory and unloads resources. Destroys root + children windows.
		 */
		void destroy();
		
		/**
		 * @brief Draws the GUI to the screen over top of what's already there.
		 */
		void draw();
		
		/**
		 * @brief Updates the amount of time passed in CEGUI.
		 */
		void update();
		
		/**
		 * @brief Sets the active context
		 * @param contextIndex The index of the context to activate. Must be less than numContexts from init().
		 */
		void setActiveContext(unsigned int contextIndex);
		
		/**
		 * @brief Sets the image of the mouse cursor.
		 * @param imageFile The file to set the mouse cursor's image from.
		 */
		void setMouseCursor(std::string& imageFile);
		
		/**
		 * @brief Shows/hides the mouse cursor. Useful for cutscenes!
		 * @param shown True = shows the cursor, false = hides it.
		 */
		void setMouseCursorShown(bool shown);
		
		/**
		 * @brief Handles and propagates input.
		 * @param evnt The SDL_Event to add.
		 */
		void handleSDLEvent(SDL_Event& evnt);
		
		/**
		 * @brief Loads a scheme file from resourceDirectory/schemes
		 * @param schemeFile The file to load from
		 */
		void loadScheme(std::string& schemeFile);
		
		/**
		 * @brief Sets the current font to some font.
		 * @param fontFile The file of the font to be loaded.
		 */
		void setFont(std::string& fontFile);
		
		/**
		 * @brief Creates a widget of some type.
		 * @param type The type of window - should generally be "[YourScheme]/[Label,Button,FrameWindow,etc.]". These strings are available in the scheme files.
		 * @param destRectPercent The destination+rectangle of the widget, in terms of percentages of the screen.
		 * @param destRectPixels The destination+rectangle of the widget, in terms of pixels.
		 * @param parent The parent window - defaults to nullptr.
		 * @param name The name of the window - defaults to a unique identifier. Only set this if a pointer of the window cannot be retained/propagated as a handle.
		 * @return A pointer to the new CEGUI::Window - can be casted to some child type generally.
		 */
		CEGUI::Window* createWidget(std::string& type, glm::vec4& destRectPercent, glm::vec4 destRectPixels, CEGUI::Window* parent = nullptr, std::string name = "");
		
		/**
		 * @return The OpenGL3Renderer that the context "owns" 
		 */
		CEGUI::OpenGL3Renderer* getRenderer();
		/**
		 * @return The GUIContext that the context "owns" 
		 */
		CEGUI::GUIContext* getContext();
		
	private:
		static bool m_initialized;
		
		std::vector<CEGUIContextWrapper*> m_contexts;
		unsigned int m_lastTime = 0;
		unsigned int m_activeContext = 0;
	};
	
	CEGUI::Key::Scan SDLKeyToCEGUIKey(SDL_Keycode key);
	CEGUI::MouseButton SDLButtonToCEGUIButton(Uint8 sdlButton);
}

