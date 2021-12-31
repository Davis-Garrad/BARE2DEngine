#include "TestScreen.h"

#include <math.h>
#include <GL/glew.h>
#include <Logger.hpp>
#include <Window.hpp>
#include <ResourceManager.hpp>
#include <Camera2D.hpp>
#include <LuaScript.hpp>
#include <LuaScriptQueue.hpp>

#define LUA_WINDOW_REGISTRY_KEY "window"

// Some Lua functions

int lua_setWindowSize(lua_State* L) {
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

TestScreen::TestScreen(BARE2D::Window* window, BARE2D::InputManager* input) : BARE2D::Screen(), m_window(window), m_inputManager(input)
{
}

TestScreen::~TestScreen()
{
}
void TestScreen::destroyScreen()
{
}

void TestScreen::draw()
{
	glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	m_fbo->begin();
	
	m_renderer->begin();
	
	float depth = -1.0f;

	for(unsigned int i = 0; i < 55; i++) {
		for(unsigned int j = 0; j < 25; j++) {
			glm::vec2 pos = glm::vec2(-350.0f, -250.0f);
			glm::vec2 size = glm::vec2(126.0f, 201.0f) * 0.1f;
			
			depth += 1.6f / (55.0f*25.0f);
			
			m_renderer->draw(glm::vec4(pos.x + i * size.x, pos.y + j * size.y, size.x, size.y), glm::vec4(0.0f, 1.0f, 1.0f, -1.0f), m_texture.id, depth);
		}
	}
	
	
	m_renderer->end();
	m_renderer->render();
	
	m_fbo->end();
	
	m_fbo->render();
	
	m_fontRenderer->begin();
	
	float fps = (60.0/updateCount)*renderCount;
	
	m_fontRenderer->draw(m_font_openSans, glm::vec2(1.0f), glm::vec4(-400.0f, -300.0f, 1.0f, 1.0f), std::string("Updates: " + std::to_string((int)(updateCount)) + "\nDraw Calls: " + std::to_string((int)renderCount) + "\nFPS: " + std::to_string(fps)).c_str(), 0.0f, BARE2D::Colour(255, 255, 255, 255));
	
	m_fontRenderer->end();
	m_fontRenderer->render();


	m_gui->draw();
	
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
	
	for(unsigned int i = 0; i < slowFactor; i++) {
		
	}
}

unsigned int TestScreen::getNextScreenIndex()
{
	return 0;
}

void TestScreen::initScreen()
{
}

void TestScreen::onEntry()
{
	BARE2D::initGLErrorCallback(BARE2D::GLErrorSeverity::LOW);
	
	m_position = glm::vec2(0.0f);
	
	BARE2D::Logger::getInstance()->log("Entering screen! Will display pretty colours for a bit, then shrink, then leave!");
	
	// Load a texture
	std::string texPath = "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/0000.png";
	m_texture = BARE2D::ResourceManager::loadTexture(texPath);
	
	// Load a shader
	std::string vShaderPath = "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/Shader.vert";
	std::string fShaderPath = "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/Shader.frag";
	
	// Load another FBO shader
	std::string fShaderPath_fbo = "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/ShaderFBO.frag";
	
	m_renderer = new BARE2D::BasicRenderer(fShaderPath, vShaderPath, m_window->getWidth(), m_window->getHeight());
	m_renderer->init();
	
	m_fbo = new BARE2D::FBORenderer(fShaderPath_fbo, vShaderPath, m_window->getWidth(), m_window->getHeight(), glm::vec2(m_window->getWidth(), m_window->getHeight()));
	m_fbo->init();
	
	std::string fontPath = "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/OpenSans-Regular.ttf";
	m_font_openSans = BARE2D::ResourceManager::loadFont(fontPath, 36);
	
	m_fontRenderer = new BARE2D::FontRenderer(fShaderPath, vShaderPath);
	m_fontRenderer->init();
	m_fontRenderer->setCamera(m_renderer->getCamera());
	
	m_debugRenderer = new BARE2D::DebugRenderer();
	m_debugRenderer->init();
	
	m_luaEngine.init("/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/Lua/PrintTest.lua");
	m_luaEngine.registerCFunction(lua_setWindowSize, "setWindowSize");
	BARE2D::LuaScriptEngine::addValueToRegistry(m_luaEngine.getMasterState(), m_window, LUA_WINDOW_REGISTRY_KEY);
	
	std::string scriptPath = "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/Lua/PrintTest.lua";
	BARE2D::LuaScript scr = BARE2D::ResourceManager::loadScript(scriptPath);
	BARE2D::LuaScriptQueue::getInstance()->addLuaScript(scr);
	
	std::string guiPath = "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/GUI";
	m_gui = BARE2D::BARECEGUI::getInstance();
	m_gui->init(guiPath, 1);
	m_gui->loadScheme("WindowsLook.scheme");
	m_gui->setFont("Junicode-13");
	CEGUI::FrameWindow* win = static_cast<CEGUI::FrameWindow*>(m_gui->createWidget("WindowsLook/FrameWindow", glm::vec4(0.25f, 0.25f, 0.5f, 0.5f), glm::vec4(0.0f)));
	win->setText("Look ma! It's a FrameWindow!");
	
	m_audioManager = BARE2D::AudioManager::getInstance();
	m_audioManager->init();
	
	std::string musicPath = "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/SampleMusic.mus";
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
	
	if(std::abs(m_time - 240.0f) <= 0.01f || std::abs(m_time - 720.0f) <= 0.01f) {
		BARE2D::Logger::getInstance()->log("Shrinking (Done by script)! " + std::to_string(renderCount) + " renders versus " + std::to_string(updateCount) + " updates.");
		renderCount = 0;
		updateCount = 0;
	}
	if(std::abs(m_time - 480.0f) <= 0.01f) {
		slowFactor = 80000000;
		BARE2D::Logger::getInstance()->log("Now emulating very very heavy rendering. " + std::to_string(renderCount) + " renders versus " + std::to_string(updateCount) + " updates.");
		renderCount = 0;
		updateCount = 0;
	}
	if(m_time >= 960.0f) {
		m_screenState = BARE2D::ScreenState::EXIT_APPLICATION;
		BARE2D::Logger::getInstance()->log("Finished heavy rendering. " + std::to_string(renderCount) + " renders versus " + std::to_string(updateCount) + " updates.");
	}
	
	updateCount++;
	
	float scroll = m_inputManager->getMouseScrollwheelPosition();
	
	if(std::abs(scroll) > 0.000001f) {
		float scaleNudge = scroll * m_fbo->getCamera()->getScaleX() / 2.0f;
		m_fbo->getCamera()->offsetScale(scaleNudge, scaleNudge);
	}
	
	m_luaEngine.update();
	m_gui->update();
}
