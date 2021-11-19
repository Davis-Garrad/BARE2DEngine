#pragma once

#include <string>
#include <vector>

namespace BARE2D {
	/**
	* @brief Represents a specific type of error that has occured.
	*/
	enum class BAREError {
		SDL_FAILURE,
		GL_FAILURE_VERSION,
		DOUBLE_INIT,
		GLEW_FAILURE,
		FILE_FAILURE,
		TEXTURE_FAILURE,
		VERTEX_SHADER_FAILURE,
		FRAGMENT_SHADER_FAILURE,
		UNIFORM_NOT_FOUND,
		SHADER_COMPILE_FAILURE,
		SHADER_LINK_FAILURE
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
	
	/**
	 * @brief Throws an error (fatal). Also calls displayErrors and exits the program.
	 * @param err The type of error to throw.
	 */
	extern void throwFatalError(BAREError err);
	
	/**
	 * @brief Throws an error silently. Adds it to the pile.
	 * @param err The error to throw.
	 */
	extern void throwError(BAREError err);
	
	/**
	 * @brief Displays the latest thrown errors (really just all the thrown errors) in the console.
	 */
	extern void displayErrors();
	
	extern std::vector<BAREError> thrownErrors;
}
