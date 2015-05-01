#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "RigidBody.h"
#include "RigidBodyForceRegistry.h"
#include "ContactResolver.h"
#include "Contact.h"
#include "ContactResolver.h"
#include "CollisionPrimitive.h"
#include "CollisionDetection.h"

using namespace std;

struct Ball
{
	string name;
	CollisionPrimitive* col;
	RigidBody* body;
	Vector3 startPos;
	Vector3 startVel;
};

struct BodyRegistration
{
	RigidBody *body;
	BodyRegistration * next;
};

struct ContactGenRegistration
{
	ContactGenerator *gen;
	ContactGenRegistration *next;
};

class World
{
protected:
	bool calculateIterations;

	//rigid body
	//vector<RigidBody*> bodies;
	vector<Ball*> balls;
	//forces
	RigidBodyForceRegistry rbForceRegistry;
	

	//collisions
	ContactResolver resolver;
	Contact* contacts;
	ContactGenRegistration firstContactGen;

	unsigned maxContacts;


public:
	World();

	Ball* createBall(string name, Color color, double radius, double mass, Vector3 pos = Vector3(), Vector3 vel = Vector3());

	void startFrame();
	void runPhysics(double duration);
	void cleanup();
	void createLevel();
	void initBalls();
	void applyForces();
	void applySpring(RigidBody* body, RigidBody* other);
	void generateContacts(double duration);

	void draw();
};
#endif