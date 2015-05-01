#ifndef MOON_H
#define MOON_H

#include "Particle.h"
#include "Planet.h"

class Moon : public Planet
{
protected:
	Planet* myPlanet;

};

#endif