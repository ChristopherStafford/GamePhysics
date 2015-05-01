#ifndef CONNECTION_H
#define CONNECTION_H

#include "Color.h"
#include "ParticleContactGenerator.h"

class Connection : public ParticleContactGenerator
{
public:
	virtual unsigned addContact(ParticleContact* contact, unsigned limit) = 0;
	Particle* particle[2];
	Color lineColor;

protected:
	double currentLength();
};
#endif