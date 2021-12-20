#include <stdio.h>

#include <App.hpp>

#include "OrbitScreen.hpp"

int main(int argc, char **argv)
{
	BARE2D::App app;
	
	app.getScreenList()->addEntryScreen(new OrbitScreen(app.getWindow(), app.getInputManager()));
	app.getWindow()->setSize(1000, 600);
	app.getWindow()->setTitle("Orbiter Demo");
	app.run();
	
	return 0;
}
