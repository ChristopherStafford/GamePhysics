#include "ForceGenerator.h"
#include "Particle.h"
#include <math.h>

class Spring : public ForceGenerator
{
private:
	Particle* other;

	double springConst;
	double restConst;

public:
	Spring();
	Spring(Particle* other, double spr, double rest);

	void updateForce(Particle* p, double duration);
};