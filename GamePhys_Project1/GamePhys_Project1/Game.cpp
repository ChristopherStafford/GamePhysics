#include "Game.h"



Game::Game()
{
	timeScale = powf(10, 6);
}

bool Game::init(int argc, char *argv[])
{
	graphics = new GraphicsSystem();
	if (!graphics->init(argc, argv))
	{
		return false;
	}

	ps = new ParticleSystem();

	initSolarSystem();

	return true;
}

void Game::gameLoop()
{

	while (!glfwWindowShouldClose(graphics->getWindow()))
	{
		//get deltaTime
		double newTime = glfwGetTime();
		deltaTime = (newTime - timeSinceLaunch) * timeScale;
		timeSinceLaunch = newTime;

		cout << "Time Since Launch: " << timeSinceLaunch << "   DeltaTime:" << deltaTime << "\n";

		if (resetSim)
		{
			ps->reset();
			graphics->reset();
			resetSim = false;
		}

		for (int i = 0; i < ps->particles.size(); i++)
		{
			if (i > 9)
			{
				i = ps->particles.size();
			}
			else if (i == 0)
			{
				if (numPressed[i])
				graphics->cam->reset();
			}
			else if (numPressed[i])
			{
				graphics->cam->setTarget(ps->particles[i]);
			}
		}

		graphics->startDraw();

		ps->update();
		ps->draw();

		

		graphics->endDraw();
	}
}

Game::~Game()
{
	cleanup();
}

void Game::cleanup()
{
	graphics->cleanup();
	delete graphics;
	ps->cleanup();
	delete ps;
}


void Game::initSolarSystem()
{
	ps->addParticle(new Planet("Sun", 6, 1.989 * pow(10, 30), 0, 0, Color::yellow()));
	ps->addParticle(new Planet("Mercury", 1, 328.5 * pow(10, 21), 5.79 * powf(10, 10), -47400, Color::white() ));
	ps->addParticle(new Planet("Venus", 1.2f, 4.867 * pow(10, 24), 1.082 * powf(10, 11), -32400, Color::yellow() ));
	ps->addParticle(new Planet("Earth", 1.3f, 5.972 * pow(10, 24), 1.495 * powf(10, 11), -30000, Color::blue() ));
	ps->addParticle(new Planet("Mars", 1.2f, 639 * pow(10, 21), 2.279 * powf(10, 11), -23000, Color::red() ));
	ps->addParticle(new Planet("Jupiter", 3, 1.898 * pow(10, 27), 7.785 * powf(10, 11), -12000, Color(1, 0.4f, 0) ));
	ps->addParticle(new Planet("Saturn", 2.75, 568.3 * pow(10, 24), 1.433 * powf(10, 12), -10000, Color(0.75, 0.75f, 0) ));
	ps->addParticle(new Planet("Uranus", 1.75, 86.81 * pow(10, 24), 2.877 * powf(10, 12), -6500, Color(0, 0.75f, 1)));
	ps->addParticle(new Planet("Neptune", 1.75, 102.4 * pow(10, 24), 4.503 * powf(10, 12), -5000, Color::blue() ));

	applyGravity();
}

void Game::applyGravity()
{
	PlanetaryGravityGenerator* pgg = new PlanetaryGravityGenerator();

	bool first = true;
	vector<Particle*>::iterator pIt = ps->particles.begin();
	for (pIt; pIt != ps->particles.end(); ++pIt)
	{
		if (!first)
		{
			ps->applyForce(*pIt, ps->particles[0], pgg);	
		}
		else
			first = false;
	}

	//vector<Moon*>::iterator mIt = mMoons.begin();
	/*for (moonIt; moonIt != mMoons.end(); ++moonIt)
	{
		ps->applyForce((*mIt), (*mIt)->planet, pgg);
		ps->applyForce((*mIt), mPlanets[0], pgg);
	}*/
}