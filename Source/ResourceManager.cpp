#include "ResourceManager.hpp"

#include <vector>
#include <string>

#include "IOManager.hpp"
#include "BAREErrors.hpp"
#include "PicoPNG.hpp"
#include "GLContextManager.hpp"

namespace BARE2D
{

	std::string ResourceManager::m_assetsPathPrefix = "";
	std::string ResourceManager::m_texturePathPrefix = "";
	Cache<std::string, Texture>* ResourceManager::m_textures = new Cache<std::string, Texture>();
	Cache<std::string, MutableTexture>* ResourceManager::m_mutableTextures = new Cache<std::string, MutableTexture>();
	Cache<std::string, Sound>* ResourceManager::m_sounds = new Cache<std::string, Sound>();
	Cache<std::string, Music>* ResourceManager::m_music = new Cache<std::string, Music>();
	Cache<std::string, LuaScript>* ResourceManager::m_scripts = new Cache<std::string, LuaScript>();
	Cache<std::string, Font>* ResourceManager::m_fonts = new Cache<std::string, Font>();

	ShaderProgram ResourceManager::loadShaders(std::string& vertShaderSource, std::string& fragShaderSource)
	{
		ShaderProgram newProgram;

		newProgram.compileShaders((m_assetsPathPrefix + vertShaderSource).c_str(), (m_assetsPathPrefix + fragShaderSource).c_str());

		return newProgram;
	}

	ShaderProgram ResourceManager::loadShadersFromSource(std::string& vertShaderSource, std::string& fragShaderSource)
	{
		ShaderProgram newProgram;

		newProgram.compileShadersFromSource(vertShaderSource.c_str(), fragShaderSource.c_str());

		return newProgram;
	}

	Texture ResourceManager::loadTexture(std::string& texturePath)
	{
		std::string fullPath = m_assetsPathPrefix + m_texturePathPrefix + texturePath;

		{
			// First, check that it doesn't already exist.
			Texture* cached = m_textures->findItem(fullPath);

			if(cached)
				return *cached;
		}

		// So, it's not in the cache if we're still here. Load it from a file, create it in the cache, and add it.
		// Creates it in the cache and returns a pointer.
		Texture* loadedTex = m_textures->createItem(fullPath);
		loadedTex->filepath = fullPath;
		{

			// Load raw data from the file
			std::vector<unsigned char> fileData;
			bool good = IOManager::readFileToBuffer(fullPath, fileData);

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
		std::string fullPath = m_assetsPathPrefix + soundPath;

		Sound* searched = m_sounds->findItem(fullPath);
		if(searched) {
			return *searched; // We've already got it in the cache
		}

		// Cache doesn't have it. Load it.
		Mix_Chunk* chunk = Mix_LoadWAV(fullPath.c_str());
		if(!chunk) {
			// There's been an error!
			throwFatalError(BAREError::SDL_MIXER_LOAD_FAILURE, "Failed to load sound: " + std::string(Mix_GetError()));
		}

		// Create a new one in the cache.
		Sound* created = m_sounds->createItem(fullPath);
		created->chunk = chunk;

		return *created;
	}

	Music ResourceManager::loadMusic(std::string& musicPath)
	{
		std::string fullPath = m_assetsPathPrefix + musicPath;

		Music* searched = m_music->findItem(fullPath);
		if(searched) {
			return *searched; // We've already got it in the cache
		}

		// Cache doesn't have it. Load it.
		Mix_Music* musicChunk = Mix_LoadMUS(fullPath.c_str());
		if(!musicChunk) {
			// There's been an error!
			throwFatalError(BAREError::SDL_MIXER_LOAD_FAILURE, "Failed to load music: " + std::string(Mix_GetError()));
		}

		// Create a new one in the cache.
		Music* created = m_music->createItem(fullPath);
		created->music = musicChunk;

		return *created;
	}

	LuaScript ResourceManager::loadScript(std::string& scriptPath)
	{
		if(scriptPath == "") return LuaScript();

		std::string fullPath = m_assetsPathPrefix + scriptPath;

		// Make sure we don't already have it loaded
		LuaScript* searched = m_scripts->findItem(fullPath);
		if(searched) {
			return *searched;
		}

		// Just needs to load text from a script file and put it into a LuaScript object, then put that into the cache.
		// Load it!
		std::string scriptSource = "";
		if(!IOManager::readFileToBuffer(fullPath.c_str(), scriptSource)) {
			// There was a problem reading, return an uninited script
			return LuaScript();
		}

		// Put it in the cache!
		LuaScript* script = m_scripts->createItem(fullPath);
		// and actually give it data lol.
		script->m_script = scriptSource;
		script->m_path = fullPath;
		script->inited = true;

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
		script->m_path = "NO_PATH";
		script->inited = true;

		return *script;
	}

	Font ResourceManager::loadFont(std::string& fontPath, int size)
	{
		std::string path = m_assetsPathPrefix + fontPath + std::to_string(size);

		// Check we haven't cached it
		{
			Font* cached = m_fonts->findItem(path);

			if(cached)
				return *cached;
		}

		// We don't already have it. Time to create it!
		Font* font = m_fonts->createItem(path);

		font->init((m_assetsPathPrefix + fontPath).c_str(), size);

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

	void ResourceManager::setAssetsPathPrefix(std::string prefix)
	{
		m_assetsPathPrefix = prefix;
	}

	std::string ResourceManager::getAssetsPathPrefix()
	{
		return m_assetsPathPrefix;
	}

	void ResourceManager::setTexturePathPrefix(std::string prefix)
	{
		m_texturePathPrefix = prefix;
	}

}
