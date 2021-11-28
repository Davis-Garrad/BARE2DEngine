#include <App.hpp>

#include "AppScreen.hpp"

int main(int argc, char **argv)
{
	BARE2D::App app;
	
	app.getWindow()->setSize(1000, 600);
	app.getWindow()->setTitle("Boids!");
	
	app.getScreenList()->addEntryScreen(new AppScreen(app.getWindow(), app.getInputManager()));
	
	app.run();
	
	
	return 0;
}
