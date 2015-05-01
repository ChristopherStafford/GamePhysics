#include "Game.h"



Game::Game()
{

}

Game::~Game()
{
	cleanup();
}

bool Game::init(int argc, char *argv[])
{
	graphics = new GraphicsSystem();
	if (!graphics->init(argc, argv))
	{
		return false;
	}

	ps = new ParticleSystem();
	debugText = Text();

	buildLevel();
	initParticles();
	return true;
}

void Game::gameLoop()
{

	while (!glfwWindowShouldClose(graphics->getWindow()))
	{
		//get deltaTime
		double newTime = glfwGetTime();
		deltaTime = (newTime - timeSinceLaunch);
		timeSinceLaunch = newTime;

		//cout << "Time Since Launch: " << timeSinceLaunch << "   DeltaTime:" << deltaTime << "\n";


		//reset
		if (resetSim)
		{
			ps->reset();
			graphics->reset();
			resetBlobs();
			resetPlanes();
			resetSim = false;
		}

		handlePlayerMovement();
		handlePickups();
		graphics->startDraw();

		ps->update();
		ps->draw();
		handleDebugText();
		graphics->endDraw();
	}
}

void Game::cleanup()
{
	graphics->cleanup();
	delete graphics;
	ps->cleanup();
	delete ps;
}


void Game::initParticles()
{
	resetBlobs();
	resetPlanes();
	applyGravity();
	applyContacts();
}

void Game::resetBlobs()
{
	vector<Blob*>::iterator blobIter = blobs.begin();
	for (blobIter; blobIter != blobs.end(); ++blobIter)
	{
		(*blobIter)->particle->setPosition((*blobIter)->startPosition);
		(*blobIter)->particle->setVelocity(Vector3(0, 0, 0));
	}

	vector<Pickup*>::iterator pkIter = pickups.begin();
	for (pkIter; pkIter != pickups.end(); ++pkIter)
	{
		(*pkIter)->particle->setPosition((*pkIter)->startPosition);
		(*pkIter)->particle->setVelocity(Vector3(0, 0, 0));
	}
}

void Game::resetPlanes()
{
	vector<GroundPlane*>::iterator blockIter = planes.begin();

	for (blockIter; blockIter != planes.end(); ++blockIter)
	{
		(*blockIter)->particle->setPosition((*blockIter)->startPosition);
		(*blockIter)->particle->setVelocity(Vector3(0, 0, 0));
	}
}

void Game::buildLevel()
{
	//first we add the player
	player = createBlob("Player", Color::white(), 10, 1, Vector3(0, 10, 0));
	blobs.push_back(player);

	//now add the floor
	GroundPlane* floor = createPlane("Floor", Color(0.0f, 0.4f, 0.2f), Vector3(0, 0, 0));
	planes.push_back(floor);


	if (!loadLevel("test.txt"))
	{
		cout << "Unable to load level.\n";
		//this blob is connected with a cable
		Pickup* cablePickup = createPickup("CableBlob", Color::green(), 10, 1, Vector3(5, 10, 10), CABLE, 3);
		pickups.push_back(cablePickup);

		//and this one with a rod
		Pickup* rodPickup = createPickup("RodBlob", Color::red(), 10, 1, Vector3(-5, 10, 10), ROD, 3);
		pickups.push_back(rodPickup);

		//add some shapes
		buildCube("TestCube", Color::blue(), Color::cyan(), 0.5f, 5, 5, Vector3(10, 5, 0));
		buildTetrahedron("TestTetrahedron", Color::blue(), Color::cyan(), 0.5f, 5, 5, Vector3(-10, 5, 0));
	}



}

