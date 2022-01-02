#pragma once

#include <string>

#include "LuaHeaders.hpp"

namespace BARE2D {

	/**
	 * @class LuaScript
	 * @file LuaScript.hpp
	 * @brief This is the basic Lua script wrapper - it is what the end-user will create and add to the queue. It basically just holds the text that the script will run.
	 */
	class LuaScript
	{
	public:
		LuaScript();
		~LuaScript();
		
		// The script's text - this is the code.
		std::string m_script;
		std::string m_path;
		
		bool inited = false;
	};

	/**
	 * @class LuaScriptContextWrapper
	 * @file LuaScript.hpp
	 * @brief This is not to be used by the end user under any circumstances. This is the class which represents a Lua context that has been initialized with a script's Lua to run. It holds various data, such as a handle to the parent context.
	 */
	class LuaScriptContextWrapper {
	public:
		LuaScriptContextWrapper();
		~LuaScriptContextWrapper();
		
		/**
		 * @brief Creates and initializes all the necessary bits.
		 * @param id The ID of the script, which was assigned from the LuaScriptQueue
		 * @param parentState The masterstate, generally, although I suppose it could be others.
		 */
		void init(lua_State* parentState, LuaScript* script);
		
		/**
		 * @brief Cleans up
		 */
		void destroy();
		
		/**
		 * @brief Starts the script
		 */
		void start();
		
		/**
		 * @brief Updates the script - decreases delay counter, checks if it is finished, etc.
		 */
		void update();
		
		/**
		 * @brief Returns m_completed.
		 */
		bool isCompleted();
		
	protected:
		/**
		 * @brief Loads and compiles the given Lua script. Also, sets m_scriptReference to the index of the compiled script in the registry.
		 * @param luaStr The script to compile.
		 */
		void loadLua(std::string& luaStr);
		
		/**
		 * @brief Creates the m_state variable as a thread, or subroutine of the parent
		 */
		void createThread();
	
		// The state (or context, if you will) that this class represents.
		lua_State* m_state = nullptr;
		// The parent state (or context) that caused this class to be created.
		lua_State* m_parent = nullptr;
		
		// Is the script paused? if so, how long is on the timer?
		bool m_yielded = false;
		unsigned int m_remainingDelay = 0;
		
		// If the script is finished.
		bool m_completed = false;
		
		// This is a reference to the loaded script's place in the registry.
		int m_scriptReference = LUA_REFNIL;
		// This is a reference to the thread in the master state's registry
		int m_threadReference = LUA_REFNIL;
	};

}
