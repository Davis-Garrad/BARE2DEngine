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
		void compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		
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
		 * @brief Gets the location of a uniform in a program
		 * @param uniform The name of the uniform to find.
		 * @return The location of the uniform.
		 */
		GLint getUniformLocation(const std::string& uniform);
		
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

	};

}

