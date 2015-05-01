#include "Vector3.h"

Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3::Vector3(double newX, double newY, double newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}

double Vector3::distanceSquared(Vector3 other)
{
	return (other.x - x) * (other.x - x)
		+ (other.y - y) * (other.y - y)
		+ (other.z - z) * (other.z - z);
}


double Vector3::dotProduct(Vector3 other)
{
	return (x*other.x) + (y*other.y) + (z*other.z);
}

void Vector3::addScaledVector(Vector3 vector, double scaler)
{
	x += vector.x * scaler;
	y += vector.y * scaler;
	z += vector.z * scaler;
}

double Vector3::getMagnitude()
{
	double magnitude = sqrt( pow(x, 2) + pow(y, 2) + pow(z, 2));
	return abs(magnitude);
}

void Vector3::normalize()
{
	double mag = getMagnitude();

	x = x / mag;
	y = y / mag;
	z = z / mag;
}

string Vector3::toString()
{
	stringstream ss;
	ss << x;
	ss << " | ";
	ss << y;
	ss << " | ";
	ss << z;

	return ss.str();
}

void Vector3::copy(Vector3 other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}



Vector3 Vector3::operator+(const Vector3& right)
{
	Vector3 result;
	result.x = x + right.x;
	result.y = y + right.y;
	result.z = z + right.z;
	return result;
}

Vector3 Vector3::operator-(const Vector3& right)
{
	Vector3 result;
	result.x = x - right.x;
	result.y = y - right.y;
	result.z = z - right.z;
	return result;
}

Vector3 Vector3::operator*(const double& right)
{
	Vector3 result;
	result.x = x * right;
	result.y = y * right;
	result.z = z * right;
	return result;
}

Vector3& Vector3::operator+=(const Vector3& right)
{
	x += right.x;
	y += right.y;
	z += right.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& right)
{
	x -= right.x;
	y -= right.y;
	z -= right.z;
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& right)
{
	x *= right.x;
	y *= right.y;
	z *= right.z;
	return *this;
}


Vector3& Vector3::operator*=(const double& right)
{
	x *= right;
	y *= right;
	z *= right;
	return *this;
}