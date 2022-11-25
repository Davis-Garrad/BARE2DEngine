#include "ScreenList.hpp"

#include "Screen.hpp"

namespace BARE2D {

	ScreenList::ScreenList()
	{
	}

	ScreenList::~ScreenList()
	{
		for(unsigned int i = 0; i < m_screens.size(); i++) {
			m_screens[i]->destroyScreen();
			delete m_screens[i];
		}
		m_currentScreen = nullptr;
		m_previousScreen = nullptr;
	}

	void ScreenList::addScreen(Screen* screen)
	{
		screen->initScreen();
		m_screens.push_back(screen);
	}

	void ScreenList::addEntryScreen(Screen* screen)
	{
		m_currentScreen = screen;
		addScreen(screen);
	}

	void ScreenList::moveToNextScreen()
	{
		// Make sure we don't do something dumb.
		if(m_currentScreen) {
			if((long unsigned int)m_currentScreen->getNextScreenIndex() < m_screens.size()) {
				// Exit the current screen
				m_currentScreen->onExit();
				
				// Move to the next
				m_currentScreen = m_screens[m_currentScreen->getNextScreenIndex()];
				
				// Enter the next
				m_currentScreen->onEntry();
			}
		}
	}

	void ScreenList::moveToPreviousScreen()
	{
		// Make sure we don't do dumb stuff
		if(m_previousScreen) {
			// Take a temporary variable to swap this and the previous screen.
			Screen* prev = m_currentScreen;
			
			// Exit this one
			m_currentScreen->onExit();
			
			// Move to previous, set the new previous
			m_currentScreen = m_previousScreen;
			m_previousScreen = prev;
			
			// Enter previous
			m_currentScreen->onEntry();
		}
	}
	
	Screen* ScreenList::getCurrentScreen() {
		return m_currentScreen;
	}

}
