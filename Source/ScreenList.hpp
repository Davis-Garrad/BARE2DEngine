#pragma once

#include <vector>

namespace BARE2D
{
	class Screen;
	
	/**
	 * @class ScreenList
	 * @brief Holds and connects all of the screens used in the program in a list. Keeps track of the previous screen. Contains functions to move to the next or previous screens.
	 */
	class ScreenList
	{
	public:
		ScreenList();
		
		/**
		 * @brief Destroys the screen list, "taking care" of the screen pointers it owns.
		 * @param screen
		 */
		~ScreenList();
		
		/**
		 * @brief Adds a screen to the list of screens, AKA the screen list. Requires non-nullptr. Also, calls the screen's initScreen function
		 * @param screen A pointer to the screen to be added.
		 */
		void addScreen(Screen* screen);
		
		/**
		 * @brief Adds a screen, and sets the current screen to this one.
		 * @param screen A pointer to the entry screen.
		 */
		void addEntryScreen(Screen* screen);
		
		/**
		 * @brief Moves to the next screen, updates needed variables. Also, exits old screen and enters new one.
		 */
		void moveToNextScreen();
		
		/**
		 * @brief Moves to the previous screen. Similar to moveToNextScreen, in that it makes sure everything's good!
		 */
		void moveToPreviousScreen();
		
		/**
		 * @return The current screen.
		 */
		Screen* getCurrentScreen();
		
	private:
		std::vector<Screen*> m_screens;
		Screen* m_previousScreen = nullptr;
		Screen* m_currentScreen = nullptr;

	};

}

