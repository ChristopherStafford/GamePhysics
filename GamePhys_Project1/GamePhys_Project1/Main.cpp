#ifndef MAIN_CPP
#define MAIN_CPP

//#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "Globals.h"

double deltaTime;
double timeSinceLaunch;

bool forwardDown;
bool backwardDown;
bool leftDown;
bool rightDown;
bool showDebug;
vector<bool> numPressed;
bool resetSim;

int main(int argc, char *argv[])
{
	forwardDown = false;
	backwardDown = false;
	leftDown = false;
	rightDown = false;
	numPressed.resize(10, false);
	showDebug = true;
	resetSim = false;

	Game *game = new Game();

	if (game->init(argc, argv))
	{
		game->gameLoop();
	}

	game->cleanup();
	delete game;

	system("pause");
	return 0;
}
#endif
