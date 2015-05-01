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
#include <iostream>
#include "Color.h"

class Particle
{

protected:
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

public:
	Particle();
	Particle(double x, double y, double z);
	Particle(double r, double m, Color c);

	void init();
	virtual void draw();
	void update();

	void integrate();
	bool hasFiniteMass(){ return (inverseMass() > 0); };

	Vector3 getPosition(){ return position; };
	Vector3 getRotation(){ return rotation; };
	Vector3 getVelocity(){ return velocity; };
	Vector3 getAcceleration(){ return acceleration; };

	void setPosition(Vector3 p){ position.copy(p); };
	void setRotation(Vector3 r){ rotation.copy(r); };
	void setVelocity(Vector3 v){ velocity.copy(v); };
	void setAcceleration(Vector3 a){ acceleration.copy(a); };

	double getMass(){ return mass; };
	double getRadius(){ return radius; };

	void addForce(Vector3 forceVector);
	void clearAccumulator();

	double inverseMass();
	string getName(){ return name; };

	void reset();

};
#endif