bool Game::loadLevel(string levelName)
{
	ifstream file;
	string line;

	file.open(levelName);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			if (line == "CUBE")
			{
				string name;
				//Color cVect;
				//Color cEdge;
				double ballSize;
				double mass;
				double edgeLength;
				double x;
				double y;
				double z;
				string temp;
				//name
				getline(file, name);

				//ball size
				getline(file, temp);
				ballSize = stod(temp);

				//mass
				getline(file, temp);
				mass = stod(temp);

				//edge length
				getline(file, temp);
				edgeLength = stod(temp);

				//pos
				getline(file, temp);
				x = stod(temp);
				getline(file, temp);
				y = stod(temp);
				getline(file, temp);
				z = stod(temp);

				buildCube(name, Color::blue(), Color::cyan(), ballSize, mass, edgeLength, Vector3(x, y, z));
			}
			else if (line == "TETRAHEDRON")
			{
				string name;
				//Color cVect;
				//Color cEdge;
				double ballSize;
				double mass;
				double edgeLength;
				double x;
				double y;
				double z;
				string temp;
				//name
				getline(file, name);

				//ball size
				getline(file, temp);
				ballSize = stod(temp);

				//mass
				getline(file, temp);
				mass = stod(temp);

				//edge length
				getline(file, temp);
				edgeLength = stod(temp);

				//pos
				getline(file, temp);
				x = stod(temp);
				getline(file, temp);
				y = stod(temp);
				getline(file, temp);
				z = stod(temp);
				buildTetrahedron(name, Color::blue(), Color::cyan(), ballSize, mass, edgeLength, Vector3(x, y, z));
			}
			else if (line == "TRI_PRISM")
			{
				string name;
				//Color cVect;
				//Color cEdge;
				double ballSize;
				double mass;
				double el;
				double tl;
				double x;
				double y;
				double z;
				string temp;
				//name
				getline(file, name);

				//ball size
				getline(file, temp);
				ballSize = stod(temp);

				//mass
				getline(file, temp);
				mass = stod(temp);

				//edge length (connection)
				getline(file, temp);
				el = stod(temp);
				//edge length (triangle)
				getline(file, temp);
				tl = stod(temp);

				//pos
				getline(file, temp);
				x = stod(temp);
				getline(file, temp);
				y = stod(temp);
				getline(file, temp);
				z = stod(temp);

				buildTriangleLoaf(name, Color::blue(), Color::cyan(), ballSize,
					mass, el, tl, Vector3(x,y,z));
			}
			
			else if (line == "CABLE_PICKUP")
			{
				string name;
				//Color cVect;
				//Color cEdge;
				double ballSize;
				double mass;
				double grabDist;
				double x;
				double y;
				double z;
				string temp;
				//name
				getline(file, name);

				//ball size
				getline(file, temp);
				ballSize = stod(temp);

				//mass
				getline(file, temp);
				mass = stod(temp);

				//grabdist
				getline(file, temp);
				grabDist = stod(temp);

				//pos
				getline(file, temp);
				x = stod(temp);
				getline(file, temp);
				y = stod(temp);
				getline(file, temp);
				z = stod(temp);

				Pickup* cablePickup = createPickup(name, Color::green(), mass, ballSize, Vector3(x, y, z), CABLE, grabDist);
				pickups.push_back(cablePickup);
			}
			else if (line == "ROD_PICKUP")
			{
				string name;
				//Color cVect;
				//Color cEdge;
				double ballSize;
				double mass;
				double grabDist;
				double x;
				double y;
				double z;
				string temp;
				//name
				getline(file, name);

				//ball size
				getline(file, temp);
				ballSize = stod(temp);

				//mass
				getline(file, temp);
				mass = stod(temp);

				//grabdist
				getline(file, temp);
				grabDist = stod(temp);

				//pos
				getline(file, temp);
				x = stod(temp);
				getline(file, temp);
				y = stod(temp);
				getline(file, temp);
				z = stod(temp);

				//and this one with a rod
				Pickup* rodPickup = createPickup(name, Color::red(), mass, ballSize, Vector3(x, y, z), ROD, grabDist);
				pickups.push_back(rodPickup);

			}

			else if (line == "SPRING_PICKUP")
			{
				string name;
				double ballSize;
				double mass;
				double grabDist;
				double x;
				double y;
				double z;
				string temp;

				//name
				getline(file, name);

				//ball size
				getline(file, temp);
				ballSize = stod(temp);

				//mass
				getline(file, temp);
				mass = stod(temp);

				//grabdist
				getline(file, temp);
				grabDist = stod(temp);

				//pos
				getline(file, temp);
				x = stod(temp);
				getline(file, temp);
				y = stod(temp);
				getline(file, temp);
				z = stod(temp);

				//and this one with a rod
				Pickup* springPickup = createPickup(name, Color::yellow(), mass, ballSize, Vector3(x, y, z), SPRING, grabDist);
				pickups.push_back(springPickup);

			}
			else if (line == "BUNGIE_PICKUP")
			{
				string name;
				double ballSize;
				double mass;
				double grabDist;
				double x;
				double y;
				double z;
				string temp;

				//name
				getline(file, name);

				//ball size
				getline(file, temp);
				ballSize = stod(temp);

				//mass
				getline(file, temp);
				mass = stod(temp);

				//grabdist
				getline(file, temp);
				grabDist = stod(temp);

				//pos
				getline(file, temp);
				x = stod(temp);
				getline(file, temp);
				y = stod(temp);
				getline(file, temp);
				z = stod(temp);

				//and this one with a rod
				Pickup* bungiePickup = createPickup(name, Color::magenta(), mass, ballSize, Vector3(x, y, z), BUNGIE, grabDist);
				pickups.push_back(bungiePickup);

			}
			else if (line == "PLAYER")
			{
				double x;
				double y;
				double z;
				string temp;

				getline(file, temp);
				x = stod(temp);
				getline(file, temp);
				y = stod(temp);
				getline(file, temp);
				z = stod(temp);

				player->startPosition = Vector3(x, y, z);
			}
		}
	}
	else
	{
		return false;
	}
	file.close();
	return true;

}

