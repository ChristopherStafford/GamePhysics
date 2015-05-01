#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <vector>
#include "Particle.h"
#include "ParticleForceRegistry.h"
#include "ForceGenerator.h"
#include "ParticleContactGenerator.h"
#include "ParticleContactResolver.h"

class ParticleSystem
{
private:
	unsigned maxContacts;

public:
	ParticleSystem();

	vector<Particle*> particles;
	



	vector<ForceGenerator*> forceGenerators;

	vector<ParticleContactGenerator*> contactGenerators;
	ParticleContactResolver contactResolver;
	vector<ParticleContact*> particleContacts;
	
	vector<ParticleContact*> drawContacts;
	vector<ForceGenerator*> drawForces;

	ParticleForceRegistry forceRegistry;

	void addParticle(Particle* newParticle);

	void addForce(ForceGenerator* fg);

	void applyForce(Particle* particle, ForceGenerator* fg);
	void applyForce(Particle* particle, Particle* particle2, ForceGenerator* fg);

	unsigned generateContacts();

	void addContact(ParticleContactGenerator* partCon);
	void applyContact(Particle* particle1, Particle* particle2, ParticleContactGenerator* contact);

	void update();
	void draw();

	void cleanup();
	void reset();
};

#endif