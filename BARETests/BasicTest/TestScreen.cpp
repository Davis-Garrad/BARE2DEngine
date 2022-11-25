#include "TestScreen.h"

#include <GL/glew.h>
#include <math.h>
#include <Camera2D.hpp>
#include <Filesystem.hpp>
#include <Logger.hpp>
#include <LuaScript.hpp>
#include <LuaScriptQueue.hpp>
#include <ResourceManager.hpp>
#include <Window.hpp>

#define LUA_WINDOW_REGISTRY_KEY "window"

// Some Lua functions

int lua_setWindowSize(lua_State* L)
{
    // get width and height
    unsigned int width = lua_tointeger(L, -2);
    unsigned int height = lua_tointeger(L, -1);
    lua_pop(L, 2);

    // get the window
    BARE2D::Window* win = BARE2D::LuaScriptEngine::getValueFromRegistry<BARE2D::Window>(L, LUA_WINDOW_REGISTRY_KEY);

    win->setSize(width, height);

    return 0;
}

// Now to actual member functions

TestScreen::TestScreen(BARE2D::Window* window, BARE2D::InputManager* input)
    : BARE2D::Screen(), m_window(window), m_inputManager(input)
{}

TestScreen::~TestScreen()
{}
void TestScreen::destroyScreen()
{}

void TestScreen::draw()
{
    glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_fbo->begin();
    m_fbo->getShader()->setUniform("mousePos", &m_position);

    m_renderer->begin();

    float depth = 0.0f;
    unsigned int xNum = 7, yNum = 4;  // = 35, yNum = 20;

    for(unsigned int i = 0; i < xNum; i++)
	{
	    for(unsigned int j = 0; j < yNum; j++)
		{
		    glm::vec2 pos = glm::vec2(0.0f);
		    glm::vec2 size = glm::vec2(700.0f / (float)xNum, 400.0f / (float)yNum);

		    depth = 1.0f / std::pow(xNum + yNum, 3) * std::pow(i + j, 3);

		    m_renderer->draw(glm::vec4(pos.x + i * size.x, pos.y + j * size.y, size.x, size.y),
		                     glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), m_texture.id, m_textureNormal.id, depth);
		}
	}

    m_renderer->end();
    m_renderer->render();

    m_fbo->end();
    m_fbo->render();

    m_fontRenderer->begin();

    float fps = renderCount / (updateCount / 60.0f);

    glm::vec2 pos = m_fontRenderer->getCamera()->getWorldspaceCoord(glm::vec2(0.0f, 0.0f));
    glm::vec2 size = m_renderer->getCamera()->getWorldspaceSize(glm::vec2(0.4f, 0.4f));

    m_fontRenderer->draw(m_font_openSans, size, glm::vec4(pos.x, pos.y, size.x, size.y),
                         std::string("Updates: " + std::to_string((int)(updateCount)) + "\nDraw Calls: " +
                                     std::to_string((int)renderCount) + "\nFPS: " + std::to_string(fps))
                             .c_str(),
                         0.0f, BARE2D::Colour(255, 255, 255, 255));

    m_fontRenderer->end();
    m_fontRenderer->render();

    // m_gui->draw();

    // Debug rendering demo.
    /*float radians = m_time * M_PI * 2.0f / 60.0f;
float radiansCycle = m_time * M_PI * 2.0f / 240.0f;
float radiusSeconds = 0.6f;
float radiusCycles = 0.4f;
float x0 = radiusSeconds * std::sin(radians);
float y0 = radiusSeconds * std::cos(radians);
float x1 = radiusCycles * std::sin(radiansCycle);
float y1 = radiusCycles * std::cos(radiansCycle);

m_debugRenderer->begin();
m_debugRenderer->drawCircle(glm::vec2(0.0f, 0.0f), 3.0f, 0.6f, BARE2D::Colour(0, 255, 0, 64));
m_debugRenderer->drawLine(glm::vec2(0.0f, 0.0f), glm::vec2(x0, y0), 2.0f, BARE2D::Colour(255, 255, 255, 255));
m_debugRenderer->drawLine(glm::vec2(0.0f, 0.0f), glm::vec2(x1, y1), 4.0f, BARE2D::Colour(255, 255, 255, 255));
m_debugRenderer->drawRectangle(glm::vec4(0.0f, 0.0f, 0.4f, 0.4f), 3.0f, BARE2D::Colour(255, 255, 255, 64));
m_debugRenderer->end();
m_debugRenderer->render();*/

    renderCount++;

    for(unsigned int i = 0; i < slowFactor; i++)
	{}
}

int TestScreen::getNextScreenIndex() const
{
    return 0;
}

void TestScreen::initScreen()
{}

