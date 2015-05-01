#include "Spring.h"

Spring::Spring()
	:ForceGenerator()
{

}

Spring::Spring(Particle* p, double spr, double rest)
	: ForceGenerator()
{
	other = p;
	springConst = spr;
	restConst = rest;
}

void Spring::updateForce(Particle* p, double duration)
{
	cout << "Applying force!\n";
	Vector3 force;
	force.copy(p->getPosition() - other->getPosition());

	double mag = force.getMagnitude();
	mag = mag - restConst;
	mag *= springConst;

	force.normalize();
	force *= -mag;
	p->addForce(force);
}