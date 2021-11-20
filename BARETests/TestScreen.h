#pragma once

#include <Screen.hpp>
#include <Window.hpp>
#include <ShaderProgram.hpp>
#include <Texture.hpp>
#include <BasicRenderer.hpp>

class TestScreen : public BARE2D::Screen
{
public:
    TestScreen(BARE2D::Window* window);
    ~TestScreen();
	
    virtual void initScreen() override;
	virtual void destroyScreen() override;
	
    virtual void onEntry() override;
    virtual void onExit() override;
	
    virtual void draw() override;
    virtual void update() override;
	
    virtual unsigned int getNextScreenIndex() override;
private:
	float m_time = 0;
	
	BARE2D::Window* m_window = nullptr;
	BARE2D::BasicRenderer* m_renderer = nullptr;
	BARE2D::Texture m_texture;
};
