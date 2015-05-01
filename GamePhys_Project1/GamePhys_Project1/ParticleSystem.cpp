#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	 forceRegistry = ParticleForceRegistry();
	 particles = vector<Particle*>();
	 forceGenerators = vector<ForceGenerator*>();
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
	forceRegistry.addRegistry( ForceRegistration(particle, force) );
}

void ParticleSystem::applyForce(Particle* particle, Particle* particle2, ForceGenerator* fg)
{
	forceRegistry.addRegistry(ForceRegistration(particle, particle2, fg));
}

void ParticleSystem::update()
{
	for (size_t i = 0; i < particles.size(); i++)
	{
		particles[i]->update();
	}


}

void ParticleSystem::draw()
{
	for (size_t i = 0; i < particles.size(); i++)
	{
		particles[i]->draw();
	}

	forceRegistry.update();
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