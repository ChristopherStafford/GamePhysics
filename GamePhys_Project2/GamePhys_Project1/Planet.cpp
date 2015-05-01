#include "Planet.h"

Planet::Planet(string nm, double size, double m, double distance, double speed, Color c)
	:Particle()
{
	
	//cout << "Planet constructor\n";

	name = nm;
	radius = size;
	mass = m;
	startPosition = Vector3(distance, 0, 0);
	startVelocity = Vector3(0, 0, speed);
	position = startPosition;
	velocity = startVelocity;
	color.r = c.r;
	color.g = c.g;
	color.b = c.b;
	color.a = c.a;

	initPosition.copy(position);
	initAcceleration.copy(acceleration);
	initRotation.copy(rotation);
	initVelocity.copy(velocity);

	//color = c;
}