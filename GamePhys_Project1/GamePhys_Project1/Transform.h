#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <windows.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>


#include <gl/freeglut.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>

#include "Vector3.h"
#include "Globals.h"

class Transform
{

protected:
	Vector3 position;
	Vector3 rotation;
	Vector3 velocity;
	Vector3 acceleration;

	double dampening;
	double inverseMass;

public:
	Transform();
	Transform(float x, float y, float z);
	void update();
	void integrate(double duration);
	bool hasFiniteMass(){ return (inverseMass > 0); };

	Vector3 getPosition(){ return position; };
	Vector3 getRotation(){ return rotation; };
	Vector3 getVelocity(){ return velocity; };
	Vector3 getAcceleration(){ return acceleration; };

	

};
#endif