void TestScreen::onEntry()
{
    BARE2D::initGLErrorCallback(BARE2D::GLErrorSeverity::LOW);

    m_position = glm::vec2(0.0f);

    BARE2D::Logger::getInstance()->log(
        "Entering screen! Will display pretty colours for a bit, then shrink, then leave!");

    std::string assetsPath = BARE2D::Filesystem::getWorkingDirectory() + "/..";

    // Load a texture
    std::string texPath = assetsPath + "/152.png";
    std::string texBMPath = assetsPath + "/152_norm.png";
    m_texture = BARE2D::ResourceManager::loadTexture(texPath);
    m_textureNormal = BARE2D::ResourceManager::loadTexture(texBMPath);
    // Load a shader
    std::string vShaderPath = assetsPath + "/Shader.vert";
    std::string fShaderPath = assetsPath + "/Shader.frag";

    // Load another FBO shader
    std::string fShaderPath_fbo = assetsPath + "/ShaderFBO.frag";

    m_renderer = new BARE2D::BumpyRenderer(fShaderPath, vShaderPath, m_window->getWidth(), m_window->getHeight());
    m_renderer->init();

    m_fbo = new BARE2D::FBORenderer(fShaderPath_fbo, vShaderPath, m_window->getWidth(), m_window->getHeight(), 3);
    m_fbo->init();

    std::string fontPath = assetsPath + "/OpenSans-Regular.ttf";
    m_font_openSans = BARE2D::ResourceManager::loadFont(fontPath, 96);  // 24 is decent

    m_fontRenderer = new BARE2D::FontRenderer(fShaderPath, vShaderPath);
    m_fontRenderer->init();
    m_fontRenderer->setCamera(m_renderer->getCamera());

    m_debugRenderer = new BARE2D::DebugRenderer();
    m_debugRenderer->init();

    m_luaEngine.init(assetsPath + "/Lua/PrintTest.lua");
    m_luaEngine.registerCFunction(lua_setWindowSize, "setWindowSize");
    BARE2D::LuaScriptEngine::addValueToRegistry(m_luaEngine.getMasterState(), m_window, LUA_WINDOW_REGISTRY_KEY);

    std::string scriptPath = assetsPath + "/Lua/PrintTest.lua";
    BARE2D::LuaScript scr = BARE2D::ResourceManager::loadScript(scriptPath);
    BARE2D::LuaScriptQueue::getInstance()->addLuaScript(scr);

    std::string guiPath = assetsPath + "/GUI";
    m_gui = BARE2D::BARECEGUI::getInstance();
    m_gui->init(guiPath, 1);
    m_gui->loadScheme("WindowsLook.scheme");
    m_gui->setFont("Junicode-13");
    CEGUI::FrameWindow* win = static_cast<CEGUI::FrameWindow*>(
        m_gui->createWidget("WindowsLook/FrameWindow", glm::vec4(0.25f, 0.25f, 0.5f, 0.5f), glm::vec4(0.0f)));
    win->setText("Look ma! It's a FrameWindow!");

    m_audioManager = BARE2D::AudioManager::getInstance();
    m_audioManager->init();

    std::string musicPath = assetsPath + "/SampleMusic.mus";
    BARE2D::Music mus = BARE2D::ResourceManager::loadMusic(musicPath);
    m_audioManager->playMusic(mus, 8000);
}

void TestScreen::onExit()
{
    BARE2D::Logger::getInstance()->log("Leaving screen!");

    BARE2D::AudioManager::release();
    BARE2D::BARECEGUI::release();

    delete m_renderer;
    delete m_fbo;
    delete m_fontRenderer;
    delete m_debugRenderer;
}

void TestScreen::update(double dt)
{
    m_time++;

    updateCount++;

    glm::vec2 screenSize = glm::vec2(m_window->getWidth(), m_window->getHeight());

    glm::vec2 newPos =
        ((m_inputManager->getMousePosition() / screenSize * 2.0f) - glm::vec2(1.0f)) * glm::vec2(1.0f, -1.0f);
    glm::vec2 delta = newPos - m_position;
    m_position = newPos;

    /*if(m_inputManager->isKeyDown(SDL_BUTTON_LEFT))
            m_renderer->getCamera()->offsetFocus(-delta * screenSize / 2.0f / m_renderer->getCamera()->getScale());

    m_renderer->getCamera()->offsetScale(m_inputManager->getMouseScrollwheelPosition() / 10.0f,
                                                                             m_inputManager->getMouseScrollwheelPosition()
    / 10.0f);*/

    if(m_inputManager->isKeyDown(SDLK_LEFT))
	{
	    m_renderer->getCamera()->offsetFocus(glm::vec2(-1.0f, 0.0f));
    }
    if(m_inputManager->isKeyDown(SDLK_RIGHT))
	{
	    m_renderer->getCamera()->offsetFocus(glm::vec2(1.0f, 0.0f));
    }
    if(m_inputManager->isKeyDown(SDLK_UP))
	{
	    m_renderer->getCamera()->offsetFocus(glm::vec2(0.0f, 1.0f));
    }
    if(m_inputManager->isKeyDown(SDLK_DOWN))
	{
	    m_renderer->getCamera()->offsetFocus(glm::vec2(0.0f, -1.0f));
    }
    if(m_inputManager->isKeyDown(SDLK_LCTRL))
	{
	    m_renderer->getCamera()->offsetScale(-0.01f, -0.01f);
    }
    if(m_inputManager->isKeyDown(SDLK_RCTRL))
	{
	    m_renderer->getCamera()->offsetScale(0.01f, 0.01f);
    }

    m_luaEngine.update();
    m_gui->update();
}
