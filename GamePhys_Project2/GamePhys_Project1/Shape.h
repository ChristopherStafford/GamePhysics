#ifndef SHAPE_H
#define SHAPE_H

#include <windows.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>


#include <gl/freeglut.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>

#include "Vector3.h"

class Shape
{

protected:
	Vector3 position;
	Vector3 rotation;

public:
	Shape();
	Shape(float x, float y, float z);
	virtual void draw();

	Vector3 getPosition(){ return position; };
	Vector3 getRotation(){ return rotation; };

};
#endif