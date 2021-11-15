#include <stdio.h>

#include <BARE2DEngine.h>
#include <App.h>
#include <Window.h>

#include "TestScreen.h"

int main(int argc, char **argv)
{
	BARE2D::App app;
	app.getWindow()->setSize(800, 600);
	
	TestScreen* screen = new TestScreen();
	
	app.getScreenList()->addEntryScreen(screen);
	
	app.run();
	
	return 0;
}
