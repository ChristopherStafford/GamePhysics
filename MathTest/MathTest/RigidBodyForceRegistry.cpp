#include "RigidBodyForceRegistry.h"

RigidBodyForceRegistry::RigidBodyForceRegistry()
{
	forces = vector<ForceRegistration>();
}

void RigidBodyForceRegistry::addRegistry(ForceRegistration fr)
{
	forces.push_back(fr);
}

void RigidBodyForceRegistry::update(double duration)
{
	for (size_t i = 0; i < forces.size(); i++)
	{
		forces[i].fg->updateForce(forces[i].rigidBody, duration);
	}
}