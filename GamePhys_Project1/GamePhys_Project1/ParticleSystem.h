#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <vector>
#include "Particle.h"
#include "ParticleForceRegistry.h"
#include "ForceGenerator.h"

class ParticleSystem
{
public:
	ParticleSystem();

	vector<Particle*> particles;
	vector<ForceGenerator*> forceGenerators;
	ParticleForceRegistry forceRegistry;

	void addParticle(Particle* newParticle);

	void addForce(ForceGenerator* fg);

	void applyForce(Particle* particle, ForceGenerator* fg);
	void applyForce(Particle* particle, Particle* particle2, ForceGenerator* fg);

	void update();
	void draw();

	void cleanup();
	void reset();
};

#endif