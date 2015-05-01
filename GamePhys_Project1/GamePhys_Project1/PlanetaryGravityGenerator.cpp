#include "PlanetaryGravityGenerator.h"

PlanetaryGravityGenerator::PlanetaryGravityGenerator()
{
}

void PlanetaryGravityGenerator::updateForce(Particle* particle, Particle* particle2, double duration)
{
	Vector3 direction = particle2->getPosition() - particle->getPosition();
	direction.normalize();

	double masses = (double)particle->getMass() * (double)particle2->getMass();
	double distSquare = particle->getPosition().distanceSquared(particle2->getPosition());
	double gravScale = GRAVITY * masses / distSquare;

	particle->addForce(direction * gravScale);
}