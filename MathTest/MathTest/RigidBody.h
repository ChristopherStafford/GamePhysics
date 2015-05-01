#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <assert.h>
#include <float.h>

#include "Quaternion.h"
#include "Vector.h"
#include "Matrix.h"
#include "Color.h"

#include <iostream>

#include <windows.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/freeglut.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

class RigidBody
{
protected:
	double inverseMass;
	
	double linearDampening;
	double angularDampening;

	bool isAwake;
	double motion;
	bool canSleep;

	Vector3 position;
	Quaternion orientation;
	Vector3 velocity;
	Vector3 rotation; //holds angular velocity
	Vector3 acceleration;
	Vector3 lastFrameAcceleration;


	Matrix4 transformMatrix;
	Matrix3 inverseInertiaTensor;
	Matrix3 inverseInertiaTensorWorld;

	Vector3 forceAccum;
	Vector3 torqueAccum;

public:
	RigidBody();

	void init();
	void setPos(Vector3 pos){ position = pos; };
	void calculateDerivedData();

	void setInertiaTensor(const Matrix3 &inertiaTensor);
	void getInertiaTensor(Matrix3* it);
	Matrix3 getInertiaTensor();
	void setInertiaTensorWorld(Matrix3 &inertiaTensor);
	void getInertiaTensorWorld(Matrix3 *inertiaTensor) const;
	Matrix3 getInertiaTensorWorld() const;

	void setInverseInertiaTensor(const Matrix3 &inverseInertiaTensor);
	void getInverseInertiaTensor(Matrix3 *inverseInertiaTensor) const;
	Matrix3 getInverseInertiaTensor() const;
	void getInverseInertiaTensorWorld(Matrix3 *inverseInertiaTensor) const;
	Matrix3 getInverseInertiaTensorWorld() const;

	void setOrientation(const Quaternion &o);
	void setOrientation(const double r, const double i, const double j, const double k);

	Vector3 getPosition(){ return position; };
	void setPosition(Vector3 pos){ position.copy(pos); };
	Vector3 getRotation(){ return rotation; };
	void setVelocity(Vector3 vel){ velocity.copy(vel); };
	Vector3 getVelocity(){ return velocity; };
	Vector3 getPreviousAcceleration(){ return lastFrameAcceleration; };
	Quaternion getOrientation(){ return orientation; };
	bool getAwake() { return isAwake; };
	void setAwake(bool tf=true){ isAwake = tf; };
	Matrix4 getTransform() { return transformMatrix; }

	void addVelocity(const Vector3 &delta){ velocity += delta; };
	void addRotation(const Vector3 &delta){ rotation += delta; };

	Vector3 getPointInWorldSpace(Vector3 point);

	void addForce(const Vector3 &force);
	void addForceAtPoint(const Vector3 &force, const Vector3 &point);
	void addForceAtBodyPoint(const Vector3 &force, const Vector3 &point);

	void clearAccumulators();
	void integrate(double duration);


	double getMass();
	double getInverseMass();
	void setMass(double mass);
	void setInverseMass(double im);
	bool hasFiniteMass();
	
	Color color;
	float radius;
	int slices;
	int stacks;
	virtual void draw();
};

#endif