#pragma once

#include <typeinfo>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "BAREErrors.hpp"

namespace BARE2D {
	template<class T>
	void ShaderProgram::setUniform(const std::string uniform, T* data, unsigned int num) {
		throwFatalError(BAREError::GLSL_PROGRAM_FAILURE, "Tried calling setUniform with unsupported type: " + demangle(typeid(*data).name()));
	}
	
	template<class T>
	void ShaderProgram::setUniformMatrix(const std::string uniform, bool transpose, T* data, unsigned int num) {
		throwFatalError(BAREError::GLSL_PROGRAM_FAILURE, "Tried calling setUniformMatrix with unsupported type: " + demangle(typeid(*data).name()));
	}
	
	// Template specialization declarations
	
	template<>
	void ShaderProgram::setUniform<int>(const std::string uniform, int* data, unsigned int num);
	template<>
	void ShaderProgram::setUniform<unsigned int>(const std::string uniform, unsigned int* data, unsigned int num);
	template<>
	void ShaderProgram::setUniform<float>(const std::string uniform, float* data, unsigned int num);
	template<>
	void ShaderProgram::setUniform<glm::vec2>(const std::string uniform, glm::vec2* data, unsigned int num);
	template<>
	void ShaderProgram::setUniform<glm::vec3>(const std::string uniform, glm::vec3* data, unsigned int num);
	template<>
	void ShaderProgram::setUniform<glm::vec4>(const std::string uniform, glm::vec4* data, unsigned int num) ;
	template<>
	void ShaderProgram::setUniform<glm::ivec2>(const std::string uniform, glm::ivec2* data, unsigned int num) ;
	template<>
	void ShaderProgram::setUniform<glm::ivec3>(const std::string uniform, glm::ivec3* data, unsigned int num);
	template<>
	void ShaderProgram::setUniform<glm::ivec4>(const std::string uniform, glm::ivec4* data, unsigned int num) ;
	template<>
	void ShaderProgram::setUniformMatrix<glm::mat4>(const std::string uniform, bool transpose, glm::mat4* data, unsigned int num);
}
