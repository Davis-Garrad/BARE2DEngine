#include "OrbitScreen.hpp"

#include <Camera2D.hpp>

#include <string>

OrbitScreen::OrbitScreen(BARE2D::Window* window, BARE2D::InputManager* input) : m_window(window), m_input(input)
{
}

OrbitScreen::~OrbitScreen()
{
}
void OrbitScreen::destroyScreen()
{
}

void OrbitScreen::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	m_regrenderer->begin();
	
	m_regrenderer->draw(glm::vec4(-1.0f, -1.0f, 2.0f, 2.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), m_starsTexture.id, 0.0f, BARE2D::Colour(255, 255, 255, 128));
	
	m_regrenderer->end();
	m_regrenderer->render();
	
	m_renderer->begin();
	
	for(unsigned int i = 0; i < m_bodies.size(); i++) {
		glm::vec4 destRect = glm::vec4(m_bodies[i]->pos.x, m_bodies[i]->pos.y, m_bodies[i]->radius * 2, m_bodies[i]->radius * 2);
		
		m_renderer->draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), m_planetTexture.id, 0.0f);
	}
	
	m_renderer->end();
	m_renderer->render();
}

unsigned int OrbitScreen::getNextScreenIndex()
{
	return 0;
}

void OrbitScreen::initScreen()
{
}

void OrbitScreen::onEntry()
{
	loadAssets();
	
	// Two stable orbits - zoom out to see em
	m_bodies.push_back(new Body(glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 100.0f), 5.97e10, 6.3e3));
	m_bodies.push_back(new Body(glm::vec2(38400.0f, 0.0f), glm::vec2(0.0f, 100.0f-37.0f), 7.30e10, 1.7e3));
	
	
	m_bodies.push_back(new Body(glm::vec2(-700000.0f, 0.0f), glm::vec2(0.0f, -150.0f), 5.97e18, 6.3e3));
	m_bodies.push_back(new Body(glm::vec2(38400.0f - 700000.0f, 0.0f), glm::vec2(0.0f, -200.0f), 7.30e18, 1.7e3));
	
	m_bodies.push_back(new Body(glm::vec2(38400.0f - 400000.0f, 0.0f), glm::vec2(0.0f, 0.0f), 1.30e21, 1.7e4));
}

void OrbitScreen::onExit()
{
	delete m_renderer;
	delete m_regrenderer;
	
	for(unsigned int i = 0; i < m_bodies.size(); i++) {
		delete m_bodies[i];
	}
	
	m_bodies.clear();
}

void OrbitScreen::loadAssets() {
	if(m_renderer) delete m_renderer;
	if(m_regrenderer) delete m_regrenderer;
	
	std::string fragShader = "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/Shader.frag";
	std::string vertShader = "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/Shader.vert";
	
	std::string texturePath = "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/planet.png";
	std::string starsPath = "/home/davis-dev/Documents/Programming/C++/CodingGithub/BARE2DEngine/BARETests/stars.png";
	
	m_planetTexture = BARE2D::ResourceManager::loadTexture(texturePath);
	m_starsTexture = BARE2D::ResourceManager::loadTexture(starsPath);
	
	m_renderer = new BARE2D::BasicRenderer(fragShader, vertShader, m_window->getWidth(), m_window->getHeight());
	m_renderer->init();
	
	
	m_regrenderer = new BARE2D::BasicRenderer(fragShader, vertShader);
	m_regrenderer->init();
}

void OrbitScreen::update(double dt)
{
	for(unsigned int i = 0; i < m_bodies.size(); i++) {
		m_bodies[i]->update(m_bodies);
	}
	
	float scroll = m_input->getMouseScrollwheelPosition();
	
	if(std::abs(scroll) > 0.000001f)
		m_renderer->getCamera()->offsetScale(scroll * m_renderer->getCamera()->getScale() / 2.0f);
		
	if(m_input->isKeyDown(SDL_BUTTON_LEFT)) {
		glm::vec2 movement = m_lastMouse - m_input->getMousePosition() * glm::vec2(1.0f, -1.0f);
		movement /= m_renderer->getCamera()->getScale();
		m_renderer->getCamera()->offsetPosition(movement);
	}
	m_lastMouse = m_input->getMousePosition() * glm::vec2(1.0f, -1.0f);
	
	if(m_input->isKeyPressed(SDLK_F1)) {
		// Reload cache
		BARE2D::ResourceManager::clearCaches();
		// Reload assets
		loadAssets();
	}
}
