#include "LuaScriptEngine.hpp"

#include "LuaScript.hpp"
#include "LuaScriptQueue.hpp"
#include "LuaContextManager.hpp"
#include "LuaFunctions.hpp"

#include "Logger.hpp"

namespace BARE2D {

	LuaScriptEngine::LuaScriptEngine()
	{
	}

	LuaScriptEngine::~LuaScriptEngine()
	{
		// Lua automatically garbage collects.
	}

	void LuaScriptEngine::init(std::string luaModulesPath)
	{
		// Create the master state
		m_masterState = luaL_newstate();
		
		// now load all the standard Lua libraries for the master state
		luaL_openlibs(m_masterState);
		
		// Set the package.path variable for Lua so that extra user-created modules can be loaded in.
		// Put the global variable's name on the stack
		lua_getglobal(m_masterState, "package");
		// Push the path identifier for any and all modules
		lua_pushstring(m_masterState, std::string(luaModulesPath + "/?.lua").c_str());
		// Now set package**.path** instead of just package (combines items on the stack, popping the value - the path in this case)
		lua_setfield(m_masterState, -2, "path");
		// Clean up, popping the whole item.
		lua_pop(m_masterState, 1);
		
		// register the delay() function.
		registerCFunction(LuaFunctions::delay, "delay");
		// register the print() function
		registerCFunction(LuaFunctions::print, "print");
	}

	void LuaScriptEngine::registerModule(std::string filename)
	{
		throwError(BAREError::UNINITIALIZED_FUNCTION, "LuaScriptEngine::registerModule");
	}

	void LuaScriptEngine::registerCFunction(lua_CFunction function, std::string name)
	{
		// Needs to add a C-function to the masterState
		// Push the function to the stack with no closure variables (this is equivalent to lua_pushcclosure(L, func, 0) as stated in the docs
		lua_pushcfunction(m_masterState, function);
		// Pop the function from the stack and create a global with name `name`
		lua_setglobal(m_masterState, name.c_str());
	}
	
	// addValueToRegistry is defined in the LuaScriptEngine_impl.tcc template file.

	void LuaScriptEngine::update()
	{
		// First, update all the contexts which are already running
		LuaContextManager::getInstance()->update();
		
		// Second, convert all new LuaScripts on the queue to LuaContextWrappers
		// Use a for each loop because we're fancy like that
		for(std::pair<unsigned int, LuaScript*> e : LuaScriptQueue::getInstance()->getQueue()) {
			// Create the new context wrapper jazz for a new script to run in
			LuaScriptContextWrapper* context = createLuaContext(e.second);
			
			// Activate it
			context->start();
			
			// Throw it on into the context manager with the ID given before (that's the e.first part.)
			LuaContextManager::getInstance()->addContext(e.first, context);
		}
		// Clear the queue - we've activated all the scripts
		LuaScriptQueue::getInstance()->clearQueue();
	}

	LuaScriptContextWrapper* LuaScriptEngine::createLuaContext(LuaScript* script)
	{
		// Allocate the memory for a new one
		LuaScriptContextWrapper* context = new LuaScriptContextWrapper();
		// Actually initialize it.
		context->init(m_masterState, script);
		
		return context;
	}
	
	lua_State* LuaScriptEngine::getMasterState() {
		return m_masterState;
	}

}
