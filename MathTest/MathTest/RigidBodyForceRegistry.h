#ifndef RIGIDBODYFORCEGENERATOR_H
#define RIGIDBODYFORCEGENERATOR_H

#include <vector>
#include "ForceGenerator.h"
#include "ForceRegistration.h"

class RigidBodyForceRegistry
{
public:
	RigidBodyForceRegistry();
	vector<ForceRegistration> forces;

	void addRegistry(ForceRegistration fr);
	void update(double duration);
};

#endif