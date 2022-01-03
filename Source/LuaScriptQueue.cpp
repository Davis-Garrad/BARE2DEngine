#include "LuaScriptQueue.hpp"

#include "LuaScript.hpp"

namespace BARE2D {

	LuaScriptQueue* LuaScriptQueue::m_instance = nullptr;
	
	LuaScriptQueue::LuaScriptQueue()
	{
		// Not really anything to do here.
	}

	LuaScriptQueue::~LuaScriptQueue()
	{
		// Nor here, either.
	}

	LuaScriptQueue* LuaScriptQueue::getInstance()
	{
		if(m_instance == nullptr) {
			m_instance = new LuaScriptQueue();
		}
		return m_instance;
	}
	
	void LuaScriptQueue::destroyInstance() {
		if(m_instance) delete m_instance;
	}

	unsigned int LuaScriptQueue::addLuaScript(LuaScript& script)
	{
		// Add the script to the map. (or, in the off chance we have somehow added 4,294,967,295 different scripts in the last update, overwrite this one.)
		LuaScript* scr = new LuaScript();
		*scr = script;
		
		m_scripts[++m_lastUUID] = scr;
		
		return m_lastUUID;
	}
	
	unsigned int LuaScriptQueue::addLuaScript(std::string script) {
		// Create a script object and add it normally
		LuaScript scr;
		scr.m_script = script;
		scr.inited = true;
		
		addLuaScript(scr);
	}

	std::map<unsigned int,LuaScript*>& LuaScriptQueue::getQueue()
	{
		return m_scripts;
	}

	void LuaScriptQueue::clearQueue()
	{
		// First, make sure we actually dispose of the scripts correctly
		for(auto e : m_scripts) {
			delete e.second;
		}
		
		// Just clear the map now. Ez.
		m_scripts.clear();
	}

}
