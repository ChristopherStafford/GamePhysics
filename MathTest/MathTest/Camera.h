#ifndef CAMERA_H
#define CAMERA_H

#include <windows.h>
#include <GL/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#include "Vector.h"
#include "Globals.h"
#include <sstream>
//#include "Text.h"
#include <vector>
#include <math.h>

struct CamSpecs
{
	CamSpecs()
	{
		fov = 45;
		aspectRatio = 1;
		nearClip = 0.01f;
		farClip = 1000;
	}
	float fov;
	float aspectRatio;
	float nearClip;
	float farClip;
};

class Camera
{

private:
	Vector3 position;
	Vector3 rotation;
	Vector3 velocity;

	Vector3 initialPosition;
	Vector3 initialRotation;

	CamSpecs camSpecs;
	double moveSpeed;
	//Particle* lookTarget;

	Vector3 offset;
	//Text debugText;
	bool targeted;

	void handleMovement();
	void handleMouse();

public:
	Camera();
	Camera(float x, float y, float z);
	void init();
	void setCamSpecs(float fov, float aspectRatio, float nearClip, float farClip);

	Vector3 getPosition(){ return position; };
	Vector3 getRotation(){ return rotation; };
	Vector3 getVelocity(){ return velocity; };

	//void update();
	void draw(Vector2 mouseDelta);

	double degToRad(double angle);

	float getFov(){ return camSpecs.fov; };
	float getAspectRatio(){ return camSpecs.aspectRatio; };
	float getNearClip(){ return camSpecs.nearClip; };
	float getFarClip(){ return camSpecs.farClip; };
	//void setTarget(Particle* p);
	void reset();
};

#endif