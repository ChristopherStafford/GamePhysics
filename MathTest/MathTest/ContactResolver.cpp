#include "ContactResolver.h"

ContactResolver::ContactResolver()
{
	setIterations(99, 99);
	setEpsilon(.01f, .01f);
}

ContactResolver::ContactResolver(unsigned iterations, double velocityEpsilon, double positionEpsilon)
{
	setIterations(iterations, iterations);
	setEpsilon(velocityEpsilon, positionEpsilon);
}

ContactResolver::ContactResolver(unsigned velocityIterations, unsigned positionIterations, double velocityEpsilon, double positionEpsilon)
{
	setIterations(velocityIterations);
	setEpsilon(velocityEpsilon, positionEpsilon);
}

bool ContactResolver::isValid()
{
	return (velocityIterations > 0) && (positionIterations > 0) &&
		(positionEpsilon >= 0.0f) && (positionEpsilon >= 0.0f);
}

void ContactResolver::setIterations(unsigned velocityIterations, unsigned positionIterations)
{
	this->velocityIterations = velocityIterations;
	this->positionIterations = positionIterations;
}

void ContactResolver::setIterations(unsigned iterations)
{
	setIterations(iterations, iterations);
}

void ContactResolver::setEpsilon(double velocityEpsilon, double positionEpsilon)
{
	this->velocityEpsilon = velocityEpsilon;
	this->positionEpsilon = positionEpsilon;
}

void ContactResolver::resolveContacts(Contact *contactArray, unsigned numContacts, double duration)
{
	if ((numContacts == 0) || !isValid())
	{
		return;
	}

	prepareContacts(contactArray, numContacts, duration);
	adjustPositions(contactArray, numContacts, duration);
	adjustVelocities(contactArray, numContacts, duration);
}

void ContactResolver::prepareContacts(Contact *contactArray, unsigned numContacts, double duration)
{
	Contact* lastContact = contactArray + numContacts;
	for (Contact* contact = contactArray; contact < lastContact; contact++)
	{
		contact->calculateInternals(duration);
	}
}

void ContactResolver::adjustVelocities(Contact *contactArray, unsigned numContacts, double duration)
{
	Vector3 velocityChange[2], rotationChange[2];
	Vector3 deltaVel;

	velocityIterationsUsed = 0;
	while (velocityIterationsUsed < velocityIterations)
	{
		double max = velocityEpsilon;
		unsigned index = numContacts;
		for (unsigned i = 0; i < numContacts; i++)
		{
			if (contactArray[i].desiredDeltaVelocity > max)
			{
				max = contactArray[i].desiredDeltaVelocity;
				index = i;
			}
		}
		if (index == numContacts)
		{
			break;
		}

		contactArray[index].matchAwakeState();
		contactArray[index].applyVelocityChange(velocityChange, rotationChange);

		for (unsigned i = 0; i < numContacts; i++)
		{
			for (unsigned b = 0; b < 2; b++) if (contactArray[i].bodies[b])
			{
				for (unsigned d = 0; d < 2; d++)
				{
					if (contactArray[i].bodies[b] == contactArray[index].bodies[d])
					{
						deltaVel = velocityChange[d] + Vector3::crossProduct(rotationChange[d], contactArray[i].relativeContactPosition[b]);

						contactArray[i].contactVelocity += contactArray[i].contactToWorld.transformTranspose(deltaVel) * (b ? -1 : 1);
						contactArray[i].calculateDesiredDeltaVelocity(duration);
					}
				}
			}
		}
		velocityIterationsUsed++;
	}
}

void ContactResolver::adjustPositions(Contact *contacts, unsigned numContacts, double duration)
{
	unsigned i, index;
	Vector3 linearChange[2], angularChange[2];
	double max;
	Vector3 deltaPosition;

	positionIterationsUsed = 0;
	while (positionIterationsUsed < positionIterations)
	{
		max = positionEpsilon;
		index = numContacts;
		for (i = 0; i<numContacts; i++)
		{
			if (contacts[i].penetration > max)
			{
				max = contacts[i].penetration;
				index = i;
			}
		}
		if (index == numContacts)
		{
			break;
		}

		contacts[index].matchAwakeState();
		contacts[index].applyPositionChange(linearChange, angularChange, max);

		for (i = 0; i < numContacts; i++)
		{
			for (unsigned b = 0; b < 2; b++) if (contacts[i].bodies[b])
			{
				for (unsigned d = 0; d < 2; d++)
				{
					if (contacts[i].bodies[b] == contacts[index].bodies[d])
					{
						deltaPosition = linearChange[d] + Vector3::crossProduct(angularChange[d], contacts[i].relativeContactPosition[b]);
						contacts[i].penetration += deltaPosition.dotProduct(contacts[i].contactNormal) * (b ? 1 : -1);
					}
				}
			}
		}
		positionIterationsUsed++;
	}
}