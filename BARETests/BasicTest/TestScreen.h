#pragma once

#include <Screen.hpp>
#include <Window.hpp>
#include <ShaderProgram.hpp>
#include <Texture.hpp>
#include <BasicRenderer.hpp>
#include <FBORenderer.hpp>
#include <FontRenderer.hpp>
#include <DebugRenderer.hpp>
#include <InputManager.hpp>

class TestScreen : public BARE2D::Screen
{
public:
    TestScreen(BARE2D::Window* window, BARE2D::InputManager* input);
    ~TestScreen();
	
    virtual void initScreen() override;
	virtual void destroyScreen() override;
	
    virtual void onEntry() override;
    virtual void onExit() override;
	
    virtual void draw() override;
    virtual void update(double dt) override;
	
    virtual unsigned int getNextScreenIndex() override;
	
	unsigned int slowFactor = 0;
private:
	float m_time = 0;
	
	BARE2D::Window* m_window = nullptr;
	BARE2D::InputManager* m_inputManager = nullptr;
	
	BARE2D::FBORenderer* m_fbo = nullptr;
	BARE2D::BasicRenderer* m_renderer = nullptr;
	BARE2D::FontRenderer* m_fontRenderer = nullptr;
	BARE2D::DebugRenderer* m_debugRenderer = nullptr;
	BARE2D::Texture m_texture;
	BARE2D::Font m_font_openSans;
	
	glm::vec2 m_position;
	
	glm::vec2 m_lastMouse;
	
	unsigned int renderCount = 0, updateCount = 0;
};
