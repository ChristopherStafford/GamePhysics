#ifndef VECTOR3_H
#define VECTOR3_H

#include <math.h>

class Vector3
{
public:
	Vector3();
	Vector3(double newX, double newY, double newZ);

	double distanceSquared(Vector3 other);
	void addScaledVector(Vector3 vector, double scaler);
	double getMagnitude();
	void normalize();

	double x;
	double y;
	double z;

	Vector3 operator+(const Vector3& right);
	Vector3 operator-(const Vector3& right);
	Vector3 operator*(const double& right);
	Vector3& operator+=(const Vector3& right);
	Vector3& operator-=(const Vector3& right);
	Vector3& operator*=(const Vector3& right);
	Vector3& operator*=(const double& right);

	void copy(Vector3 other);

};

#endif