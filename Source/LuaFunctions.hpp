#pragma once

#include "LuaHeaders.hpp"

namespace BARE2D::LuaFunctions {
	/**
	 * @brief A custom function which calls a lua_yield. Takes one argument, an integer representing how many updates the script should yield for.
	 * @param L The state
	 * @return The number of return values. Always zero.
	 */
	 int delay(lua_State* L);
	 
	 /**
	  * @brief Uses the Logger to print to the screen and log. Takes one argument, a string to print.
	  * @param L The state
	  * @return The number of return values. Always zero.
	  */
	 int print(lua_State* L);
}

