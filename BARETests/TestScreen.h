#pragma once

#include <Screen.h>

class TestScreen : public BARE2D::Screen
{
public:
    TestScreen();
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
};
