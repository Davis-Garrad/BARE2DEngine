#pragma once

#include <functional>

#include "LuaHeaders.hpp"

#include "LuaScript.hpp"
#include "LuaScriptQueue.hpp"

namespace BARE2D {
	
	class LuaScript;
	class LuaScriptContextWrapper;

	/**
	 * @class LuaScriptEngine
	 * @file LuaScriptEngine.hpp
	 * @brief This is the class which actually processes all of the scripts in the script queue, and creates/initializes contexts for them. Takes from LuaScriptQueue and gives to LuaContextManager.
	 */
	class LuaScriptEngine
	{
	public:
		LuaScriptEngine();
		~LuaScriptEngine();
		
		/**
		 * @brief Initializes the LuaScriptEngine - loads basic modules etc.
		 * @param The path to the user-created Lua modules.
		 */
		void init(std::string luaModulesPath);
		
		/**
		 * @brief Loads and registers (read: runs) the module located at the given file
		 * @param filename The file to load/run.
		 */
		void registerModule(std::string filename);
		
		/**
		 * @brief Adds a Lua C Function. This is a function which can be called from inside a Lua script, and executes C/C++ code.
		 * @param function The function which will be called when the Lua script calls the closure. Follows the form of a std::function<int(lua_State*)>. The lua_State pointer provides a handle to the Lua stack (really, the whole state, but the stack is the most important) which allows the C/C++ program to recieve parameters and add return values. Must return the number of values the function gives back to Lua. See https://www.lua.org/manual/5.1/manual.html#lua_CFunction
		 * @param name The name by which the Lua code can call the function.
		 */
		void registerCFunction(lua_CFunction function, std::string name);
		
		/**
		 * @brief Processes all scripts from the LuaScriptQueue and updates all running scripts. That's pretty much it!
		 */
		void update();
		
		/**
		 * @brief Adds a value to the Lua registry - this lets any C/C++ code use the value stored in the state (it is stored in the state)
		 * @param value A pointer to the value to be added.
		 * @param key The key to be used to access the value in the registry.
		 */
		template<class T>
		static void addValueToRegistry(lua_State* L, T* value, std::string key);
		
		template<class T>
		static T* getValueFromRegistry(lua_State* L, std::string key);
		
		/**
		 * @brief Returns a pointer to the master state. 
		 */
		lua_State* getMasterState();
		
	private:
		// Both the script queue and context manager are singletons, so we needn't worry about storing those.
		
		/**
		 * @brief Creates a LuaScriptContextWrapper using the data from script
		 * @param script A pointer to the LuaScript which we want to create a new Lua state for.
		 * @return A pointer to the LuaScriptContextWrapper which the function created.
		 */
		LuaScriptContextWrapper* createLuaContext(LuaScript* script);
		
		// The state which C-functions are loaded into, modules are loaded into, etc. All scripts start as copies of the master state, so they have all of the registry, functions, etc.
		lua_State* m_masterState = nullptr;

	};

}

#include "LuaScriptEngine_impl.tcc"

