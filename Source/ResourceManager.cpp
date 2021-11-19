#include "ResourceManager.hpp"

#include <vector>
#include <string>

#include "IOManager.hpp"
#include "BAREErrors.hpp"
#include "PicoPNG.hpp"
#include "GLContextManager.hpp"

namespace BARE2D {

	Cache<Texture>* ResourceManager::m_textures = new Cache<Texture>();
	Cache<MutableTexture>* ResourceManager::m_mutableTextures = new Cache<MutableTexture>();
	Cache<Sound>* ResourceManager::m_sounds = new Cache<Sound>();
	Cache<Script>* ResourceManager::m_scripts = new Cache<Script>();
	Cache<Font>* ResourceManager::m_fonts = new Cache<Font>();
	
	ShaderProgram ResourceManager::loadShaders(std::string& vertShaderSource, std::string& fragShaderSource) {
		ShaderProgram newProgram;
		
		newProgram.compileShaders(vertShaderSource.c_str(), fragShaderSource.c_str());
		
		return newProgram;
	}
	
	ShaderProgram ResourceManager::loadShadersFromSource(std::string& vertShaderSource, std::string& fragShaderSource) {
		ShaderProgram newProgram;
		
		newProgram.compileShadersFromSource(vertShaderSource.c_str(), fragShaderSource.c_str());
		
		return newProgram;
	}
	
	Texture ResourceManager::loadTexture(std::string& texturePath)
	{
		{ // First, check that it doesn't already exist.
			Texture* cached = m_textures->findItem(texturePath);
			
			if(cached)
				return *cached;
		}
		
		// So, it's not in the cache if we're still here. Load it from a file, create it in the cache, and add it.
		// Creates it in the cache and returns a pointer.
		Texture* loadedTex = m_textures->createItem(texturePath);
		loadedTex->filepath = texturePath;
		{
		
			// Load raw data from the file
			std::vector<unsigned char> fileData;
			bool good = IOManager::readFileToBuffer(texturePath, fileData);
			
			// Check for errors
			if(!good) {
				throwFatalError(BAREError::TEXTURE_FAILURE);
				return *loadedTex;
			}
			
			// Decode the raw information into texture data (thanks PicoPNG!)
			std::vector<unsigned char> textureData;
			unsigned long width, height;
			int errCode = decodePNG(textureData, width, height, &(fileData[0]), fileData.size());
			loadedTex->width = width;
			loadedTex->height = height;
			
			// Check if pico broke
			if(errCode != 0) {
				throwFatalError(BAREError::TEXTURE_FAILURE);
				return *loadedTex;
			}
			
			// Our data is good, so actually generate the texture, etc.
			glGenTextures((GLsizei)1, &(loadedTex->id));
			
			// Bind the texture object (GLContext just makes sure the texture isn't already bound, but we know it ain't. We just made it.)
			glBindTexture(GL_TEXTURE_2D, loadedTex->id);
			
			// Upload pixel data
			glTexImage2D(GL_TEXTURE_2D, (GLint)0, GL_RGBA, (GLsizei)loadedTex->width, (GLsizei)loadedTex->height, (GLint)0, GL_RGBA, GL_UNSIGNED_BYTE, &(textureData[0]));
			
			// Set some basic parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			
			// Generate mipmaps
			glGenerateMipmap(GL_TEXTURE_2D);
			
			// Finally, unbind the texture! This should return us to our last state, just to avoid trouble.
			glBindTexture(GL_TEXTURE_2D, GLContextManager::getContext()->getBoundTexture());
		}
		
		// Now that we know our texture definitely exists, we just return an instance of it!
		return *loadedTex;
	}

	MutableTexture* ResourceManager::setMutableTexture(std::string& textureName, Texture& texture)
	{
		return nullptr;
	}

	MutableTexture* ResourceManager::loadMutableTexture(std::string& textureName)
	{
	}

	Sound ResourceManager::loadSound(std::string& soundPath)
	{
	}

	Script ResourceManager::loadScript(std::string& scriptPath)
	{
	}

	std::string ResourceManager::loadScriptFromSource(std::string& scriptSource)
	{
	}

	Font ResourceManager::loadFont(std::string& fontPath)
	{
	}

	void ResourceManager::clearCaches()
	{
	}


}