Blob* Game::createBlob(string name, Color color, double mass, double size, Vector3 pos)
{
	Blob* blob = new Blob();
	blob->name = name;
	blob->color.copy(color);
	blob->particle = new Particle(size, mass, blob->color);
	blob->startPosition = pos;

	return blob;
}

GroundPlane* Game::createPlane(string name, Color color, Vector3 pos)
{
	GroundPlane* ground = new GroundPlane();
	ground->name = name;
	ground->color = color;
	ground->particle = new Ground(pos.x,pos.y,pos.z, color);
	ground->startPosition.copy(pos);
	
	return ground;
}

Pickup* Game::createPickup(string name, Color color, double mass, double size, Vector3 pos,
	ConnectionType type, double grabDist)
{
	Pickup* pickup = new Pickup();
	pickup->name = name;
	pickup->color.copy(color);
	pickup->particle = new Particle(size, mass, pickup->color);
	pickup->startPosition = pos;
	pickup->type = type;
	pickup->grabDist = grabDist;
	pickup->connected = false;

	return pickup;
}


void Game::applyGravity()
{
	GravityForceGenerator* gg = new GravityForceGenerator(Vector3( 0.0f ,-9.8f , 0.0f));

	vector<Blob*>::iterator blobIter = blobs.begin();
	for (blobIter; blobIter != blobs.end(); ++blobIter)
	{
		ps->applyForce((*blobIter)->particle, gg);
	}

	vector<Pickup*>::iterator pkIter = pickups.begin();
	for (pkIter; pkIter != pickups.end(); ++pkIter)
	{
		ps->applyForce((*pkIter)->particle, gg);
	}
}

void Game::applyContacts()
{
	vector<GroundPlane*>::iterator planeIter = planes.begin();

	for (planeIter; planeIter != planes.end(); ++planeIter)
	{
		ps->addParticle((*planeIter)->particle);
		GroundContactGenerator* groundGen;

		vector<Blob*>::iterator blobIter = blobs.begin();
		for (blobIter; blobIter != blobs.end(); ++blobIter)
		{
			groundGen = new GroundContactGenerator();
			groundGen->ground = (*planeIter)->particle;
			groundGen->other = (*blobIter)->particle;
			groundGen->radius = (*blobIter)->particle->getRadius();
			ps->addContact(groundGen);
		}


		vector<Pickup*>::iterator pkIter = pickups.begin();
		for (pkIter; pkIter != pickups.end(); ++pkIter)
		{
			groundGen = new GroundContactGenerator();
			groundGen->ground = (*planeIter)->particle;
			groundGen->other = (*pkIter)->particle;
			groundGen->radius = (*pkIter)->particle->getRadius();
			ps->addContact(groundGen);
		}
	}
}


