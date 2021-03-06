#pragma once

#include <Screen.hpp>
#include <Window.hpp>
#include <ShaderProgram.hpp>
#include <Texture.hpp>
#include <BumpyRenderer.hpp>
#include <FBORenderer.hpp>
#include <FontRenderer.hpp>
#include <DebugRenderer.hpp>
#include <InputManager.hpp>
#include <LuaScriptEngine.hpp>
#include <BARECEGUI.hpp>
#include <AudioManager.hpp>

class TestScreen : public BARE2D::Screen {
	public:
		TestScreen(BARE2D::Window* window, BARE2D::InputManager* input);
		~TestScreen();

		virtual void initScreen() override;
		virtual void destroyScreen() override;

		virtual void onEntry() override;
		virtual void onExit() override;

		virtual void draw() override;
		virtual void update(double dt) override;

		virtual int getNextScreenIndex() const override;

		unsigned int slowFactor = 0;
	private:
		float m_time = 0;

		BARE2D::Window* m_window = nullptr;
		BARE2D::InputManager* m_inputManager = nullptr;

		BARE2D::FBORenderer* m_fbo = nullptr;
		BARE2D::BumpyRenderer* m_renderer = nullptr;
		BARE2D::FontRenderer* m_fontRenderer = nullptr;
		BARE2D::DebugRenderer* m_debugRenderer = nullptr;
		BARE2D::Texture m_texture;
		BARE2D::Texture m_textureNormal;
		BARE2D::Font m_font_openSans;
		BARE2D::LuaScriptEngine m_luaEngine;
		BARE2D::BARECEGUI* m_gui = nullptr;
		BARE2D::AudioManager* m_audioManager = nullptr;

		glm::vec2 m_position;

		glm::vec2 m_lastMouse;

		unsigned int renderCount = 0, updateCount = 0;
};
