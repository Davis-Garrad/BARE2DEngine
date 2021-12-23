#include "LuaContextManager.hpp"

#include "BAREErrors.hpp"

#include "LuaScript.hpp"

namespace BARE2D {

	LuaContextManager* LuaContextManager::m_instance = nullptr;

	LuaContextManager::LuaContextManager()
	{
		// Not much to do here
	}

	LuaContextManager::~LuaContextManager()
	{
		// Nor here.
	}

	LuaContextManager* LuaContextManager::getInstance()
	{
		if (m_instance == nullptr) {
			m_instance = new LuaContextManager();
		}
		return m_instance;
	}
	
	void LuaContextManager::destroyInstance() {
		if(m_instance) delete m_instance;
	}

	void LuaContextManager::update()
	{
		// We need to loop through all of the contexts and update them each. As well, we need to check if any are completed. If they are, remove and destroy them.
		std::vector<unsigned int> completedScripts;
		
		for(auto it : m_contexts) {
			// Update it
			it.second->update();
			if(it.second->isCompleted()) {
				// If it is done, release resources and remove it from the list.
				it.second->destroy();
				completedScripts.push_back(it.first);
			}
		}
		
		for(unsigned int i : completedScripts) {
			delete m_contexts[i];
			m_contexts.erase(i);
		}
	}

	void LuaContextManager::addContext(unsigned int id, LuaScriptContextWrapper* context)
	{
		// Just add the pair to the map
		m_contexts.insert(std::make_pair(id, context));
	}

	void LuaContextManager::removeContext(unsigned int id)
	{
		// Find the context in the map, delete it, and then remove it from the map
		// Find the context
		auto it = m_contexts.find(id);
		// Check to make sure it exists
		if(it == m_contexts.end()) {
			throwError(BAREError::LUA_FAILURE, "LuaContextManager attempted to remove nonexistent script with ID " + std::to_string(id));
			return;
		}
		
		// The element exists - we need to delete it and remove it from the map
		// delete it
		delete it->second;
		// remove from the map
		m_contexts.erase(it);
		
		// And we're good! Just return.
	}

}
