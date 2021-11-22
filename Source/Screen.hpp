#pragma once

namespace BARE2D {
	
	enum class ScreenState {
		RUNNING,
		CHANGE_NEXT,
		CHANGE_PREV,
		EXIT_APPLICATION
	};
	
	/**
	 * @class Screen
	 * @brief This is meant to be a parent for other, app-specific, screen classes, which is essentially where all game mechanics will "happen", so to speak. This class decides what happens on updates, draws, when to go to different screens, etc.
	 */
	class Screen
	{
	public:
		Screen();
		~Screen();
		
		/**
		 * @brief This is called once, at the start of the program, when the screen is added to the screen list.
		 */
		virtual void initScreen() = 0;
		
		/**
		 * @brief Destroys the screen, called when the screen list is destroyed.
		 */
		virtual void destroyScreen() = 0;
		
		/**
		 * @brief This is pretty close to the init function. It is called every time the screen is entered.
		 */
		virtual void onEntry() = 0;
		
		/**
		 * @brief This is close to the destroy function, but is only called when the screen is exited, not at the end of the program.
		 */
		virtual void onExit() = 0;
		
		/**
		 * @brief Draws anything and everything to the screen!
		 */
		virtual void draw() = 0;
		
		/**
		 * @brief Updates all necessary things!
		 */
		virtual void update(double dt) = 0;
		
		/**
		 * @brief Returns the index of the next screen. It is recommended to keep a file, say, ScreenIndices.h, where all indices are defined.
		 * @return Index of the next screen
		 */
		virtual unsigned int getNextScreenIndex() = 0;
		
		/**
		 * @return Returns the current ScreenState 
		 */
		ScreenState getState();
	
	protected:
		ScreenState m_screenState = ScreenState::RUNNING;
		
		
	};

}

