#ifndef GROUND_H
#define GROUND_H

#include "Particle.h"
#include "Color.h"

class Ground : public Particle
{
protected:
	Vector3 size;

	//for reset
	Vector3 startPosition;
	Vector3 startVelocity;

public:
	Ground(double x, double y, double z, Color c);

	void draw();
};

#endif