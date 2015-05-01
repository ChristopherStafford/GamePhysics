#ifndef GRAVITYFORCEGENERATOR_H
#define GRAVITYFORCEGENERATOR_H

#include "Vector3.h"
#include "ForceGenerator.h"

class GravityForceGenerator : public ForceGenerator
{
public:
	GravityForceGenerator(const Vector3& newGravity);

	Vector3 gravity;

	void updateForce(Particle* particle, double duration);
	void updateForce(Particle* particle, Particle* particle2, double duration);
};

#endif;