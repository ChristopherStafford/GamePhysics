#include "ParticleForceRegistry.h"

ParticleForceRegistry::ParticleForceRegistry()
{
	forces = vector<ForceRegistration>();
}

void ParticleForceRegistry::addRegistry(ForceRegistration fg)
{
	forces.push_back(fg);
}

void ParticleForceRegistry::update()
{
	for (size_t i = 0; i < forces.size(); i++)
	{
		if (forces[i].twoParticles)
		{
			forces[i].fg->updateForce(forces[i].particle, forces[i].exertParticle, deltaTime);
		}
		else
		{
			forces[i].fg->updateForce(forces[i].particle, deltaTime);
		}
	}
}