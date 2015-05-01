#ifndef GAME_H
#define GAME_H

#include "GraphicsSystem.h"
#include "Planet.h"
#include "Color.h"
#include <vector>
#include "PlanetaryGravityGenerator.h"
#include "ParticleSystem.h"
#include <sstream>
class Game
{

private:
	GraphicsSystem *graphics;

public:
	Game();
	~Game();

	bool init(int argc, char *argv[]);
	void cleanup();
	void gameLoop();
	ParticleSystem* ps;

	double timeScale;

	void applyGravity();
	void initSolarSystem();

};

#endif