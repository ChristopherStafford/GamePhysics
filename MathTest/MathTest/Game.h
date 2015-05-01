#ifndef GAME_H
#define GAME_H

#include "World.h"
#include "Camera.h"
#include "ForceGenerator.h"
#include "Globals.h"

#include <windows.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/freeglut.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

class Game
{
private:
	World* rbWorld;
	
	//graphics
	GLFWwindow* window;
	Camera* viewCam;

	string winName;
	Vector2 winSize;
	double mouseSensitivity;

	Vector2 handleMouseMovement();
	double deltaTime;
	double timeSinceLaunch;


public:
	Game();
	bool init(int argc, char *argv[]);
	bool initGraphics(int argc, char *argv[]);

	void gameLoop();

	void startDraw();
	void endDraw();
	void cleanup();


};

#endif