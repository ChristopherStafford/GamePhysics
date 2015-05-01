#ifndef FORCEGENERATOR_H
#define FORCEGENERATOR_H

#include "Particle.h"
#include "Vector3.h"

const float FORCE_WIDTH = 5.0f;

class ForceGenerator
{
public:
	ForceGenerator();
	bool drawLine;
	virtual void updateForce(Particle* particle, double duration){};
	virtual void updateForce(Particle* particle, Particle* particle2, double duration){};
};

class ForceRegistration
{
public:
	ForceRegistration(Particle* p, ForceGenerator* nfg)
	{
		particle = p;
		fg = nfg;
		twoParticles = false;
	}

	ForceRegistration(Particle* p, Particle* p2, ForceGenerator* nfg)
	{
		particle = p;
		exertParticle = p2;
		fg = nfg;
		twoParticles = true;
	}

	bool twoParticles;
	Particle* particle;
	Particle* exertParticle;
	ForceGenerator* fg;
};


#endif;