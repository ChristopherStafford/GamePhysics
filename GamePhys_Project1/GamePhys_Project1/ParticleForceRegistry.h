#ifndef PARTICLEFORCEGENERATOR_H
#define PARTICLEfORCEGENERATOR_H

#include <vector>
#include "ForceGenerator.h"

class ParticleForceRegistry
{
public:
	ParticleForceRegistry();
	vector<ForceRegistration> forces;

	void addRegistry(ForceRegistration fg);
	void update();
};

#endif