#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	 forceRegistry = ParticleForceRegistry();
	 particles = vector<Particle*>();
	 forceGenerators = vector<ForceGenerator*>();

	 contactGenerators = vector<ParticleContactGenerator*>();
	 contactResolver = ParticleContactResolver();
	 particleContacts = vector<ParticleContact*>();

	 maxContacts = 10000;
}

void ParticleSystem::addParticle(Particle* newParticle)
{
	particles.push_back(newParticle);
}

void ParticleSystem::addForce(ForceGenerator* fg)
{
	forceGenerators.push_back(fg);
}

void ParticleSystem::applyForce(Particle* particle, ForceGenerator* force)
{
	//Check if sets already contain particle and force.  If not, add them.
	if (find(particles.begin(), particles.end(), particle) == particles.end())
	{
		addParticle(particle);
	}

	if (find(forceGenerators.begin(), forceGenerators.end(), force) == forceGenerators.end())
	{
		addForce(force);
	}
	forceRegistry.addRegistry( ForceRegistration(particle, force) );
}

void ParticleSystem::applyForce(Particle* particle, Particle* particle2, ForceGenerator* fg)
{
	forceRegistry.addRegistry(ForceRegistration(particle, particle2, fg));
}

void ParticleSystem::addContact(ParticleContactGenerator* partCon)
{
	contactGenerators.push_back(partCon);
}

void ParticleSystem::applyContact(Particle* particle1, Particle* particle2, ParticleContactGenerator* contact)
{
	if (find(particles.begin(), particles.end(), particle1) == particles.end())
	{
		addParticle(particle1);
	}

	if (find(particles.begin(), particles.end(), particle2) == particles.end())
	{
		addParticle(particle2);
	}

	addContact(contact);
}

unsigned ParticleSystem::generateContacts()
{
	unsigned limit = maxContacts;

	vector<ParticleContact*>::iterator contactIt = particleContacts.begin();
	for (contactIt; contactIt != particleContacts.end(); ++contactIt)
	{
		delete(*contactIt);
	}
	particleContacts.clear();

	//Draw Contacts
	drawContacts.clear();

	vector<ParticleContactGenerator*>::iterator g;
	for (g = contactGenerators.begin(); g != contactGenerators.end(); g++)
	{
		ParticleContact* nextContact = new ParticleContact();
		nextContact->init();
		unsigned used = (*g)->addContact(nextContact, limit);
		limit -= used;

		if (nextContact->drawLine)
		{
			drawContacts.push_back(nextContact);
		}
		
		if (used > 0)
		{
			nextContact->use = true;
			particleContacts.push_back(nextContact);
		}

		if (limit <= 0)
		{
			break;
		}
	}

	return maxContacts - limit;
}

void ParticleSystem::update()
{
	for (size_t i = 0; i < particles.size(); i++)
	{
		particles[i]->update();
	}
	
	forceRegistry.update();
	unsigned usedContacts = generateContacts();

	if (usedContacts)
	{
		bool calculateIterations = true;
		if (calculateIterations)
		{
			contactResolver.setIterations(usedContacts * 2);
		}
		contactResolver.resolveContacts(particleContacts, usedContacts);
	}
}

void ParticleSystem::draw()
{
	size_t i;
	for (i = 0; i < particles.size(); i++)
	{
		particles[i]->draw();
	}

	for (i = 0; i<drawContacts.size(); i++)
	{
		drawContacts[i]->draw();
	}
	/*
	for (i = 0; i<drawForces.size(); i++)
	{
		drawForces[i]->draw();
	}*/
}

void ParticleSystem::cleanup()
{
	vector<Particle*>::iterator pIt = particles.begin();
	for (pIt; pIt != particles.end(); ++pIt)
	{
		delete(*pIt);
	}
	particles.clear();

	vector<ForceGenerator*>::iterator fgIt = forceGenerators.begin();
	for (fgIt; fgIt != forceGenerators.end(); ++fgIt)
	{
		delete(*fgIt);
	}
	forceGenerators.clear();
}

void ParticleSystem::reset()
{
	for (size_t i = 0; i < particles.size(); i++)
	{
		particles[i]->reset();
	}
}