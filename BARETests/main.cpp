#include <stdio.h>

#include <BARE2DEngine.hpp>
#include <App.hpp>
#include <Window.hpp>

#include "TestScreen.h"

int main(int argc, char **argv)
{
	BARE2D::App app;
	app.getWindow()->setSize(800, 600);
	
	TestScreen* screen = new TestScreen(app.getWindow(), app.getInputManager());
	
	app.getScreenList()->addEntryScreen(screen);
	
	app.run();
	
	return 0;
}
