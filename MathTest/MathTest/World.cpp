#include "World.h"

World::World()
{
	balls = vector<Ball*>();
	rbForceRegistry = RigidBodyForceRegistry();
}

void World::startFrame()
{
	vector<Ball*>::iterator b = balls.begin();
	for (b;	b != balls.end(); ++b)
	{
		(*b)->body->clearAccumulators();
		(*b)->body->calculateDerivedData();
	}
}

void World::runPhysics(double duration)
{
	rbForceRegistry.update(duration);

	vector<Ball*>::iterator b = balls.begin();
	for (b; b != balls.end(); ++b)
	{
		(*b)->col->calculateInternals();
		(*b)->body->integrate(duration);
	}

	generateContacts(duration);
}

void World::draw()
{
	vector<Ball*>::iterator ballIt = balls.begin();

	for (ballIt; ballIt != balls.end(); ++ballIt)
	{
		(*ballIt)->col->draw();
	}
}

void World::cleanup()
{

}

void World::applyForces()
{
	Gravity* gg = new Gravity(Vector3(0.0f, -9.8f, 0.0f));

	vector<Ball*>::iterator b = balls.begin();
	for (b; b != balls.end(); ++b)
	{
		if ((*b)->name != "Static")
			rbForceRegistry.addRegistry(ForceRegistration((*b)->body, gg));
	}

	
}

void World::applySpring(RigidBody* body, RigidBody* other)
{
	Spring* spring = new Spring(Vector3(0, 0, 0), other, Vector3(0,0,0), 0.5f, 4);
	rbForceRegistry.addRegistry(ForceRegistration(body, spring));
}

Ball* World::createBall(string name, Color color, double radius, double mass, Vector3 pos, Vector3 vel)
{
	Ball* ball = new Ball();
	ball->name = name;
	ball->col = new CollisionSphere(radius, color);
	ball->col->body = new RigidBody();
	ball->body = ball->col->body;
	ball->body->setMass(mass);
	ball->startPos.copy(pos);
	ball->startVel.copy(vel);

	return ball;
}

void World::initBalls()
{
	vector<Ball*>::iterator ballIt = balls.begin();

	for (ballIt; ballIt != balls.end(); ++ballIt)
	{
			(*ballIt)->col->setPosition((*ballIt)->startPos);
			(*ballIt)->col->setVelocity((*ballIt)->startVel);
	}
}

void World::generateContacts(double duration)
{
	CollisionData data = CollisionData();
	data.friction = 0.5f;
	data.restitution = 0.2f;
	data.reset(99);

	vector<Ball*>::iterator ballIt = balls.begin();
	for (ballIt; ballIt != balls.end(); ++ballIt)
	{
		vector<Ball*>::iterator ballIt2 = balls.begin();
		for (ballIt2; ballIt2 != balls.end(); ++ballIt2)
		{
			if (ballIt != ballIt2)
			{
				(*ballIt)->col->DetectCollision((*ballIt2)->col, &data);

			}
		}
	}

	if (data.contactCount > 0)
	{
		//cout << data.contactCount << endl;
		resolver.resolveContacts(data.contactArray, data.contactCount, duration);
	}

}

void World::createLevel()
{
	balls.push_back(createBall("Steel", Color(0.7f, 0.7f, 0.7f), 0.5f, 0.8f, Vector3(0, 10, 0)));
	balls.push_back(createBall("Ice", Color::cyan(), 0.5f, 0.4f, Vector3(3, 10, 0)));
	balls.push_back(createBall("Wood", Color::green(), 0.5f, 0.4f, Vector3(-3, 10, 0)));
	balls.push_back(createBall("Foam", Color::cyan(), 1, 0.1f, Vector3(0, 10, 4)));
	balls.push_back(createBall("Alluminum", Color(0.2f, 0.2f, 0.2f), 0.2f, 0.7f, Vector3(0, 10, -3)));

	balls.push_back(createBall("Static", Color::red(), 6, 400000, Vector3(0, -5, 0) ));
	initBalls();
}