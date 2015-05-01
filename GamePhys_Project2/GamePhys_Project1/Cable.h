#ifndef CABLE_H
#define CABLE_H

#include "Connection.h"

class Cable : public Connection
{
public:
	double maxLength;
	double restitution;

	virtual unsigned addContact(ParticleContact* contact, unsigned limit);
};

#endif