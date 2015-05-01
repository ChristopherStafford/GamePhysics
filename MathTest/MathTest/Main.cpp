#ifndef MAIN_CPP
#define MAIN_CPP

#include <stdlib.h>
#include <stdio.h>

#include "Game.h"

using namespace std;

bool forwardDown;
bool backwardDown;
bool leftDown;
bool rightDown;
bool showDebug;
vector<bool> numPressed;
bool resetSim;
bool lockMouse;

int main(int argc, char *argv[])
{
	Game *game = new Game();

	if (game->init(argc, argv))
	{
		game->gameLoop();
	}

	game->cleanup();
	delete game;

	system("pause");
	return 0;
	return 0;
}

#endif