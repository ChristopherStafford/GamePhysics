#ifndef FORCEREGISTRATION_H
#define FORCEREGISTRATION_H

#include "RigidBody.h"
#include "ForceGenerator.h"

class ForceRegistration
{
public:
	ForceRegistration(RigidBody* p, ForceGenerator* nfg)
	{
		rigidBody = p;
		fg = nfg;
		twoParticles = false;
	}

	ForceRegistration(RigidBody* rb, RigidBody* rb2, ForceGenerator* nfg)
	{
		rigidBody = rb;
		exertRigidBody = rb2;
		twoParticles = true;
	}

	bool twoParticles;
	RigidBody* rigidBody;
	RigidBody* exertRigidBody;
	ForceGenerator* fg;
};
#endif