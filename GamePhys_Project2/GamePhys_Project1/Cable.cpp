#include "Cable.h"

unsigned Cable::addContact(ParticleContact* contact, unsigned limit)
{
	double length = currentLength();

	contact->drawLine = true;
	contact->color = lineColor;
	contact->mParticle[0] = particle[0];
	contact->mParticle[1] = particle[1];

	if (length < maxLength)
	{
		return 0;
	}



	Vector3 normal = particle[1]->getPosition() - particle[0]->getPosition();
	normal.normalize();

	contact->mContactNormal = normal;
	contact->mPenetration = length - maxLength;
	contact->mRestitution = restitution;

	return 1;
}