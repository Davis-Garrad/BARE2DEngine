#pragma once

#include <map>

namespace BARE2D {

	class LuaScript;
	
	/**
	 * @class LuaScriptQueue
	 * @file LuaScriptQueue.hpp
	 * @brief This class essentially just collects all of the scripts that need to be run from all the various end-user sources in a single update loop, and then "reports them" to the LuaScriptEngine, who actually runs them. Note that this is a singleton class.
	 */
	class LuaScriptQueue
	{
	public:
		/**
		 * @brief Returns a pointer to the singleton object - creates the object if one doesn't already exist.
		 * @return A pointer to the LuaScriptQueue.
		 */
		static LuaScriptQueue* getInstance();
		/**
		 * @brief Destroys the singleton
		 */
		static void destroyInstance();
		
		/**
		 * @brief Adds a script to the queue to be run.
		 * @param script A reference to the LuaScript to add to the queue.
		 * @return An unsigned int which represents the UUID of the script added. This UUID will persist throughout all of the pipeline.
		 */
		unsigned int addLuaScript(LuaScript& script);
		
		/**
		 * @brief Adds a script to the queue to be run by its source code.
		 * @param script The code to run.
		 * @return An unsigned int which represents the UUID of the script added. This UUID will persist throughout all of the pipeline
		 */
		unsigned int addLuaScript(std::string script);
		
		/**
		 * @brief Returns the queue of scripts to activate
		 * @return A reference to m_scripts.
		 */
		std::map<unsigned int, LuaScript*>& getQueue();
		
		/**
		 * @brief Clears the stored script queue - for regular use by tbe Script Engine. Deallocates memory that was in use in the m_scripts map.
		 */
		void clearQueue();
		
	private:
		LuaScriptQueue();
		~LuaScriptQueue();
		
		// The singleton object.
		static LuaScriptQueue* m_instance;
		
		// All of the scripts to be run. We use an ordered map so that we can store both the UUID and script together.
		std::map<unsigned int, LuaScript*> m_scripts;
		
		// The "counter" we're on for our UUIDs (I know, I know - not a 'true' UUID. It works though, doesn't it?) - set to -1 initially so our first script is 0
		unsigned int m_lastUUID = -1;

	};

}