void Game::connectWithCable(Particle* p1, Particle* p2, Color color, double restitution, double length)
{
	Cable* c = new Cable();
	c->restitution = restitution;
	c->maxLength = length;
	c->lineColor.copy(color);
	c->particle[0] = p1;
	c->particle[1] = p2;
	ps->addContact(c);
}

void Game::connectWithRod(Particle* p1, Particle* p2, Color color, double length)
{
	Rod* rod = new Rod();
	rod->length = length;
	rod->lineColor.copy(color);
	rod->particle[0] = p1;
	rod->particle[1] = p2;
	ps->addContact(rod);
}

void Game::connectWithSpring(Particle* p1, Particle* p2, Color color, double spr, double rest)
{
	Spring* s = new Spring(p2, spr, rest);
	ps->applyForce(p1, s);
}

void Game::connectWithBungie(Particle* p1, Particle* p2, Color color, double spr, double rest)
{
	Bungie* b = new Bungie(p2, spr, rest);
	ps->applyForce(p1, b);
}



void Game::handlePlayerMovement()
{
	Vector3 totalForce = Vector3(0, 0, 0);
	float force = 100;

	if (leftDown)
		totalForce.x -= force;
	if (rightDown)
		totalForce.x += force;
	if (forwardDown)
		totalForce.z -= force;
	if (backwardDown)
		totalForce.z += force;

	player->particle->addForce(totalForce);
}

void Game::handlePickups()
{
	vector<Pickup*>::iterator pkIter = pickups.begin();
	for (pkIter; pkIter != pickups.end(); ++pkIter)
	{
		if ((*pkIter)->connected)
		{
			//this unit is connected already. no need to check.
			//cout << "Already connected.\n";
			continue;
		}

		Vector3 myPos = (*pkIter)->particle->getPosition();
		Vector3 playerPos = player->particle->getPosition();

		double distanceSquared = myPos.distanceSquared(playerPos);
		if (distanceSquared <= (*pkIter)->grabDist * (*pkIter)->grabDist)
		{
			cout << "Pickup collision!\n";
			switch ((*pkIter)->type)
			{
			case CABLE:
				connectWithCable(player->particle, (*pkIter)->particle, (*pkIter)->color, 0.5f, 5.0f);
				break;
			case ROD:
				connectWithRod(player->particle, (*pkIter)->particle, (*pkIter)->color, 5.0f);
				break;
			case SPRING:
				connectWithSpring((*pkIter)->particle, player->particle, (*pkIter)->color, 1.0f, 3);
			case BUNGIE:
				connectWithBungie((*pkIter)->particle, player->particle, (*pkIter)->color, 1.0f, 3);
			}
			
			(*pkIter)->connected = true;
		}
	}
}

void Game::buildTetrahedron(string name, Color cEdge, Color cVert, double size, double mass, double length, Vector3 pos)
{
	double posOffset = length * 0.5f;
	
	Blob* forward = createBlob(name + "Vert_Forward", cVert, mass, size, Vector3(pos.x, pos.y, pos.z - posOffset));
	Blob* left = createBlob(name + "Vert_Left", cVert, mass, size, Vector3(pos.x - posOffset, pos.y, pos.z + posOffset));
	Blob* right = createBlob(name + "Vert_Right", cVert, mass, size, Vector3(pos.x + posOffset, pos.y, pos.z + posOffset));
	Blob* top = createBlob(name + "Vert_Top", cVert, mass, size, Vector3(pos.x, pos.y + length, pos.z));

	connectWithRod(forward->particle, right->particle, cEdge, length);
	connectWithRod(right->particle, left->particle, cEdge, length);
	connectWithRod(left->particle, forward->particle, cEdge, length);



	connectWithRod(top->particle, right->particle, cEdge, length);
	connectWithRod(top->particle, left->particle, cEdge, length);
	connectWithRod(top->particle, forward->particle, cEdge, length);

	blobs.push_back(forward);
	blobs.push_back(left);
	blobs.push_back(right);
	blobs.push_back(top);
}




