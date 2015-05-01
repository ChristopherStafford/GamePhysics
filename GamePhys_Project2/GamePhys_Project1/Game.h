#ifndef GAME_H
#define GAME_H

#include "GraphicsSystem.h"
#include "Planet.h"
#include "Color.h"

#include "GravityForceGenerator.h"
#include "ParticleSystem.h"

#include "Ground.h"
#include "Objects.h"
#include "GroundContactGenerator.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>

#include "Cable.h"
#include "Rod.h"
#include "Spring.h"
#include "Bungie.h"

using namespace std;

class Game
{

private:
	GraphicsSystem *graphics;

	vector<GroundPlane*> planes;
	vector<Blob*> blobs;
	vector<Pickup*> pickups;

	Blob* player;

	Text debugText;

	void handlePlayerMovement();
	void handlePickups();
	void handleDebugText();
	string debugLine(string name, Particle* p);

	void buildCube(string name, Color cEdge, Color cVert, double size, double mass, double length, Vector3 pos);
	void buildTetrahedron(string name, Color cEdge, Color cVert, double size, double mass, double length, Vector3 pos);
	void buildTriangleLoaf(string name, Color cEdge, Color cVert, double size, double mass, double triLength, double edgeLength, Vector3 pos);
	

	bool loadLevel(string levelName);


public:
	Game();
	~Game();

	bool init(int argc, char *argv[]);
	void cleanup();
	void gameLoop();
	ParticleSystem* ps;

	double timeScale;

	void applyGravity();
	void applyContacts();
	void initParticles();
	void buildLevel();

	void resetBlobs();
	void resetPlanes();

	void connectWithCable(Particle* p1, Particle* p2, Color color, double restitution, double length);
	void connectWithRod(Particle* p1, Particle* p2, Color color, double length);
	void connectWithSpring(Particle* p1, Particle* p2, Color color, double spr, double rest);
	void connectWithBungie(Particle* p1, Particle* p2, Color color, double spr, double rest);

	GroundPlane* createPlane(string name, Color color, Vector3 pos);
	Blob* createBlob(string name, Color color, double mass, double size, Vector3 pos);
	Pickup* createPickup(string name, Color color, double mass, double size, Vector3 pos, ConnectionType type, double grabDist);

	


};

#endif