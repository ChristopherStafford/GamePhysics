#ifndef PARTICLE_H
#define PARTICLE_H

#include <windows.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>


#include <gl/freeglut.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Vector3.h"
#include "Globals.h"
//#include "Transform.h"
#include <iostream>
#include "Color.h"

class Particle
{

protected:
	//Transform transform;
	Vector3 position;
	Vector3 rotation;
	Vector3 velocity;
	Vector3 acceleration;

	Vector3 initPosition;
	Vector3 initRotation;
	Vector3 initVelocity;
	Vector3 initAcceleration;

	Vector3 forceAcumulation;
	string name;
	double dampening;
	double mass;

	GLUquadricObj *quadric;

	double radius;
	int stacks;
	int slices;

	Color color;

	double sizeScale;
	double positionScale;

public:
	Particle();
	Particle(double x, double y, double z);

	void init();
	void draw();
	void update();

	void integrate();
	bool hasFiniteMass(){ return (inverseMass() > 0); };

	//Transform getTransform(){ return transform; };
	Vector3 getPosition(){ return position; };
	Vector3 getRotation(){ return rotation; };
	Vector3 getVelocity(){ return velocity; };
	Vector3 getAcceleration(){ return acceleration; };

	double getMass(){ return mass; };

	void addForce(Vector3 forceVector);
	void clearAccumulator();

	double getSizeScale(){ return sizeScale; };
	double getPositionScale(){ return positionScale; };

	void setSizeScale(double ss){ sizeScale = ss; };
	void setPositionScale(double ps){ positionScale = ps; };
	double inverseMass();
	string getName(){ return name; };

	void reset();
};
#endif