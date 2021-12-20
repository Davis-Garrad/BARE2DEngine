#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

namespace BARE2D {
	
	/**
	 * @class InputManager
	 * @brief This is the input manager. It does what you expect! Nearly completely copied from GLEngine, the ol' gal.
	 */
	class InputManager
	{
	public:
		InputManager();
		~InputManager();
		
		/**
		 * @brief Updates the inputmanager. Should be called every frame.
		 */
		void update();
		
		/**
		 * @brief Sets a key as 'pressed'
		 * @param keyID The id given for a key by SDL
		 */
		void pressKey(unsigned int keyID);
		
		/**
		 * @brief Sets a key as 'released'
		 * @param keyID The id given for a key by SDL
		 */
		void releaseKey(unsigned int keyID);
		
		/**
		 * @brief Sets the mouse position to (x,y)
		 * @param x A float to represent x position
		 * @param y A float to represent y position
		 */
		void setMousePosition(float x, float y);
		
		/**
		 * @brief Sets the mouse position to 'position'
		 * @param position The position to set it to.
		 */
		void setMousePosition(glm::vec2 position);
		
		/**
		 * @brief Sets the "position" of the scrollwheel - essentially, how much it has moved since the last frame
		 * @param position The distance it has moved since last update.
		 */
		void setMouseScrollwheelPosition(int position);
		
		/**
		 * @brief Checks if the key is down at all
		 * @param keyID The SDL-given ID to check against
		 * @return true if the key is down
		 */
		bool isKeyDown(unsigned int keyID) const;
		
		/**
		 * @brief Checks if the key has just been pressed
		 * @param keyID The SDL-given ID to check against
		 * @return true if the key wasn't down last frame and is this frame. false otherwise
		 */
		bool isKeyPressed(unsigned int keyID) const;
		
		/**
		 * @brief Gets the position of the mouse in the window
		 * @return The position of the mouse in a glm::vec2
		 */
		glm::vec2 getMousePosition() const;
		
		/**
		 * @brief Gets the position of the mousewheel
		 * @return How much the mousewheel has moved since last update.
		 */
		int getMouseScrollwheelPosition() const;
		
	private:
		/**
		 * @brief Checks if the key was down last frame
		 * @param keyID The SDL-given ID to check against
		 * @return true if the key was down last frame, false otherwise.
		 */
		bool wasKeyDown(unsigned int keyID) const;
		
		std::unordered_map<unsigned int, bool> m_keyMap;
		std::unordered_map<unsigned int, bool> m_previousKeyMap;
		glm::vec2 m_mousePosition;
		int m_mouseScrollwheelPosition = 0;
		
	};

}

