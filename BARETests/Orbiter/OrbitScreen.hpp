#pragma once

#include <Screen.hpp>
#include <BasicRenderer.hpp>
#include <DebugRenderer.hpp>
#include <Window.hpp>
#include <ResourceManager.hpp>
#include <InputManager.hpp>

#include <vector>

#include "Body.hpp"

class OrbitScreen : public BARE2D::Screen {
	public:
		OrbitScreen(BARE2D::Window* window, BARE2D::InputManager* input);
		~OrbitScreen();

		virtual void destroyScreen();
		virtual void draw();
		virtual int getNextScreenIndex() const;
		virtual void initScreen();
		virtual void onEntry();
		virtual void onExit();
		virtual void update(double dt);

	private:
		virtual void loadAssets();

		std::vector<Body*> m_bodies;

		glm::vec2 m_lastMouse;

		BARE2D::BasicRenderer* m_renderer = nullptr;
		BARE2D::BasicRenderer* m_regrenderer = nullptr;
		BARE2D::DebugRenderer* m_debugRenderer = nullptr;
		BARE2D::Window* m_window;
		BARE2D::Texture m_planetTexture;
		BARE2D::Texture m_starsTexture;
		BARE2D::InputManager* m_input;
};
