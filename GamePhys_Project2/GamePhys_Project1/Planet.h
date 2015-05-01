#ifndef PLANET_H
#define PLANET_H

#include "Particle.h"
#include "Color.h"

class Planet : public Particle
{
protected:


	//for reset
	Vector3 startPosition;
	Vector3 startVelocity;

public:
	Planet(string nm, double size, double m, double distance, double speed, Color c);
};

#endif