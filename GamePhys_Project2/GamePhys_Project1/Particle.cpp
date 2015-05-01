#include "Particle.h"

Particle::Particle()
{
	init();

	initPosition.copy(position);
	initAcceleration.copy(acceleration);
	initRotation.copy(rotation);
	initVelocity.copy(velocity);
}

Particle::Particle(double x, double y, double z)
{
	init();
	position = Vector3(x,y,z);

	initPosition = position;
	initAcceleration = acceleration;
	initRotation = rotation;
	initVelocity = velocity;
}

Particle::Particle(double r, double m, Color c)
{
	init();
	color.r = c.r;
	color.g = c.g;
	color.b = c.b;
	color.a = c.a;
	radius = r;
	mass = m;

	initPosition = position;
	initAcceleration = acceleration;
	initRotation = rotation;
	initVelocity = velocity;
}

void Particle::init()
{
	//cout << "Particle constructor\n";
	stacks = 100;
	slices = 100;
	radius = 0.2f;
	mass = 10.0f;

	dampening = 0.2f;

	color = Color::white();

	position = Vector3();
	velocity = Vector3();
	rotation = Vector3();
	acceleration = Vector3();

	initPosition = Vector3();
	initVelocity = Vector3();
	initRotation = Vector3();
	initAcceleration = Vector3();
}

void Particle::update()
{
	integrate();
}

void Particle::draw()
{

	GLUquadricObj *s;
	s = gluNewQuadric();

	glLoadIdentity();
	glPushMatrix();

	//translate
	//cout << "Scaled pos: " << position.z / positionScale << endl;
	glTranslatef( (float)(position.x),
		(float)(position.y),
		(float)(position.z));

	//rotate
	glRotatef((float)rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef((float)rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef((float)rotation.z, 0.0f, 0.0f, 1.0f);

	glColor4f(color.r, color.g, color.b, color.a);
	gluSphere(s, radius, slices, stacks);

	glPopMatrix();
	gluDeleteQuadric(s);
}

void Particle::addForce(Vector3 forceVector)
{
	forceAcumulation += forceVector;
}

void Particle::integrate()
{
	if (inverseMass() <= 0)
		return;

	assert(deltaTime > 0.0f);

	position.addScaledVector(velocity, deltaTime);

	Vector3 resultingAcc = acceleration;
	resultingAcc.addScaledVector(forceAcumulation, inverseMass());
	velocity.addScaledVector(resultingAcc, deltaTime);

	velocity *= powf((float)(dampening), (float)(deltaTime));
	clearAccumulator();
}

void Particle::clearAccumulator()
{
	forceAcumulation = Vector3();
}

double Particle::inverseMass()
{
	if (mass <= 0)
		return 0;
	return (1.0f / mass);
}

void Particle::reset()
{
	position.copy(initPosition);
	acceleration.copy(initAcceleration);
	rotation.copy(initRotation);
	velocity.copy(initVelocity);
}
