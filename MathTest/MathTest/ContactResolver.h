#ifndef CONTACTRESOLVER_H
#define CONTACTRESOLVER_H

#include "Contact.h"

class ContactResolver
{
public:
	ContactResolver();
	ContactResolver(unsigned iterations, double velocityEpsilon = (double)0.01, double positionEpsilon = (double)0.01);
	ContactResolver(unsigned velocityIterations, unsigned positionIterations, double velocityEpsilon = (double)0.01, double positionEpsilon = (double)0.01);
	bool isValid();
	void setIterations(unsigned velocityIterations, unsigned positionIterations);
	void setIterations(unsigned iterations);
	void setEpsilon(double velocityEpsilon, double positionEpsilon);
	void resolveContacts(Contact *contactArray, unsigned numContacts, double duration);

	unsigned velocityIterationsUsed;
	unsigned positionIterationsUsed;

private:
	bool validSettings;

protected:
	void prepareContacts(Contact *contactArray, unsigned numContacts, double duration);
	void adjustVelocities(Contact *contactArray, unsigned numContacts, double duration);
	void adjustPositions(Contact *contacts, unsigned numContacts, double duration);

	unsigned velocityIterations;
	unsigned positionIterations;
	double velocityEpsilon;
	double positionEpsilon;
};
#endif