#pragma once

#include "Cache.hpp"

#include "Font.hpp"
#include "LuaScript.hpp"
#include "Music.hpp"
#include "MutableTexture.hpp"
#include "ShaderProgram.hpp"
#include "Sound.hpp"
#include "Texture.hpp"

namespace BARE2D
{

/**
 * @class ResourceManager
 * @brief The resource manager manages resources. Groundbreaking news, I know. In short, the resource manager loads and
 * manages Textures, Sounds, Scripts, Fonts, etc.
 */
class ResourceManager
{
public:
    /**
     * @brief Loads some shaders. Combines both to give a full shader program. Does not cache.
     * @param vertShaderPath The path to the vertex shader
     * @param fragShaderPath The path to the fragment shader
     * @return A GLSL program of type ShaderProgram instance which is the compiled version of vertShader + fragShader.
     */
    static ShaderProgram loadShaders(std::string& vertShaderPath, std::string& fragShaderPath);

    /**
     * @brief Loads some shaders from their source. Does not cache
     * @param vertShaderSource The source to compile from.
     * @param fragShaderSource The source to compile from.
     * @return
     */
    static ShaderProgram loadShadersFromSource(std::string& vertShaderSource, std::string& fragShaderSource);

    /**
     * @brief Loads a texture if it isn't already in the cache.
     * @param texturePath A path to the texture to be loaded, including the actual name of the texture
     * ("assets/texture.png" for example)
     * @return A copy of the texture, whether it was just loaded or it was taken from the cache.
     */
    static Texture loadTexture(std::string& texturePath);

    /**
     * @brief Sets the data of some created texture. This can be used to create "dummy" textures for use in FBOs,
     * shaders, etc. Creates a GL texture in the context if one doesn't already exist.
     * @param textureName The "filepath" of the texture. This is used to identify the texture in the cache when
     * loadTexture is called.
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
     * @brief Loads some music from the filepath given from the cache or from the file if the cache doesn't contain it.
     * @param musicPath The path to load the music from
     * @return An instance of the music.
     */
    static Music loadMusic(std::string& musicPath);

    /**
     * @brief Loads a script from the filepath given from the cache or from the file if it's not already in the cache.
     * @param scriptPath The path to load the script from.
     * @return An instance of the script.
     */
    static LuaScript loadScript(std::string& scriptPath);

    /**
     * @brief Creates and caches a script from the given source code.
     * @param scriptSource The actual source code (Lua) of the script
     * @param name The name of the script
     * @return The name of the script, so that it can be loaded from the regular cache.
     */
    static LuaScript loadScriptFromSource(std::string& scriptSource, std::string name);

    /**
     * @brief Loads a font to the cache.
     * @param fontPath The path to load the font from
     * @param size The size of the font to load it as.
     * @return An instance of the font.
     */
    static Font loadFont(std::string& fontPath, int size);

    /**
     * @brief Clears the various caches. This is useful for debugging.
     */
    static void clearCaches();

private:
    static Cache<std::string, Texture>* m_textures;
    static Cache<std::string, MutableTexture>* m_mutableTextures;
    static Cache<std::string, Sound>* m_sounds;
    static Cache<std::string, Music>* m_music;
    static Cache<std::string, LuaScript>* m_scripts;
    static Cache<std::string, Font>* m_fonts;
};

}
