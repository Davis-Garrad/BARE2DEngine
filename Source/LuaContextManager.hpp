#pragma once

#include <map>

namespace BARE2D {

	class LuaScriptContextWrapper;
	
	/**
	 * @class LuaContextManager
	 * @file LuaContextManager.hpp
	 * @brief NOTE: This is a singleton class. The LuaContextManager, well, manages the Lua Contexts which the ScriptEngine has created. These, generally, are scripts which are running. This class simply updates them and handles delay functions and the like.
	 */
	class LuaContextManager
	{
	public:
		static LuaContextManager* getInstance();
		static void destroyInstance();

		/**
		 * @brief Updates all of the context wrappers, pausing, removing (if finished), or resuming them as is correct.
		 */
		void update();
		
		/**
		 * @brief Adds a context wrapper to the map.
		 * @param id The ID that the ScriptQueue gave the script all those cycles ago
		 * @param context The context to insert in the map.
		 */
		void addContext(unsigned int id, LuaScriptContextWrapper* context);

	private:
		LuaContextManager();
		~LuaContextManager();
		
		static LuaContextManager* m_instance;

		/**
		 * @brief Removes a context wrapper from the map
		 * @param id The ID of the context to remove from the map.
		 */
		void removeContext(unsigned int id);

		// All of the scripts
		std::map<unsigned int, LuaScriptContextWrapper*> m_contexts;

	};

}

