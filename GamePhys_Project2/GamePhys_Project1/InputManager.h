#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "InputCodes.h"

#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

class InputManager
{

public:
	InputManager();
	bool init();

	void handleKeyPress(int key, int action);

	bool getKeyDown(InputCodes code);
	bool getKey(InputCodes code);
};

#endif