void Game::buildCube(string name, Color cVert, Color cEdge, double size, double mass, double length, Vector3 pos)
{
	double posOffset = length * 0.5f;
	double beamLength = sqrt(pow(length, 2) * 2);
	double crossBeamLength = sqrt( pow(beamLength, 2) + pow(length, 2) );
	//make the vertexes
	Blob* cubeBUL = createBlob(name + "Vert_BUL", cEdge, mass, size, Vector3(pos.x - posOffset, pos.y - posOffset, pos.z - posOffset));
	Blob* cubeBUR = createBlob(name + "Vert_BUR", cEdge, mass, size, Vector3(pos.x + posOffset, pos.y - posOffset, pos.z - posOffset));
	Blob* cubeBLL = createBlob(name + "Vert_BLL", cEdge, mass, size, Vector3(pos.x - posOffset, pos.y - posOffset, pos.z + posOffset));
	Blob* cubeBLR = createBlob(name + "Vert_BLR", cEdge, mass, size, Vector3(pos.x + posOffset, pos.y - posOffset, pos.z + posOffset));
	Blob* cubeTUL = createBlob(name + "Vert_TUL", cEdge, mass, size, Vector3(pos.x - posOffset, pos.y + posOffset, pos.z - posOffset));
	Blob* cubeTUR = createBlob(name + "Vert_TUR", cEdge, mass, size, Vector3(pos.x + posOffset, pos.y + posOffset, pos.z - posOffset));
	Blob* cubeTLL = createBlob(name + "Vert_TLL", cEdge, mass, size, Vector3(pos.x - posOffset, pos.y + posOffset, pos.z + posOffset));
	Blob* cubeTLR = createBlob(name + "Vert_TLR", cEdge, mass, size, Vector3(pos.x + posOffset, pos.y + posOffset, pos.z + posOffset));

	//connect the dots

	//top plane
	connectWithRod(cubeTUL->particle, cubeTUR->particle, cVert, length);
	connectWithRod(cubeTUR->particle, cubeTLR->particle, cVert, length);
	connectWithRod(cubeTLR->particle, cubeTLL->particle, cVert, length);
	connectWithRod(cubeTLL->particle, cubeTUL->particle, cVert, length);

	//bottom plane
	connectWithRod(cubeBUL->particle, cubeBUR->particle, cVert, length);
	connectWithRod(cubeBUR->particle, cubeBLR->particle, cVert, length);
	connectWithRod(cubeBLR->particle, cubeBLL->particle, cVert, length);
	connectWithRod(cubeBLL->particle, cubeBUL->particle, cVert, length);
		
	//remaining edges
	connectWithRod(cubeTUL->particle, cubeBUL->particle, cVert, length);
	connectWithRod(cubeTUR->particle, cubeBUR->particle, cVert, length);
	connectWithRod(cubeTLR->particle, cubeBLR->particle, cVert, length);
	connectWithRod(cubeTLL->particle, cubeBLL->particle, cVert, length);


	//Top X
	connectWithRod(cubeTUL->particle, cubeTLR->particle, cVert, beamLength);
	connectWithRod(cubeTUR->particle, cubeTLL->particle, cVert, beamLength);

	//Bottom X
	connectWithRod(cubeBUL->particle, cubeBLR->particle, cVert, beamLength);
	connectWithRod(cubeBUR->particle, cubeBLL->particle, cVert, beamLength);

	//Front X
	connectWithRod(cubeTLL->particle, cubeBLR->particle, cVert, beamLength);
	connectWithRod(cubeTLR->particle, cubeBLL->particle, cVert, beamLength);
	
	//Back X
	connectWithRod(cubeTUL->particle, cubeBUR->particle, cVert, beamLength);
	connectWithRod(cubeTUR->particle, cubeBUL->particle, cVert, beamLength);
	
	//Left X
	connectWithRod(cubeTUL->particle, cubeBLL->particle, cVert, beamLength);
	connectWithRod(cubeTLL->particle, cubeBUL->particle, cVert, beamLength);
	
	//Right X
	connectWithRod(cubeTUR->particle, cubeBLR->particle, cVert, beamLength);
	connectWithRod(cubeTLR->particle, cubeBUL->particle, cVert, beamLength);

	
	//center X
	connectWithRod(cubeTUR->particle, cubeBLL->particle, Color::red(), crossBeamLength);
	connectWithRod(cubeBUR->particle, cubeTLL->particle, Color::red(), crossBeamLength);
	connectWithRod(cubeTLR->particle, cubeBUL->particle, Color::red(), crossBeamLength);
	connectWithRod(cubeTUL->particle, cubeBLR->particle, Color::red(), crossBeamLength);
	

	//add blobs to blobs
	blobs.push_back(cubeBUL);
	blobs.push_back(cubeBUR);
	blobs.push_back(cubeBLR);
	blobs.push_back(cubeBLL);

	blobs.push_back(cubeTUL);
	blobs.push_back(cubeTUR);
	blobs.push_back(cubeTLR);
	blobs.push_back(cubeTLL);
}


