#include "LuaScript.hpp"

#include "BAREErrors.hpp"

namespace BARE2D {

	LuaScript::LuaScript()
	{
	}

	LuaScript::~LuaScript()
	{
	}

	LuaScriptContextWrapper::LuaScriptContextWrapper()
	{
	}

	LuaScriptContextWrapper::~LuaScriptContextWrapper()
	{
		
	}

	void LuaScriptContextWrapper::init(lua_State* parentState, LuaScript* script)
	{
		// Set the parent state.
		m_parent = parentState;
		
		// Create the self's state, which is actually just a subroutine of the main.
		createThread();
		
		// Load and compile the script, saving it for later.
		loadLua(script->m_script);
	}
	
	void LuaScriptContextWrapper::createThread() {
		// Create the thread, as a subroutine of the parent - the master state/thread.
		m_state = lua_newthread(m_parent);
		// Push the state to the registry of the parent, and return the index
		m_threadReference = luaL_ref(m_parent, LUA_REGISTRYINDEX);
		
		// Make sure that we have no errors.
		if(m_threadReference == LUA_REFNIL) {
			m_state = nullptr;
			throwError(BAREError::LUA_FAILURE, "Failed to create Lua thread");
		}
	}
	
	void LuaScriptContextWrapper::destroy() {
		m_completed = true;
		if(m_state) {
			// Clean the stack
			lua_settop(m_state, 0);
			// close and clean the thread
			lua_close(m_state);
			m_state = nullptr;
		}
	}

	void LuaScriptContextWrapper::start()
	{
		// To start a Lua script, we need to call lua_callk to allow yielding.
		
		// First, to call lua_callk, we need to push the function (which we earlier stored in the registry) to the stack.
		// Adds registry[m_scriptReference] to the stack.
		lua_rawgeti(m_state, LUA_REGISTRYINDEX, m_scriptReference);
		
		// Then push arguments (of which there are none because it's just an entire script)
	
		// Now actually call the function, starting the script.
		int nargs = 0;
		// This actually runs the script as a coroutine, so it can be yielded, etc.
		int errorCode = lua_resume(m_state, nullptr, nargs);
		
		// Check if there were any errors
		if(errorCode != LUA_OK && errorCode != LUA_YIELD) {
			// There is some error. Throw, and use lua_tostring to get the error string.
			throwError(BAREError::LUA_FAILURE, "Failed to run Lua script: Lua reports: Error code " + std::to_string(errorCode) + " - \'" + lua_tostring(m_state, -1));
			return; // we're done here.
		}
	}

	void LuaScriptContextWrapper::update()
	{
		// Check if the function is already being delayed
		if(m_yielded) {
			// Check if there's still a delay left or if we should resume.
			if(m_remainingDelay <= 0) {
				// No delay left, set flags to false and resume
				m_yielded = false;
				// Because there was no true "coroutine," it is okay to pass nullptr as the "from" parameter.
				// Otherwise, resumes the script and replaces exactly 0 things on the stack.
				lua_resume(m_state, nullptr, 0);
			} else {
				// If we still have delay left, just decrement.
				m_remainingDelay--;
			}
		} else {
			// The function is not yielded (!)as far as we know(!)
			// Check to make sure of this
			int status = lua_status(m_state);
			
			// May as well check for errors
			if(status != LUA_OK && status != LUA_YIELD) {
				// Error occurred!
				throwError(BAREError::LUA_FAILURE, "Lua script crashed partway through!");
				destroy();
				return;
			} else if(status == LUA_YIELD) {
				// If the status is LUA_YIELD, then its obviously yielded. Obviously the C-side of things doesn't know this yet
				// So set the stuff we needed to.
				m_yielded = true;
				// Get the first thing on the stack - the delay() variable.
				m_remainingDelay = lua_tointeger(m_state, -1);
				// And remove from the stack.
				lua_pop(m_state, 1);
			} else if(status == LUA_OK) {
				// This means that the thread is completed
				m_completed = true;
			}
		}
	}
	
	void LuaScriptContextWrapper::loadLua(std::string& luaStr) {
		// Load the string and collect any error code. Note that this loads the script and pushes it to the stack.
		int errorCode = luaL_loadstring(m_state, (char*)luaStr.c_str());
		
		// Check the error.
		if(errorCode != LUA_OK) {
			// There is some error. Throw, and use lua_tostring to get the error string.
			throwError(BAREError::LUA_FAILURE, "Failed to compile Lua string: Lua reports: Error code " + std::to_string(errorCode) + " - \'" + lua_tostring(m_state, -1) + "\'\n\n" + luaStr + "\n\n");
			// At this point it makes no sense to set the script reference, as the script... doesn't exist.
			return; // we're done here.
		}
		
		// Now that we've loaded and compiled the script, we need to push it to the registry.
		// This is a short form of popping from the stack, storing it in the registry, and returning the key.
		int reference = luaL_ref(m_state, LUA_REGISTRYINDEX);
		// Set the reference to the index in the registry.
		m_scriptReference = reference;
	}
	
	bool LuaScriptContextWrapper::isCompleted() {
		return m_completed;
	}

}
