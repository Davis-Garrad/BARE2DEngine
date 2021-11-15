#pragma once

#include <string>

namespace BARE2D {
	/**
	* @brief Represents a specific type of error that has occured.
	*/
	enum class BAREError {
		NONE,
		SDL_FAILURE,
		GL_FAILURE_VERSION,
		DOUBLE_INIT,
		GLEW_FAILURE
	};
	
	/**
	 * @brief Returns the string representing/explaining the error that occurred.
	 * @param err The error enum, which a function returns.
	 * @return The representative string.
	 */
	extern std::string getErrString(BAREError err);
	
	/**
	 * @brief Throws an error message, printing a message directly into the terminal (bypassing the logger). Ends the program.
	 * @param message The message to print.
	 */
	extern void throwFatalError(std::string message);
}
