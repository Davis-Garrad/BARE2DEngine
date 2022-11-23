#pragma once

#include <memory>
#include <vector>

#include <BasicRenderer.hpp>
#include <DebugRenderer.hpp>
#include <InputManager.hpp>
#include <ResourceManager.hpp>
#include <Screen.hpp>
#include <Window.hpp>

#include "Boid.hpp"

class AppScreen : public BARE2D::Screen
{
   public:
    AppScreen(BARE2D::Window* window, BARE2D::InputManager* input);
    ~AppScreen();

    virtual void destroyScreen();
    virtual void draw();
    virtual int getNextScreenIndex() const;
    virtual void initScreen();
    virtual void onEntry();
    virtual void onExit();
    virtual void update(double dt);

   private:
    BARE2D::Window* m_window = nullptr;
    BARE2D::InputManager* m_inputManager = nullptr;

    BARE2D::BasicRenderer* m_renderer = nullptr;
    BARE2D::DebugRenderer* m_debug = nullptr;

    BARE2D::Texture m_boidTexture;

    std::shared_ptr<BARE2D::Camera2D> m_camera;

    std::vector<Boid*> m_boids;

    glm::vec2 m_lastMouse;
};
