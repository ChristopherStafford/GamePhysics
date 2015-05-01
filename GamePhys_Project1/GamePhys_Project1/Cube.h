#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"

class Cube : public Shape
{
private:

public:
	Cube();
	Cube(float x, float y, float z);

	void draw();
};
#endif