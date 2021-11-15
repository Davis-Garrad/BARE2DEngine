#include "TestScreen.h"

#include <math.h>
#include <GL/gl.h>
#include <Logger.h>

TestScreen::TestScreen() : BARE2D::Screen()
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(std::cos(m_time / 10000.0f)/2.0f + 0.5f, std::cos(m_time / 20000.0f)/2.0f + 0.5f, std::cos(m_time / 30000.0f)/2.0f + 0.5f, 1.0f);
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
	BARE2D::Logger::getInstance()->log("Entering screen! Will display pretty colours for a bit.");
}

void TestScreen::onExit()
{
	BARE2D::Logger::getInstance()->log("Leaving screen!");
}

void TestScreen::update()
{
	m_time++;
	if(m_time > 100000.0f) {
		m_screenState = BARE2D::ScreenState::EXIT_APPLICATION;
	}
}
