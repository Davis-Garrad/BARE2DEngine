#include "ResourceManager.hpp"

#include <vector>
#include <string>

#include "IOManager.hpp"
#include "BAREErrors.hpp"
#include "PicoPNG.hpp"
#include "GLContextManager.hpp"

namespace BARE2D {

	Cache<std::string, Texture>* ResourceManager::m_textures = new Cache<std::string, Texture>();
	Cache<std::string, MutableTexture>* ResourceManager::m_mutableTextures = new Cache<std::string, MutableTexture>();
	Cache<std::string, Sound>* ResourceManager::m_sounds = new Cache<std::string, Sound>();
	Cache<std::string, LuaScript>* ResourceManager::m_scripts = new Cache<std::string, LuaScript>();
	Cache<std::string, Font>* ResourceManager::m_fonts = new Cache<std::string, Font>();
	
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
			
			// Bind the texture object
			GLContextManager::getContext()->bindTexture(GL_TEXTURE_2D, loadedTex->id);
			
			// Upload pixel data
			glTexImage2D(GL_TEXTURE_2D, (GLint)0, GL_RGBA, (GLsizei)loadedTex->width, (GLsizei)loadedTex->height, (GLint)0, GL_RGBA, GL_UNSIGNED_BYTE, &(textureData[0]));
			
			// Set some basic parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			
			// Generate mipmaps
			glGenerateMipmap(GL_TEXTURE_2D);
			
			// Finally, unbind the texture.
			GLContextManager::getContext()->bindTexture(GL_TEXTURE_2D, 0);
		}
		
		// Now that we know our texture definitely exists, we just return an instance of it!
		return *loadedTex;
	}

	MutableTexture* ResourceManager::setMutableTexture(std::string& textureName, Texture& texture)
	{
		throwFatalError(BAREError::UNINITIALIZED_FUNCTION, "ResourceManager::setMutableTexture");
		
		return nullptr;
	}

	MutableTexture* ResourceManager::loadMutableTexture(std::string& textureName)
	{
		throwFatalError(BAREError::UNINITIALIZED_FUNCTION, "ResourceManager::loadMutableTexture");
		
		return nullptr;
	}

	Sound ResourceManager::loadSound(std::string& soundPath)
	{
		throwFatalError(BAREError::UNINITIALIZED_FUNCTION, "ResourceManager::loadSound");
		
		Sound s;
		return s;
	}

	LuaScript ResourceManager::loadScript(std::string& scriptPath)
	{
		// Make sure we don't already have it loaded
		LuaScript* searched = m_scripts->findItem(scriptPath); 
		if(searched) {
			return *searched;
		}
		
		// Just needs to load text from a script file and put it into a LuaScript object, then put that into the cache.
		// Load it!
		std::string scriptSource = "";
		IOManager::readFileToBuffer(scriptPath.c_str(), scriptSource);
		
		// Put it in the cache!
		LuaScript* script = m_scripts->createItem(scriptPath);
		// and actually give it data lol.
		script->m_script = scriptSource;
		
		return *script;
	}

	LuaScript ResourceManager::loadScriptFromSource(std::string& scriptSource, std::string name)
	{
		// Make sure we don't already have it loaded
		LuaScript* searched = m_scripts->findItem(name); 
		if(searched) {
			return *searched;
		}
		
		// Put it in the cache!
		LuaScript* script = m_scripts->createItem(name);
		// and actually give it data lol.
		script->m_script = scriptSource;
		
		return *script;
	}

	Font ResourceManager::loadFont(std::string& fontPath, int size)
	{
		std::string path = fontPath + std::to_string(size);
		
		// Check we haven't cached it
		{
			Font* cached = m_fonts->findItem(path);
			
			if(cached) 
				return *cached;
		}
		
		// We don't already have it. Time to create it!
		Font* font = m_fonts->createItem(path);
		
		font->init(fontPath.c_str(), size);
		
		return *font;
	}

	void ResourceManager::clearCaches()
	{
		m_textures->clear();
		m_mutableTextures->clear();
		m_sounds->clear();
		m_scripts->clear();
		m_fonts->clear();
		
		Logger::getInstance()->log("Cleared all caches.");
	}


}


