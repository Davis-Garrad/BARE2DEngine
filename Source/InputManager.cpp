#include "InputManager.hpp"

namespace BARE2D {

	InputManager::InputManager()
	{
		
	}

	InputManager::~InputManager()
	{
		
	}

	void InputManager::update()
	{
		// Update the previous keymap
		for(auto& iterator : m_keyMap) {
			m_previousKeyMap[iterator.first] = iterator.second;
		}
		
		// As this is essentially the \delta mouseScrollWheel variable, it needs to be set to zero each update
		m_mouseScrollwheelPosition = 0;
	}

	void InputManager::pressKey(unsigned int keyID)
	{
		// True represents pressed
		m_keyMap[keyID] = true;
	}

	void InputManager::releaseKey(unsigned int keyID)
	{
		// False represents released
		m_keyMap[keyID] = false;
	}

	void InputManager::setMousePosition(float x, float y)
	{
		m_mousePosition.x = x;
		m_mousePosition.y = y;
	}

	void InputManager::setMousePosition(glm::vec2 position)
	{
		m_mousePosition = position;
	}

	void InputManager::setMouseScrollwheelPosition(int position)
	{
		m_mouseScrollwheelPosition = position;
	}

	bool InputManager::isKeyDown(unsigned int keyID) const
	{
		// We dont want to use the associative array approach here
		// because we don't want to create a key if it doesnt exist.
		// So we do it manually
		auto it = m_keyMap.find(keyID);
		if (it != m_keyMap.end()) {
			// Found the key
			return it->second;
		} else {
			// Didn't find the key
			return false;
		}
	}

	bool InputManager::isKeyPressed(unsigned int keyID) const
	{
		// Should return true if it is pressed now and wasn't before.
		return (isKeyDown(keyID) && !wasKeyDown(keyID));
	}

	glm::vec2 InputManager::getMousePosition() const
	{
		return m_mousePosition;
	}

	int InputManager::getMouseScrollwheelPosition() const
	{
		return m_mouseScrollwheelPosition;
	}

	bool InputManager::wasKeyDown(unsigned int keyID) const
	{
		// We dont want to use the associative array approach here
		// because we don't want to create a key if it doesnt exist.
		// So we do it manually
		auto it = m_previousKeyMap.find(keyID);
		if (it != m_previousKeyMap.end()) {
			// Found the key
			return it->second;
		} else {
			// Didn't find the key
			return false;
		}
	}

}
