#include "TestScreen.h"

#include <math.h>
#include <GL/glew.h>
#include <Logger.hpp>
#include <Window.hpp>
#include <ResourceManager.hpp>

TestScreen::TestScreen(BARE2D::Window* window) : BARE2D::Screen(), m_window(window)
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
	glClearColor(std::cos(m_time / 10.0f)/2.0f + 0.5f, std::cos(m_time / 20.0f)/2.0f + 0.5f, std::cos(m_time / 30.0f)/2.0f + 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	m_renderer->begin();
	
	m_renderer->draw(glm::vec4(100.0f, 100.0f, 400.0f, 400.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), m_texture.id, 0.0f);

	m_renderer->end();
	m_renderer->render();
	
	m_fontRenderer->begin();
	
	m_fontRenderer->draw(m_font_openSans, glm::vec2(1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), "Test Text", 0.0f, BARE2D::Colour(0, 255, 0, 255));
	
	m_fontRenderer->end();
	m_fontRenderer->render();
	
	float radians = m_time * M_PI * 2.0f / 60.0f;
	float x = 0.6f * std::cos(radians);
	float y = 0.6f * std::sin(radians);
	
	m_debugRenderer->begin();
	m_debugRenderer->drawCircle(glm::vec2(0.0f, 0.0f), 3.0f, 0.6f, BARE2D::Colour(0, 255, 0, 64));
	m_debugRenderer->drawLine(glm::vec2(0.0f, 0.0f), glm::vec2(x, y), 9.0f, BARE2D::Colour(255, 255, 255, 255));
	m_debugRenderer->drawLine(glm::vec2(0.0f, 0.0f), glm::vec2(-x, y), 3.0f, BARE2D::Colour(255, 255, 255, 255));
	m_debugRenderer->drawRectangle(glm::vec4(0.0f, 0.0f, 0.4f, 0.4f), 3.0f, BARE2D::Colour(255, 255, 255, 64));
	m_debugRenderer->end();
	m_debugRenderer->render();
	
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
	m_position = glm::vec2(0.0f);
	
	BARE2D::Logger::getInstance()->log("Entering screen! Will display pretty colours for a bit, then shrink, then leave!");
	
	// Load a texture
	std::string texPath = "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/0000.png";
	m_texture = BARE2D::ResourceManager::loadTexture(texPath);
	
	// Load a shader
	std::string vShaderPath = "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/Shader.vert";
	std::string fShaderPath = "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/Shader.frag";
	
	m_renderer = new BARE2D::BasicRenderer(fShaderPath, vShaderPath);
	m_renderer->init();
	
	std::string fontPath = "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/OpenSans-Regular.ttf";
	
	m_font_openSans = BARE2D::ResourceManager::loadFont(fontPath, 128);
	
	m_fontRenderer = new BARE2D::FontRenderer(fShaderPath, vShaderPath);
	m_fontRenderer->init();
	
	m_debugRenderer = new BARE2D::DebugRenderer();
	m_debugRenderer->init();
}

void TestScreen::onExit()
{
	BARE2D::Logger::getInstance()->log("Leaving screen!");
}

void TestScreen::update(double dt)
{
	m_time++;
	
	if(std::abs(m_time - 240.0f) <= 0.01f || std::abs(m_time - 720.0f) <= 0.01f) {
		m_window->setSize(300, 300);
		BARE2D::Logger::getInstance()->log("Shrinking!");
	}
	if(std::abs(m_time - 480.0f) <= 0.01f) {
		slowFactor = 200000000;
		m_window->setSize(800, 600);
		BARE2D::Logger::getInstance()->log("Now emulating very very heavy rendering. " + std::to_string(renderCount) + " renders versus " + std::to_string(updateCount) + " updates.");
		renderCount = 0;
		updateCount = 0;
	}
	if(m_time >= 960.0f) {
		m_screenState = BARE2D::ScreenState::EXIT_APPLICATION;
		BARE2D::Logger::getInstance()->log("Finished heavy rendering. " + std::to_string(renderCount) + " renders versus " + std::to_string(updateCount) + " updates.");
	}
	
	updateCount++;
}
