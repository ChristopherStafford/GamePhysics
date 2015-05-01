#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
public:
	Vector2();
	Vector2(double newX, double newY);

	double distanceSquared(Vector2 other);

	double x;
	double y;

};

#endif