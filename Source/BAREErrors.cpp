#include "BAREErrors.hpp"

#include <iostream>
#include <iomanip>
#include <csignal>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <cxxabi.h>
#include <typeinfo>
#include <memory>
#include <cstdlib>

#include "Logger.hpp"

std::string demangle(const char* mangled)
{
	int status;
	std::unique_ptr<char[], void (*)(void*)> result(
	    abi::__cxa_demangle(mangled, 0, 0, &status), std::free);
	return result.get() ? std::string(result.get()) : "error occurred";
}

void GLAPIENTRY MessageCallback(GLenum source,
                                GLenum type,
                                GLuint id,
                                GLenum severity,
                                GLsizei length,
                                const GLchar* message,
                                const void* userParam)
{
	std::string severityStr = "Unspecified";
	BARE2D::GLErrorSeverity severityEnum = BARE2D::GLErrorSeverity::UNKNOWN;
	switch(severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			severityStr = "High (UB)";
			severityEnum = BARE2D::GLErrorSeverity::HIGH;
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			severityStr = "Medium (Performance, deprecated)";
			severityEnum = BARE2D::GLErrorSeverity::MED;
			break;
		case GL_DEBUG_SEVERITY_LOW:
			severityStr = "Low (performance generally)";
			severityEnum = BARE2D::GLErrorSeverity::LOW;
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			severityStr = "Notification";
			severityEnum = BARE2D::GLErrorSeverity::NOTIF;
			break;
		default:
			severityStr = "Unspecified";
			break;
	}

	if((unsigned int)severityEnum < (unsigned int)BARE2D::GLErrorMinSeverity) return;

	std::string sourceStr = "Unspecified";
	switch(source) {
		case GL_DEBUG_SOURCE_API:
			sourceStr = "OpenGL API";
			break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			sourceStr = "Window System";
			break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			sourceStr = "Shader Compiler";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			sourceStr = "Assoc. Application";
			break;
		case GL_DEBUG_SOURCE_APPLICATION:
			sourceStr = "Application User";
			break;
		case GL_DEBUG_SOURCE_OTHER:
			sourceStr = "Other";
			break;
		default:
			sourceStr = "Unspecified";
			break;
	}

	std::string typeStr = "Unspecified";
	switch(type) {
		case GL_DEBUG_TYPE_ERROR:
			typeStr = "Error";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			typeStr = "Deprecated Behaviour";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			typeStr = "Undefined Behaviour";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			typeStr = "Portability Concern";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			typeStr = "Performance Issue";
			break;
		case GL_DEBUG_TYPE_MARKER:
			typeStr = "Command Stream Annotation";
			break;
		case GL_DEBUG_TYPE_PUSH_GROUP:
			typeStr = "Group Pushing";
			break;
		case GL_DEBUG_TYPE_POP_GROUP:
			typeStr = "Documented as 'foo'";
			break;
		case GL_DEBUG_TYPE_OTHER:
			typeStr = "Other";
			break;
		default:
			typeStr = "Unspecified";
			break;
	}

	std::string errorString = "GL Callback: " + std::string(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "") + "\n";
	errorString += "Type: " + typeStr + "\n";
	errorString += "Severity: " + severityStr + "\n";
	errorString += "Message: " + std::string(message) + "\n";

	BARE2D::Logger::getInstance()->log(errorString);

	/*fprintf(stderr, "GL Callback: %s \nType: %s \nSeverity: %s \nMessage: %s\n\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		typeStr.c_str(),
		severityStr.c_str(),
		message);*/

}

namespace BARE2D
{
	GLErrorSeverity GLErrorMinSeverity = GLErrorSeverity::NOTIF;

	std::vector<BAREError> thrownErrors;

	std::string getErrString(BAREError err)
	{
		switch(err) {
			case BAREError::SDL_FAILURE:
				return "EC SDL_FAILURE - SDL Failure to initialize. SDL_GetError() yields the following: \n\n" + std::string(SDL_GetError());
			case BAREError::DOUBLE_INIT:
				return "EC DOUBLE_INIT - There was an attempted double-initialization in the program. Not too serious, but fix it anyways, nerd.";
			case BAREError::GLEW_FAILURE:
				return "EC GLEW_FAILURE - GLEW could not be initialized!";
			case BAREError::GL_FAILURE_VERSION:
				return "EC GL_FAILURE_VERSION - GL Version is not good enough.";
			case BAREError::TEXTURE_FAILURE:
				return "EC TEXTURE_FAILURE - Texture could not be loaded from file or created.";
			case BAREError::VERTEX_SHADER_FAILURE:
				return "EC VERTEX_SHADER_FAILURE";
			case BAREError::FRAGMENT_SHADER_FAILURE:
				return "EC FRAGMENT_SHADER_FAILURE";
			case BAREError::UNIFORM_NOT_FOUND:
				return "EC UNIFORM_NOT_FOUND";
			case BAREError::SHADER_COMPILE_FAILURE:
				return "EC SHADER_COMPILE_FAILURE";
			case BAREError::SHADER_LINK_FAILURE:
				return "EC SHADER_LINK_FAILURE";
			case BAREError::GLSL_PROGRAM_FAILURE:
				return "EC GLSL_PROGRAM_FAILURE";
			case BAREError::FONT_FAILURE:
				return "EC FONT_FAILURE";
			case BAREError::FBO_FAILURE:
				return "EC FBO_FAILURE";
			case BAREError::LOGGER_FAILURE:
				return "EC LOGGER_FAILURE";
			case BAREError::XML_FAILURE:
				return "EC XML_FAILURE";
			case BAREError::UNINITIALIZED_FUNCTION:
				return "EC UNINITIALIZED_FUNCTION";
			case BAREError::LUA_FAILURE:
				return "EC LUA_FAILURE";
			default:
				return "EC DNE - Unknown error. (enum " + std::to_string((unsigned int)err) + ")";
		}
	}

	void throwFatalError(BAREError err, std::string message)
	{
		std::cout << "\n";
		std::cout << std::setfill('#') << std::setw(50) << "\n";
		std::cout << "FATAL ERROR: " << "\n";
		std::cout << std::setfill('#') << std::setw(50) << "\n\n";
		throwError(err, message);
		displayErrors();
		std::raise(SIGABRT);
		exit(EXIT_FAILURE);
	}

	void throwError(BAREError err, std::string message)
	{
		thrownErrors.push_back(err);
		// We use std::cout just in case the Logger never actually got inited.
		if(message != "") {
			std::cout << std::setfill('-') << std::setw(50) << "\n";
			std::cout << "Error: " << message << std::endl;
			std::cout << thrownErrors.size() - 1 << ": " << getErrString(err) << std::endl;
			std::cout << std::setfill('-') << std::setw(50) << "\n";
		}
	}

	void displayErrors()
	{
		std::cout << std::endl << "Thrown Errors: " << std::endl;
		std::cout << std::setfill('-') << std::setw(50) << "\n";
		for(unsigned int i = 0; i < thrownErrors.size(); i++) {
			std::cout << i << ": " << getErrString(thrownErrors[i]) << std::endl;
			std::cout << std::setfill('-') << std::setw(50) << "\n";
		}
		thrownErrors.clear();
	}

	void initGLErrorCallback(GLErrorSeverity minSeverity)
	{
		GLErrorMinSeverity = minSeverity;

		GLboolean inited = GL_FALSE;
		glGetBooleanv(GL_DEBUG_OUTPUT, &inited);

		if(!inited) {
			glEnable(GL_DEBUG_OUTPUT);
			glDebugMessageCallback(MessageCallback, 0);
		}
	}
}
