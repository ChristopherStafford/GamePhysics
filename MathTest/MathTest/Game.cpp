#include "Game.h"

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		else
		{
			switch (key)
			{
				//movement
			case 'W':
				forwardDown = true;
				break;
			case 'S':
				backwardDown = true;
				break;
			case 'A':
				leftDown = true;
				break;
			case 'D':
				rightDown = true;
				break;

				//nums
			case '0':
				numPressed[0] = true;
				break;
			case '1':
				numPressed[1] = true;
				break;
			case '2':
				numPressed[2] = true;
				break;
			case '3':
				numPressed[3] = true;
				break;
			case '4':
				numPressed[4] = true;
				break;
			case '5':
				numPressed[5] = true;
				break;
			case '6':
				numPressed[6] = true;
				break;
			case '7':
				numPressed[7] = true;
				break;
			case '8':
				numPressed[8] = true;
				break;
			case '9':
				numPressed[9] = true;
				break;

			case 'T':
				//showDebug = !showDebug;
				break;
			case 'R':
				resetSim = true;
				break;

			case 'L':
				lockMouse = !lockMouse;
				break;

				
			default:
				// Do nothing...
				break;
			}
		}
	}

	if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case 'W':
			forwardDown = false;
			break;
		case 'S':
			backwardDown = false;
			break;
		case 'A':
			leftDown = false;
			break;
		case 'D':
			rightDown = false;
			break;


			//nums
		case '0':
			numPressed[0] = false;
			break;
		case '1':
			numPressed[1] = false;
			break;
		case '2':
			numPressed[2] = false;
			break;
		case '3':
			numPressed[3] = false;
			break;
		case '4':
			numPressed[4] = false;
			break;
		case '5':
			numPressed[5] = false;
			break;
		case '6':
			numPressed[6] = false;
			break;
		case '7':
			numPressed[7] = false;
			break;
		case '8':
			numPressed[8] = false;
			break;
		case '9':
			numPressed[9] = false;
			break;

		default:
			// Do nothing...
			break;
		}

	}

}



Game::Game()
{
	winName = "Chris Stafford - Physics Simulator";
	winSize = Vector2(800, 600);
	mouseSensitivity = 5.0f;
}

bool Game::init(int argc, char *argv[])
{
	if (!initGraphics(argc, argv))
	{
		return false;
	}

	rbWorld = new World();

	rbWorld->createLevel();
	rbWorld->applyForces();
	return true;
}

bool Game::initGraphics(int argc, char *argv[])
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	window = glfwCreateWindow((int)winSize.x, (int)winSize.y, winName.c_str(), NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glutInit(&argc, argv);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST); // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL); // Set the type of depth-test
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	viewCam = new Camera(0.0f, 15.0f, 30.0f);

	viewCam->setCamSpecs(45.0f, (float)(winSize.x / winSize.y), 0.01f, powf(10, 8));
	glfwSetCursorPos(window, winSize.x * 0.5f, winSize.y * 0.5f);

	return true;
}

void Game::gameLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		//get deltaTime
		double newTime = glfwGetTime();
		deltaTime = (newTime - timeSinceLaunch);
		timeSinceLaunch = newTime;
		//cout << "Time Since Launch: " << timeSinceLaunch << "   DeltaTime:" << deltaTime << "\n";

		//updates
		rbWorld->runPhysics(deltaTime);
		//draw
		startDraw();
		rbWorld->draw();
		endDraw();

		if (resetSim)
		{
			resetSim = false;
			rbWorld->initBalls();
		}

	}
}

void Game::startDraw()
{
	glViewport(0, 0, (int)winSize.x, (int)winSize.y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Reset the matrix
	glMatrixMode(GL_PROJECTION);
	viewCam->draw(handleMouseMovement());
	glMatrixMode(GL_MODELVIEW);
}

void Game::endDraw()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

Vector2 Game::handleMouseMovement()
{
	double mouseX = 0;
	double mouseY = 0;

	

	if (lockMouse)
	{
		glfwGetCursorPos(window, &(mouseX), &(mouseY));

		mouseX = (mouseX - winSize.x * 0.5f) / mouseSensitivity;
		mouseY = (mouseY - winSize.y * 0.5f) / mouseSensitivity;

		glfwSetCursorPos(window, winSize.x * 0.5f, winSize.y * 0.5f);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	Vector2 result = Vector2(mouseX, mouseY);
	return result;
}

void Game::cleanup()
{
	rbWorld->cleanup();
	delete rbWorld;
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
