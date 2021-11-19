#pragma once

#include "Cache.hpp"

#include "Texture.hpp"
#include "MutableTexture.hpp"
#include "Sound.hpp"
#include "Script.hpp"
#include "Font.hpp"
#include "ShaderProgram.hpp"

namespace BARE2D {

	/**
	 * @class ResourceManager
	 * @brief The resource manager manages resources. Groundbreaking news, I know. In short, the resource manager loads and manages Textures, Sounds, Scripts, Fonts, etc.
	 */
	class ResourceManager
	{
	public:
		/**
		 * @brief Loads some shaders if they aren't already in the cache. Combines both to give a full shader program.
		 * @param vertShaderPath The path to the vertex shader
		 * @param fragShaderPath The path to the fragment shader
		 * @return A GLSL program of type ShaderProgram instance which is the compiled version of vertShader + fragShader.
		 */
		static ShaderProgram loadShaders(std::string& vertShaderPath, std::string& fragShaderPath);
		
		/**
		 * @brief Loads some shaders from their source if they don't exist in the cache. Caches these under given key.
		 * @param vertShaderSource The source to compile from.
		 * @param vertShaderKey The key to cache the vertex shader under.
		 * @param fragShaderSource The source to compile from.
		 * @param fragShaderKey The key to cache the fragment shader under.
		 * @return 
		 */
		static ShaderProgram loadShadersFromSource(std::string& vertShaderSource, std::string& vertShaderKey, std::string& fragShaderSource, std::string& fragShaderKey);
	
		/**
		 * @brief Loads a texture if it isn't already in the cache. 
		 * @param texturePath A path to the texture to be loaded, including the actual name of the texture ("assets/texture.png" for example)
		 * @return A copy of the texture, whether it was just loaded or it was taken from the cache.
		 */
		static Texture loadTexture(std::string& texturePath);
		
		/**
		 * @brief Sets the data of some created texture. This can be used to create "dummy" textures for use in FBOs, shaders, etc. Creates a GL texture in the context if one doesn't already exist.
		 * @param textureName The "filepath" of the texture. This is used to identify the texture in the cache when loadTexture is called.
		 * @param texture The data for the mutable texture.
		 * @return A pointer to the mutable texture.
		 */
		static MutableTexture* setMutableTexture(std::string& textureName, Texture& texture);
		
		/**
		 * @brief Gets a texture from the cache, or creates a new, empty texture
		 * @param textureName The "filepath" of the texture, this is used to identify the texture in the cache.
		 * @return A pointer to the mutable texture.
		 */
		static MutableTexture* loadMutableTexture(std::string& textureName);
		
		/**
		 * @brief Loads a sound from the filepath given from the cache or from the file if the cache doesn't contain it.
		 * @param soundPath The path to load the sound from.
		 * @return An instance of the sound.
		 */
		static Sound loadSound(std::string& soundPath);
		
		/**
		 * @brief Loads a script from the filepath given from the cache or from the file if it's not already in the cache.
		 * @param scriptPath The path to load the script from.
		 * @return An instance of the script.
		 */
		static Script loadScript(std::string& scriptPath);
		
		/**
		 * @brief Creates and caches a script from the given source code.
		 * @param scriptSource The actual source code (Lua) of the script
		 * @return The name of the script, so that it can be loaded from the regular cache.
		 */
		static std::string loadScriptFromSource(std::string& scriptSource);
		
		/**
		 * @brief Loads a font to the cache.
		 * @param fontPath The path to load the font from
		 * @return An instance of the font.
		 */
		static Font loadFont(std::string& fontPath);
		
		/**
		 * @brief Clears the various caches. This is useful for debugging.
		 */
		static void clearCaches();
		
	private:
		static Cache<Texture>* m_textures;
		static Cache<MutableTexture>* m_mutableTextures;
		static Cache<Sound>* m_sounds;
		static Cache<Script>* m_scripts;
		static Cache<Font>* m_fonts;

	};

}

