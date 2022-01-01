#pragma once

#include <string>
#include <initializer_list>

#include <GL/glew.h>

namespace BARE2D {

	/**
	 * @class ShaderProgram
	 * @brief The ShaderProgram is a GLSL program which combines two shaders - the vertex shader and the fragment shader - to allow rendering. Each renderer should have its own program.
	 */
	class ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();
		
		/**
		 * @brief Compiles the shaders. Does not link them.
		 * @param vertexShaderPath The path to the vertex shader
		 * @param fragmentShaderPath The path to the fragment shader.
		 */
		void compileShaders(const char* vertexShaderPath, const char* fragmentShaderPath);
		
		/**
		 * @brief Similar to compileShaders, this just compiles the shaders.
		 * @param vertexSource The source code for the vertex shader
		 * @param fragmentSource The source code for the fragment shader
		 */
		void compileShadersFromSource(const char* vertexSource, const char* fragmentSource);
		
		/**
		 * @brief Links the compiled shaders together to create a coherent shader program
		 * @param attributes An initializer_list of std::string type of attributes to add to the program. These must link up with the renderer used to draw with this program.
		 */
		void linkShaders(std::initializer_list<std::string> attributes);
		
		/**
		 * @brief A generalized wrapper to find and set a uniform for this shader.
		 * @param uniform The name of the uniform in the shader
		 * @param data The variable to actually set the uniform's value to. This can be a glm::{i,ui,f}vec{1,2,3,4}, an unsigned int, an int, or a float
		 */
		template<class T>
		void setUniform(const std::string uniform, T& data);
		
		/**
		 * @brief Similar to setUniform.
		 * @param uniform The name of the uniform in the shader
		 * @param transpose Should the matrix be transposed when converted? If false, each matrix is assumed to be supplied in column major order. Else, row major order
		 * @param data A pointer to the matrix, which is a 1D array of floats, ints, or unsigned ints.
		 */
		template<class T>
		void setUniformMatrix(const std::string uniform, bool transpose, T& data);
		
		/**
		 * @param uniform The uniform to check for
		 * @return True if the uniform is in the compiled shader program, false otherwise.
		 */
		bool doesUniformExist(const std::string uniform);
		
		/**
		 * @brief A call to glBindFragDataLocation() - Causes an output variable of the fragment shader to output to a specific location. This is roughly equivalent to modern GLSL's layout(location=n) specifier, which is unusable until GLSL 330.
		 * @param outputVariableName The name of the output variable (oftentimes just colour or something)
		 * @param location The output location, corresponding to a colour attachment. Must be less than GL_MAX_DRAW_BUFFERS.
		 */
		void bindFragOutputLocation(std::string outputVariableName, unsigned int location);
		
		/**
		 * @brief Activates this shader program for the renderer to use.
		 */
		void use();
		
		/**
		 * @brief Deactivates this shader program.
		 */
		void unuse();
		
		/**
		 * @brief Releases all bound objects and deletes any allocated stuff.
		 */
		void destroy();
		
	private:
		unsigned int m_numberAttributes = 0;
		
		GLuint m_programID;
		GLuint m_vertexShaderID;
		GLuint m_fragmentShaderID;
		
		/**
		 * @brief Compiles a shader from source with OpenGL id
		 * @param source The source to compile from.
		 * @param name The name of the shader. This is normally associated with the key in the cache.
		 * @param id The ID of the shader that has been created with OpenGL calls.
		 */
		void compileShaderFromSource(const char* source, const std::string& name, GLuint id);
		
		/**
		 * @brief Gets the location of a uniform in a program
		 * @param uniform The name of the uniform to find.
		 * @return The location of the uniform.
		 */
		GLint getUniformLocation(const std::string& uniform);
	};

}

#include "ShaderProgram.tcc"
