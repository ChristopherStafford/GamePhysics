#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H

#include "Globals.h"
#include "Camera.h"
#include "Cube.h"
#include "Text.h"
#include "Particle.h"
#include "Vector2.h"

class GraphicsSystem
{

private:
	GLFWwindow* window;
	string winName;
	Vector2 winSize;
	double mouseSensitivity;


public:
	GraphicsSystem();
	bool init(int argc, char *argv[]);
	void cleanup();

	Camera* cam;

	GLFWwindow* getWindow();

	void startDraw();
	void endDraw();

	Vector2 handleMouseMovement();
	void reset();
};

#endif