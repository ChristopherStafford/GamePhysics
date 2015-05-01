#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(const Vector3& newGravity)
	:ForceGenerator()
{
	gravity = newGravity;
}

void GravityForceGenerator::updateForce(Particle* particle, double duration)
{
	if (!particle->hasFiniteMass()) return;
		particle->addForce(gravity * particle->getMass());
}

void GravityForceGenerator::updateForce(Particle* particle, Particle* particle2, double duration)
{

}