#include "ForceGenerator.h"
#include "Particle.h"
#include <math.h>

class Bungie : public ForceGenerator
{
private:
	Particle* other;

	double bungieConst;
	double restConst;

public:
	Bungie();
	Bungie(Particle* other, double spr, double rest);

	void updateForce(Particle* p, double duration);
};