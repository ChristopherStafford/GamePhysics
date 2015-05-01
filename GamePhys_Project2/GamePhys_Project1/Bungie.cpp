#include "Bungie.h"

Bungie::Bungie()
	:ForceGenerator()
{

}

Bungie::Bungie(Particle* p, double bn, double rest)
	: ForceGenerator()
{
	other = p;
	bungieConst = bn;
	restConst = rest;
}

void Bungie::updateForce(Particle* p, double duration)
{
	Vector3 force;
	force.copy(p->getPosition() - other->getPosition());

	double mag = force.getMagnitude();
	if (mag <= restConst)
		return;

	mag = bungieConst * (restConst - mag);
	
	force.normalize();
	force *= mag;
	p->addForce(force);
}