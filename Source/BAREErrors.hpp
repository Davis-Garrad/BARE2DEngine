#pragma once

#include <string>
#include <vector>

/// PLEASE NOTE THAT IF MINGW BREAKS, THIS IS PROBABLY WHY
/**
 * @brief De-mangles a typeid.name() return value
 * @param mangled The mangled typeid.name() return value
 * @return A demangled version of mangled.
 */
extern std::string demangle(const char* mangled);

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
		SHADER_LINK_FAILURE,
		GLSL_PROGRAM_FAILURE,
		FONT_FAILURE,
		FBO_FAILURE,
		LOGGER_FAILURE,
		XML_FAILURE,
		UNINITIALIZED_FUNCTION,
		LUA_FAILURE,
		SDL_MIXER_FLAC_FAILURE,
		SDL_MIXER_OGG_FAILURE,
		SDL_MIXER_MP3_FAILURE,
		SDL_MIXER_MOD_FAILURE,
		SDL_MIXER_CLOSE_FAILURE,
		SDL_MIXER_LOAD_FAILURE,
		SDL_MIXER_SOUND_FAILURE,
		NULL_PTR_ACCESS,
		OTHER_ERROR,
		CACHE_FAILURE
	};

	enum class GLErrorSeverity { NOTIF, LOW, MED, HIGH, UNKNOWN };

	extern GLErrorSeverity GLErrorMinSeverity;

	/**
	 * @brief Returns the string representing/explaining the error that occurred.
	 * @param err The error enum, which a function returns.
	 * @return The representative string.
	 */
	extern std::string getErrString(BAREError err);

	/**
	 * @brief Throws an error (fatal). Also calls displayErrors and exits the program.
	 * @param err The type of error to throw.
	 * @param message (Optional) The message to display along with the error.
	 */
	extern void throwFatalError(BAREError err, std::string message = "");

	/**
	 * @brief Throws an error silently. Adds it to the pile.
	 * @param err The error to throw.
	 * @param message (Optional) The message to display along with the error.
	 */
	extern void throwError(BAREError err, std::string message = "");

	/**
	 * @brief Displays the latest thrown errors (really just all the thrown errors) in the console.
	 */
	extern void displayErrors();

	/**
	 * @brief Initializes the GL Debug Message Callback function, and enables debug output straight from OpenGL
	 */
	extern void initGLErrorCallback(GLErrorSeverity minSeverity = GLErrorSeverity::NOTIF);

	extern std::vector<BAREError> thrownErrors;
} // namespace BARE2D
