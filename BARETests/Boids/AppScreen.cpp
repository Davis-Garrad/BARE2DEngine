#include "AppScreen.hpp"

#include <Filesystem.hpp>

#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

AppScreen::AppScreen(BARE2D::Window* window, BARE2D::InputManager* input) : m_window(window), m_inputManager(input)
{}

AppScreen::~AppScreen()
{}

void AppScreen::destroyScreen()
{}

void AppScreen::draw()
{
    glClearColor(154.0f / 255.0f, 203.0f / 255.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_renderer->begin();

    for(unsigned int i = 0; i < m_boids.size(); i++)
	{
	    glm::vec4 destRect(m_boids[i]->x, m_boids[i]->y, m_boids[i]->size, m_boids[i]->size);
	    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	    m_renderer->draw(destRect, uvRect, m_boidTexture.id, 0.0f);
	}

    m_renderer->end();
    m_renderer->render();

    m_debug->begin();

    for(unsigned int i = 0; i < m_boids.size(); i++)
	{
	    glm::vec4 destRect(m_boids[i]->x, m_boids[i]->y, m_boids[i]->size / 2, m_boids[i]->size / 2);
	    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	    glm::vec2 p0 = glm::vec2(destRect.x + destRect.z, destRect.y + destRect.w);
	    glm::vec2 p1 = p0 + glm::vec2(destRect.z, destRect.w) * m_boids[i]->direction * 3.0f;

	    glm::vec2 wind(m_window->getWidth() / 2, m_window->getHeight() / 2);

	    p0 = m_camera->getViewspaceCoord(p0) / wind;
	    p1 = m_camera->getViewspaceCoord(p1) / wind;

	    m_debug->drawLine(p0, p1, 2.0f, BARE2D::Colour(0, 255, 0, 255));
	}

    m_debug->end();
    m_debug->render();
}

int AppScreen::getNextScreenIndex() const
{
    return 0;
}

void AppScreen::initScreen()
{}

void AppScreen::onEntry()
{
    std::string fragShader = BARE2D::Filesystem::getWorkingDirectory() + "/../Shader.frag";
    std::string vertShader = BARE2D::Filesystem::getWorkingDirectory() + "/../Shader.vert";

    m_renderer = new BARE2D::BasicRenderer(fragShader, vertShader, m_window->getWidth(), m_window->getHeight());
    m_renderer->init();

    m_camera = m_renderer->getCamera();

    m_debug = new BARE2D::DebugRenderer();
    m_debug->init();

    std::string boidTex = BARE2D::Filesystem::getWorkingDirectory() + "/../planet.png";

    m_boidTexture = BARE2D::ResourceManager::loadTexture(boidTex);

    for(unsigned int i = 0; i < 200; i++)
	{
	    int x = std::rand() % 400;
	    int y = std::rand() % 400;

	    m_boids.emplace_back(new Boid(x - 200, y - 200, 10.0f));
	}
}

void AppScreen::onExit()
{}

void AppScreen::update(double dt)
{
    for(unsigned int i = 0; i < m_boids.size(); i++)
	{
	    m_boids[i]->update(m_boids);
	}

    float scroll = m_inputManager->getMouseScrollwheelPosition();

    if(std::abs(scroll) > 0.000001f)
	m_renderer->getCamera()->offsetScale(scroll * m_renderer->getCamera()->getScale().x / 2.0f,
	                                     scroll * m_renderer->getCamera()->getScale().y / 2.0f);

    if(m_inputManager->isKeyDown(SDL_BUTTON_LEFT))
	{
	    glm::vec2 movement = m_lastMouse - m_inputManager->getMousePosition() * glm::vec2(1.0f, -1.0f);
	    movement /= m_renderer->getCamera()->getScale().x;
	    m_renderer->getCamera()->offsetFocus(movement);
    }
    m_lastMouse = m_inputManager->getMousePosition() * glm::vec2(1.0f, -1.0f);
}
