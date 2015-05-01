#include "Rod.h"

unsigned Rod::addContact(ParticleContact* contact, unsigned limit)
{
	double currentLen = currentLength();

	contact->drawLine = true;
	contact->color.copy(lineColor);
	contact->mParticle[0] = particle[0];
	contact->mParticle[1] = particle[1];

	if (currentLen == length)
	{
		return 0;
	}

	Vector3 normal = particle[1]->getPosition() - particle[0]->getPosition();
	normal.normalize();

	if (currentLen > length)
	{
		contact->mContactNormal = normal;
		contact->mPenetration = currentLen - length;
	}
	else
	{
		contact->mContactNormal = normal * -1;
		contact->mPenetration = length - currentLen;
	}

	//Rods have no bounciness
	contact->mRestitution = 0.0f;

	return 1;
}