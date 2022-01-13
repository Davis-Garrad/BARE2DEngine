#include "LuaFunctions.hpp"

#include <string>

#include "Logger.hpp"

namespace BARE2D::LuaFunctions {
	
	int delay(lua_State* L) {
		// The delay duration (the first and only variable) is on the top of the stack. Let's keep it that way so that we can retrieve it from there for the continuation function
		// This will cause the thread to yield until lua_resume is called
		lua_yield(L, 0);
		return 0;
	}
	
	int print(lua_State* L) {
		std::string parameter0 = lua_tostring(L, -1);
		lua_pop(L, 1);
		
		std::string output = "Lua Output: ";
		
		for(char c : parameter0) {
			output += c;
			if(c == '\n')
				output += "Lua Output: ";
		}
		
		Logger::getInstance()->log(output);
		return 0;
	}
}
