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
	
	//glClearColor(std::cos(m_time / 10000.0f)/2.0f + 0.5f, std::cos(m_time / 20000.0f)/2.0f + 0.5f, std::cos(m_time / 30000.0f)/2.0f + 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	m_renderer->begin();
	
	m_renderer->draw(glm::vec4(-0.8f, -0.8f, 1.6f, 1.6f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), m_texture.id, 0.0f);

	m_renderer->end();
	m_renderer->render();
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
	BARE2D::Logger::getInstance()->log("Entering screen! Will display pretty colours for a bit, then shrink, then leave!");
	
	// Load a texture
	std::string texPath = "/home/davis-dev/Downloads/0000.png";
	m_texture = BARE2D::ResourceManager::loadTexture(texPath);
	
	// Load a shader
	std::string vShaderPath = "/home/davis-dev/Downloads/Shader.vert";
	std::string fShaderPath = "/home/davis-dev/Downloads/Shader.frag";
	
	m_renderer = new BARE2D::BasicRenderer(fShaderPath, vShaderPath);
	m_renderer->init();
}

void TestScreen::onExit()
{
	BARE2D::Logger::getInstance()->log("Leaving screen!");
}

void TestScreen::update()
{
	m_time++;
	if((int)m_time % 2000 == 0) {
		BARE2D::Logger::getInstance()->log("Cycles: " + std::to_string((int)m_time));
	}
	
	if(std::abs(m_time - 50000.0f) <= 0.01f) {
		m_window->setSize(300, 300);
		BARE2D::Logger::getInstance()->log("Shrinking!");
	}
	if(m_time > 100000.0f) {
		m_screenState = BARE2D::ScreenState::EXIT_APPLICATION;
	}
}
