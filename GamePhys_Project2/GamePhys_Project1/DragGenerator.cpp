#include "DragGenerator.h"

DragGenerator::DragGenerator(double ka, double kb)
	:ForceGenerator()
{
	k1 = ka;
	k2 = kb;
}

void DragGenerator::updateForce(Particle* particle, double duration)
{
	//get velocity
	//calculate drag force
	//particle->addForce(force);
}

void DragGenerator::updateForce(Particle* particle, Particle* particle2, double duration)
{
	//get velocity
	//calculate drag force
	//particle->addForce(force);
}