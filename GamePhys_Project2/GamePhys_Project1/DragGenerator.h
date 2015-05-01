#ifndef DRAGGENERATOR_H
#define DRAGGENERATOR_H

#include "Vector3.h"
#include "ForceGenerator.h"

class DragGenerator : public ForceGenerator
{
public:
	DragGenerator(double ka, double kb);

	double k1;
	double k2;

	void updateForce(Particle* particle, double duration);
	void updateForce(Particle* particle, Particle* particle2, double duration);
};

#endif;