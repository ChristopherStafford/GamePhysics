#include "Vector2.h"

Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2::Vector2(double newX, double newY)
{
	x = newX;
	y = newY;
}

double Vector2::distanceSquared(Vector2 other)
{
	return (other.x - x) * (other.x - x)
		+ (other.y - y) * (other.y - y);
}