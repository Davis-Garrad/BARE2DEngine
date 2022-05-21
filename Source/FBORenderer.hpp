#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Camera2D.hpp"
#include "Renderer.hpp"

namespace BARE2D
{

/**
 * @class FBORenderer
 * @brief The FBORenderer represents and manages an entire FrameBufferObject. This allows one to draw entire scenes
 * first to a texture, then perform some operations on that texture, then draw that texture to the screen. Shaders have
 * uniforms projectionMatrix (mat4), colourTexture (sampler2D), and depthTexture (sampler2D)
 */
class FBORenderer : public Renderer
{
public:
    FBORenderer(std::string& fragShader,
        std::string& vertShader,
        unsigned int windowWidth,
        unsigned int windowHeight,
        unsigned int numColourAttachments = 1);
    virtual ~FBORenderer();

    virtual void init() override;
    virtual void initUniforms() override;

    void setCamera(std::shared_ptr<Camera2D>& cam);
    std::shared_ptr<Camera2D> getCamera();

    virtual void render() override;

    virtual void begin() override;
    virtual void end() override;
    virtual void destroy() override;

protected:
    virtual void preRender() override;

    virtual void createRenderBatches() override;

    /**
     * @brief Binds the FBO and appropriate texture attachments
     */
    virtual void bind();

    /**
     * @brief Unbinds the FBO + textures
     */
    virtual void unbind();

    /**
     * @brief Creates all of the OpenGL textures, and takes their handles into m_colourTextureID, and m_depthTextureID
     */
    virtual void createTextures();

    /**
     * @brief Creates the OpenGL FBO instance and holds its handle in m_fboID;
     */
    virtual void createFBO();

    // The handle for the FBO object
    GLuint m_fboID;
    // The handles for the texture to draw colours, depths, etc. to. Accessed purely through the shader/s.
    GLuint* m_textureIDs = nullptr;
    // One for colour (normally), one for depth+stencil (8 bits of the 32 are dedicated to the stencil). Total number of
    // attachments to the FBO
    unsigned int m_numTextures;
    // Please note that the number of colour attachments is going to be the number of textures - 1.

    // The perspective camera (it also holds the window size, FBO position, etc.)
    std::shared_ptr<Camera2D> m_camera;

    // The fragment and vertex shader paths for the GLSL shader program
    std::string m_fragmentShaderPath, m_vertexShaderPath;

    // Some shaders won't touch the depth buffer.
    bool m_shaderHasDepth = false;
};

}
