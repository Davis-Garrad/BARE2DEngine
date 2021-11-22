#include "ShaderProgram.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IOManager.hpp"
#include "BAREErrors.hpp"

namespace BARE2D {

	ShaderProgram::ShaderProgram() : m_numberAttributes(0), m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0)
	{
		
	}

	ShaderProgram::~ShaderProgram()
	{
	}

	void ShaderProgram::compileShaders(const char* vertexShaderPath, const char* fragmentShaderPath)
	{
		// Just read the two shaders and compile them
		std::string vertexSource, fragmentSource;
		
		IOManager::readFileToBuffer(vertexShaderPath, vertexSource);
		IOManager::readFileToBuffer(fragmentShaderPath, fragmentSource);
		
		// Just compile them from their sources now
		compileShadersFromSource(vertexSource.c_str(), fragmentSource.c_str());
	}

	void ShaderProgram::compileShadersFromSource(const char* vertexSource, const char* fragmentSource)
	{
		// Make sure that if we already have a program, we don't anymore.
		destroy();
		
		// Now to actually compile them
		// Tell OpenGL to give us an ID
		m_programID = glCreateProgram();
		
		// Check for errors
		if(m_programID == 0) {
			// Error occurred!
			throwFatalError(BAREError::GLSL_PROGRAM_FAILURE);
		}
		
		// Do the same for the vertex and fragment shaders
		m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		
		// Check for errors
		if(m_vertexShaderID == 0) {
			// Error occurred!
			throwFatalError(BAREError::VERTEX_SHADER_FAILURE);
		}
		
		m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		
		// Check for errors
		if(m_fragmentShaderID == 0) {
			// Error!
			throwFatalError(BAREError::FRAGMENT_SHADER_FAILURE);
		}
		
		// Compile each shader separately
		compileShaderFromSource(vertexSource, "Vertex Shader", m_vertexShaderID);
		compileShaderFromSource(fragmentSource, "Fragment Shader", m_fragmentShaderID);
	}

	void ShaderProgram::linkShaders(std::initializer_list<std::string> attributes)
	{
		// Link up the shaders, and make sure that they have their needed attributes before they link.
		
		// Add the attributes
		for(std::string item : attributes) {
			glBindAttribLocation(m_programID, m_numberAttributes++, item.c_str());
		}
		
		// Now actually link
		// First, attach the shaders to the program
		glAttachShader(m_programID, m_vertexShaderID);
		glAttachShader(m_programID, m_fragmentShaderID);
		
		// Link them together
		glLinkProgram(m_programID);
		
		// Check if they're linked now (error check)
		GLint linked = GL_FALSE;
		glGetProgramiv(m_programID, GL_LINK_STATUS, &linked);
		
		// Error check
		if(linked == GL_FALSE) {
			// Not linked! They should be, but they ain't.
			// Get the length of the log
			GLint maxLength = 0;
			glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);
			
			// Get the actual log (null-terminated, but maxLength accounts for that)
			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);
			
			// Now that the program has failed and given us the info we want, we can dispose of it.
			glDeleteProgram(m_programID);
			glDeleteShader(m_vertexShaderID);
			glDeleteShader(m_fragmentShaderID);
			
			// Throw fatal error, we cannot continue.
			throwError(BAREError::SHADER_LINK_FAILURE);
			throwFatalError("Shaders failed to link: " + std::string(errorLog.begin(), errorLog.end()));
		}
		
		// Now that we have everything all linked up and it's all good, we can just detach the shaders and delete them. They're now in the program.
		glDetachShader(m_programID, m_vertexShaderID);
		glDetachShader(m_programID, m_fragmentShaderID);
		
		// And delete em
		glDeleteShader(m_vertexShaderID);
		glDeleteShader(m_fragmentShaderID);
	}

	GLint ShaderProgram::getUniformLocation(const std::string& uniform)
	{
		// Just use OpenGL's calls, then check for errors
		unsigned int location = glGetUniformLocation(m_programID, uniform.c_str());
		
		// Error check
		if(location == GL_INVALID_INDEX) {
			// Error!
			throwError(BAREError::UNIFORM_NOT_FOUND);
			throwFatalError("Uniform name: " + uniform);
		}
		
		return location;
	}

	void ShaderProgram::use()
	{
		// Enable the program!
		glUseProgram(m_programID);
		
		// Enable all attributes!
		for(unsigned int i = 0; i < m_numberAttributes; i++) {
			glEnableVertexAttribArray(i);
		}
		
		// We're done! gg ez
	}

	void ShaderProgram::unuse()
	{
		// Do the opposite of use!
		// Disable the program
		glUseProgram(0);
		
		// Disable the attributes
		for(unsigned int i = 0; i < m_numberAttributes; i++) {
			glDisableVertexAttribArray(i);
		}
	}

	void ShaderProgram::destroy()
	{
		// Dispose of stuff
		if(m_programID)
			glDeleteProgram(m_programID);
		m_programID = 0;
		m_numberAttributes = 0;
		m_vertexShaderID = 0;
		m_fragmentShaderID = 0;
	}

	void ShaderProgram::compileShaderFromSource(const char* source, const std::string& name, GLuint id)
	{
		// Tell OpenGL what our source is (1 is the number of source "files"), nullptr indicates that the source is null-terminated.
		glShaderSource(id, 1, &source, nullptr);
		
		// Just compile
		glCompileShader(id);
		
		// Check for errors of course
		GLint compiled = GL_FALSE;
		glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
		
		if(compiled == GL_FALSE) {
			// Not compiled! It should be, but it ain't.
			// Get the length of the log
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
			
			// Get the actual log (null-terminated, but maxLength accounts for that)
			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
			
			// Now that the compilation has failed and given us the info we want, we can dispose of the shader.
			glDeleteShader(id);
			
			// Throw fatal error, we cannot continue.
			throwError(BAREError::SHADER_COMPILE_FAILURE);
			throwFatalError("Shader failed to compile: " + name + "\n\n" + std::string(errorLog.begin(), errorLog.end()));
		}
	}
	
	
	// Template specializations
	

	template<>
	void ShaderProgram::setUniform<int>(const std::string uniform, int data) {
		// First, get the location
		GLint loc = getUniformLocation(uniform);
		
		// Now, call glUniform{whatever}
		glUniform1i(loc, data);
	}
	template<>
	void ShaderProgram::setUniform<unsigned int>(const std::string uniform, unsigned int data) {
		// First, get the location
		GLint loc = getUniformLocation(uniform);
		
		// Now, call glUniform{whatever}
		glUniform1ui(loc, data);
	}
	template<>
	void ShaderProgram::setUniform<float>(const std::string uniform, float data) {
		// First, get the location
		GLint loc = getUniformLocation(uniform);
		
		// Now, call glUniform{whatever}
		glUniform1f(loc, data);
	}
	template<>
	void ShaderProgram::setUniform<glm::vec2>(const std::string uniform, glm::vec2 data) {
		// First, get the location
		GLint loc = getUniformLocation(uniform);
		
		// Now, call glUniform{whatever}
		glUniform2fv(loc, 1, glm::value_ptr(data));
	}
	template<>
	void ShaderProgram::setUniform<glm::vec3>(const std::string uniform, glm::vec3 data) {
		// First, get the location
		GLint loc = getUniformLocation(uniform);
		
		// Now, call glUniform{whatever}
		glUniform3fv(loc, 1, glm::value_ptr(data));
	}
	template<>
	void ShaderProgram::setUniform<glm::vec4>(const std::string uniform, glm::vec4 data) {
		// First, get the location
		GLint loc = getUniformLocation(uniform);
		
		// Now, call glUniform{whatever}
		glUniform4fv(loc, 1, glm::value_ptr(data));
	}
	template<>
	void ShaderProgram::setUniform<glm::ivec2>(const std::string uniform, glm::ivec2 data) {
		// First, get the location
		GLint loc = getUniformLocation(uniform);
		
		// Now, call glUniform{whatever}
		glUniform2iv(loc, 1, glm::value_ptr(data));
	}
	template<>
	void ShaderProgram::setUniform<glm::ivec3>(const std::string uniform, glm::ivec3 data) {
		// First, get the location
		GLint loc = getUniformLocation(uniform);
		
		// Now, call glUniform{whatever}
		glUniform3iv(loc, 1, glm::value_ptr(data));
	}
	template<>
	void ShaderProgram::setUniform<glm::ivec4>(const std::string uniform, glm::ivec4 data) {
		// First, get the location
		GLint loc = getUniformLocation(uniform);
		
		// Now, call glUniform{whatever}
		glUniform4iv(loc, 1, glm::value_ptr(data));
	}

}
