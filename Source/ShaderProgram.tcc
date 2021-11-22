#include "BAREErrors.hpp"

namespace BARE2D {
	template<class T>
	void ShaderProgram::setUniform(const std::string uniform, T data) {
		throwFatalError("Tried calling setUniform with unsupported type: " + std::string(typeid(data).name()));
	}
	
	template<class T>
	void ShaderProgram::setUniformMatrix(const std::string uniform, unsigned int xSize, unsigned int ySize, bool transpose, T* data) {
		throwFatalError("Tried calling setUniformMatrix with unsupported type: " + std::string(typeid(*data).name()));
	}
}
