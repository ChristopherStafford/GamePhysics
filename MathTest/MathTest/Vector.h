#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <sstream>
using namespace std;



class Vector3
{
public:
	double x;
	double y;
	double z;

	Vector3();
	Vector3(double newX, double newY, double newZ);

	double dotProduct(Vector3 other) const;
	double distance(Vector3 other);
	double distanceSquared(Vector3 other);
	void addScaledVector(Vector3 vector, double scaler);
	double getMagnitude();
	double magnitudeSquared() const;
	void normalize();
	string toString();
	void clear(){x = y = z = 0;};

	Vector3 componentProduct(const Vector3 &vector) const;


	Vector3 operator+(const Vector3& right) const;
	Vector3 operator-(const Vector3& right) const;
	Vector3 operator*(const double& right) const;
	Vector3& operator+=(const Vector3& right);
	Vector3& operator-=(const Vector3& right);
	Vector3& operator*=(const Vector3& right);
	Vector3& operator*=(const double& right);
	double& operator[](int index);
	double operator[](int index) const;


	void copy(Vector3 other);

	static Vector3 crossProduct(Vector3 a, Vector3 b);

};



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