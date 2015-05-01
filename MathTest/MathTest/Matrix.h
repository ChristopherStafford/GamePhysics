#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"
#include "Quaternion.h"

class Matrix3
{
public:
	double data[9];

	Matrix3();
	Matrix3(const Vector3 &compOne, const Vector3 &compTwo, const Vector3 &compThree);
	Matrix3(double c0, double c1, double c2, double c3, double c4, double c5, double c6, double c7, double c8);

	void setDiagonal(double a, double b, double c){ setInertiaTensorCoeffs(a, b, c); };
	void setInertiaTensorCoeffs(double ix, double iy, double iz, double ixy = 0, double ixz = 0, double iyz = 0);
	void setBlockInertiaTensor(const Vector3 &halfSizes, double mass);
	void setSkewSymmetric(const Vector3 vector);
	void setComponents(const Vector3 &compOne, const Vector3 &compTwo, const Vector3 &compThree);
	Vector3 transform(const Vector3 &vector) const { return (*this) * vector; };
	Vector3 transformTranspose(const Vector3 &vector) const;
	Vector3 getRowVector(int i) const { return Vector3(data[i * 3], data[i * 3 + 1], data[i * 3 + 2]); }
	Vector3 getAxisVector(int i) const { return Vector3(data[i], data[i + 3], data[i + 6]); }
	void setInverse(const Matrix3 &m);
	Matrix3 inverse() const;
	void invert(){ setInverse(*this); };
	void setTranspose(const Matrix3 &m);
	Matrix3 transpose() const;
	void setOrientation(const Quaternion &q);
	void setColumns(Vector3 col1, Vector3 col2, Vector3 col3);

	Matrix3 operator*(const Matrix3 &o) const;
	Vector3 operator*(const Vector3 &vector) const;
	void operator*=(const Matrix3 &o);
	void operator*=(const double scalar);
	void operator+=(const Matrix3 &o);

};

class Matrix4
{
public:
	double data[12];

	Matrix4();

	void setDiagonal(double a, double b, double c);
	Vector3 transform(const Vector3 &vector) const;
	double getDeterminant() const;
	void setInverse(const Matrix4 &m);
	Matrix4 inverse() const;
	Vector3 getAxisVector(int i) const;
	void setAxisVector(int i, double a, double b, double c);

	void invert(){ setInverse(*this); };
	Vector3 transformDirection(const Vector3 &vector) const;
	Vector3 transformInverseDirection(const Vector3 &vector) const;
	Vector3 transformInverse(const Vector3 &vector) const;

	Matrix4 operator*(const Matrix4& o) const;
	Vector3 operator*(const Vector3 &vector) const;

};

#endif