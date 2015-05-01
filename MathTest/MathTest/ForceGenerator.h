#ifndef FORCEGENERATOR_H
#define FORCEGENERATOR_H

#include "RigidBody.h"
#include "Vector.h"

class ForceGenerator
{
public:
	virtual void updateForce(RigidBody *body, double duration){};
};

class Gravity : public ForceGenerator
{
	Vector3 gravity;
public:
	Gravity(const Vector3 &g){ gravity = g; };
	virtual void updateForce(RigidBody *body, double duration);
};

class Spring : public ForceGenerator
{
	Vector3 connectionPoint;
	Vector3 otherConnectionPoint;
	RigidBody *other;
	double springConstant;
	double restLength;

public:
	Spring(Vector3 localConnectionPt,
		RigidBody *otherOb,
		Vector3 otherConnectionPt,
		double sc,
		double length);

	virtual void updateForce(RigidBody *body, double duration);
};
#endif