void Game::buildTriangleLoaf(string name, Color cEdge, Color cVert, double size, double mass, double edgeLength, double triLength, Vector3 pos)
{
	double posOffset = triLength / 2;
	double height = sqrt( pow(triLength, 2) - pow((triLength / 2), 2) );

	Blob* leftF = createBlob(name + "Vert_LeftF", cVert, mass, size, Vector3(pos.x - posOffset, pos.y, pos.z));
	Blob* rightF = createBlob(name + "Vert_RightF", cVert, mass, size, Vector3(pos.x + posOffset, pos.y, pos.z));
	Blob* topF = createBlob(name + "Vert_TopF", cVert, mass, size, Vector3(pos.x, pos.y + height, pos.z));

	Blob* leftB = createBlob(name + "Vert_LeftF", cVert, mass, size, Vector3(pos.x - posOffset, pos.y, pos.z + edgeLength));
	Blob* rightB = createBlob(name + "Vert_RightF", cVert, mass, size, Vector3(pos.x + posOffset, pos.y, pos.z + edgeLength));
	Blob* topB = createBlob(name + "Vert_TopF", cVert, mass, size, Vector3(pos.x, pos.y + height, pos.z + edgeLength));

	//front
	connectWithRod(leftF->particle, rightF->particle, cEdge, triLength);
	connectWithRod(rightF->particle, topF->particle, cEdge, triLength);
	connectWithRod(topF->particle, leftF->particle, cEdge, triLength);

	//back
	connectWithRod(leftB->particle, rightB->particle, cEdge, triLength);
	connectWithRod(rightB->particle, topB->particle, cEdge, triLength);
	connectWithRod(topB->particle, leftB->particle, cEdge, triLength);

	//edge connections
	connectWithRod(leftF->particle, leftB->particle, cEdge, edgeLength);
	connectWithRod(rightF->particle, rightB->particle, cEdge, edgeLength);
	connectWithRod(topF->particle, topB->particle, cEdge, edgeLength);

	blobs.push_back(leftF);
	blobs.push_back(rightF);
	blobs.push_back(topF);

	blobs.push_back(leftB);
	blobs.push_back(rightB);
	blobs.push_back(topB);
}

void Game::handleDebugText()
{
	//reset
	debugText.clearText();
	debugText.myText.push_back( debugLine(player->name, player->particle) );

	vector<Pickup*>::iterator pkIter = pickups.begin();
	for (pkIter; pkIter != pickups.end(); ++pkIter)
	{
		if ((*pkIter)->connected)
		{
			debugText.myText.push_back(debugLine((*pkIter)->name, (*pkIter)->particle));
		}
	}
	
	debugText.draw();
}

string Game::debugLine(string name, Particle* p)
{
	stringstream ss;

	//player debugInfo
	ss << name
		<< " | Pos:"; ss << p->getPosition().toString()
		<< " | Vel:" << p->getVelocity().toString()
		;
	return ss.str();
}