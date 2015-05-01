#ifndef PLANETARYGRAVITYGENERATOR_H
#define PLATETARYGRAVITYGENERATOR_H

#include "Vector3.h"
#include "ForceGenerator.h"

const double SPACE_GRAVITY = 6.67384 * pow(10, -11);

class PlanetaryGravityGenerator : public ForceGenerator
{
public:
	PlanetaryGravityGenerator();

	void updateForce(Particle* particle, double duration){};
	void updateForce(Particle* particle, Particle* particle2, double duration);
};

#endif;