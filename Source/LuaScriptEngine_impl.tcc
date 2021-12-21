#pragma once

#include <string>

#include "BAREErrors.hpp"

namespace BARE2D {
	
	template<class T>
	void LuaScriptEngine::addValueToRegistry(lua_State* L, T* value, std::string key) {
		// Push the key
		lua_pushstring(L, key.c_str());
		// Push the data (as a void*)
		lua_pushlightuserdata(L, static_cast<void*>(value));
		// Combine name and key in the registry.
		lua_settable(L, LUA_REGISTRYINDEX);
	}
	
	template<class T>
	T* LuaScriptEngine::getValueFromRegistry(lua_State* L, std::string key) {
		// Put the key on the stack
		lua_pushstring(L, key.c_str());
		// Get the element at key in tge registry table
		lua_gettable(L, LUA_REGISTRYINDEX);
		// Turn the element into a void*
		void* ret = lua_touserdata(L, -1);
		lua_pop(L, 1);
		// convert to whatever type
		return static_cast<T*>(ret);
	}
	
}
