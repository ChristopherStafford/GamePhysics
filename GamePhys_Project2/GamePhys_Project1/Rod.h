#ifndef ROD_H
#define ROD_H

#include "Connection.h"

class Rod : public Connection
{
public:
	double length;
	virtual unsigned addContact(ParticleContact* contact, unsigned limit);
};

#endif