#include <string>
#include "Particle.h"
#include "Color.h"



struct GroundPlane
{
	string name;
	Particle* particle;
	Color color;
	Vector3 startPosition;
};

struct Blob
{
	string name;
	Particle* particle;
	Color color;
	Vector3 startPosition;
};


enum ConnectionType
{
	ROD,
	CABLE,
	SPRING,
	BUNGIE
};

struct Pickup
{
	string name;
	Particle* particle;
	Color color;
	bool connected;
	Vector3 startPosition;
	ConnectionType type;
	double grabDist;
};

