#include "Matrix.h"

Matrix4::Matrix4()
{
	data[1] = data[2] = data[3] = data[4] = data[6] =
		data[7] = data[8] = data[9] = data[11] = 0;
	data[0] = data[5] = data[10] = 1;
}

void Matrix4::setDiagonal(double a, double b, double c)
{
	data[0] = a;
	data[5] = b;
	data[10] = c;
}

Vector3 Matrix4::transform(const Vector3 &vector) const
{
	return (*this) * vector;
}


Matrix4 Matrix4::inverse() const
{
	Matrix4 result;
	result.setInverse(*this);
	return result;
}

double Matrix4::getDeterminant() const
{
	return -data[8] * data[5] * data[2] +
		data[4] * data[9] * data[2] +
		data[8] * data[1] * data[6] -
		data[0] * data[9] * data[6] -
		data[4] * data[1] * data[10] +
		data[0] * data[5] * data[10];
}

Vector3 Matrix4::getAxisVector(int i) const
{
	return Vector3(data[i], data[i + 4], data[i + 8]);
}

void Matrix4::setAxisVector(int i, double a, double b, double c) {
	data[i] = a; data[i + 4] = b; data[i + 8] = c;
}

void Matrix4::setInverse(const Matrix4 &m)
{
	// Make sure the determinant is non-zero.
	double det = getDeterminant();
	if (det == 0) return;
	det = ((double)1.0) / det;

	data[0] = (-m.data[9] * m.data[6] + m.data[5] * m.data[10])*det;
	data[4] = (m.data[8] * m.data[6] - m.data[4] * m.data[10])*det;
	data[8] = (-m.data[8] * m.data[5] + m.data[4] * m.data[9])*det;

	data[1] = (m.data[9] * m.data[2] - m.data[1] * m.data[10])*det;
	data[5] = (-m.data[8] * m.data[2] + m.data[0] * m.data[10])*det;
	data[9] = (m.data[8] * m.data[1] - m.data[0] * m.data[9])*det;

	data[2] = (-m.data[5] * m.data[2] + m.data[1] * m.data[6])*det;
	data[6] = (+m.data[4] * m.data[2] - m.data[0] * m.data[6])*det;
	data[10] = (-m.data[4] * m.data[1] + m.data[0] * m.data[5])*det;

	data[3] = (m.data[9] * m.data[6] * m.data[3]
		- m.data[5] * m.data[10] * m.data[3]
		- m.data[9] * m.data[2] * m.data[7]
		+ m.data[1] * m.data[10] * m.data[7]
		+ m.data[5] * m.data[2] * m.data[11]
		- m.data[1] * m.data[6] * m.data[11])*det;
	data[7] = (-m.data[8] * m.data[6] * m.data[3]
		+ m.data[4] * m.data[10] * m.data[3]
		+ m.data[8] * m.data[2] * m.data[7]
		- m.data[0] * m.data[10] * m.data[7]
		- m.data[4] * m.data[2] * m.data[11]
		+ m.data[0] * m.data[6] * m.data[11])*det;
	data[11] = (m.data[8] * m.data[5] * m.data[3]
		- m.data[4] * m.data[9] * m.data[3]
		- m.data[8] * m.data[1] * m.data[7]
		+ m.data[0] * m.data[9] * m.data[7]
		+ m.data[4] * m.data[1] * m.data[11]
		- m.data[0] * m.data[5] * m.data[11])*det;
}

Vector3 Matrix4::transformDirection(const Vector3 &vector) const
{
	return Vector3(
		vector.x * data[0] +
		vector.y * data[1] +
		vector.z * data[2],

		vector.x * data[4] +
		vector.y * data[5] +
		vector.z * data[6],

		vector.x * data[8] +
		vector.y * data[9] +
		vector.z * data[10]
		);
}

Vector3 Matrix4::transformInverseDirection(const Vector3 &vector) const
{
	return Vector3(
		vector.x * data[0] +
		vector.y * data[4] +
		vector.z * data[8],

		vector.x * data[1] +
		vector.y * data[5] +
		vector.z * data[9],

		vector.x * data[2] +
		vector.y * data[6] +
		vector.z * data[10]
		);
}

Vector3 Matrix4::transformInverse(const Vector3 &vector) const
{
	Vector3 tmp = vector;
	tmp.x -= data[3];
	tmp.y -= data[7];
	tmp.z -= data[11];
	return Vector3(
		tmp.x * data[0] +
		tmp.y * data[4] +
		tmp.z * data[8],

		tmp.x * data[1] +
		tmp.y * data[5] +
		tmp.z * data[9],

		tmp.x * data[2] +
		tmp.y * data[6] +
		tmp.z * data[10]
		);
}








Matrix4 Matrix4::operator*(const Matrix4 &o) const
{
	Matrix4 result;
	result.data[0] = (o.data[0] * data[0]) + (o.data[4] * data[1]) + (o.data[8] * data[2]);
	result.data[4] = (o.data[0] * data[4]) + (o.data[4] * data[5]) + (o.data[8] * data[6]);
	result.data[8] = (o.data[0] * data[8]) + (o.data[4] * data[9]) + (o.data[8] * data[10]);

	result.data[1] = (o.data[1] * data[0]) + (o.data[5] * data[1]) + (o.data[9] * data[2]);
	result.data[5] = (o.data[1] * data[4]) + (o.data[5] * data[5]) + (o.data[9] * data[6]);
	result.data[9] = (o.data[1] * data[8]) + (o.data[5] * data[9]) + (o.data[9] * data[10]);

	result.data[2] = (o.data[2] * data[0]) + (o.data[6] * data[1]) + (o.data[10] * data[2]);
	result.data[6] = (o.data[2] * data[4]) + (o.data[6] * data[5]) + (o.data[10] * data[6]);
	result.data[10] = (o.data[2] * data[8]) + (o.data[6] * data[9]) + (o.data[10] * data[10]);

	result.data[3] = (o.data[3] * data[0]) + (o.data[7] * data[1]) + (o.data[11] * data[2]) + data[3];
	result.data[7] = (o.data[3] * data[4]) + (o.data[7] * data[5]) + (o.data[11] * data[6]) + data[7];
	result.data[11] = (o.data[3] * data[8]) + (o.data[7] * data[9]) + (o.data[11] * data[10]) + data[11];

	return result;
}

Vector3 Matrix4::operator*(const Vector3 &vector) const
{
	return Vector3(
		vector.x * data[0] +
		vector.y * data[1] +
		vector.z * data[2] + data[3],

		vector.x * data[4] +
		vector.y * data[5] +
		vector.z * data[6] + data[7],

		vector.x * data[8] +
		vector.y * data[9] +
		vector.z * data[10] + data[11]
		);
}

////////////////////////////////////////////////////////////////////////////////
//////////////////////////  matrix3  ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Matrix3::Matrix3()
{
	data[0] = data[1] = data[2] = data[3] = data[4] = data[5] =
		data[6] = data[7] = data[8] = 0;
}

Matrix3::Matrix3(const Vector3 &compOne, const Vector3 &compTwo, const Vector3 &compThree)
{
	setComponents(compOne, compTwo, compThree);
}

Matrix3::Matrix3(double c0, double c1, double c2, double c3, double c4, double c5, double c6, double c7, double c8)
{
	data[0] = c0; data[1] = c1; data[2] = c2;
	data[3] = c3; data[4] = c4; data[5] = c5;
	data[6] = c6; data[7] = c7; data[8] = c8;
}

void Matrix3::setInertiaTensorCoeffs(double ix, double iy, double iz,
	double ixy, double ixz, double iyz)
{
	data[0] = ix;
	data[1] = data[3] = -ixy;
	data[2] = data[6] = -ixz;
	data[4] = iy;
	data[5] = data[7] = -iyz;
	data[8] = iz;
}

void Matrix3::setBlockInertiaTensor(const Vector3 &halfSizes, double mass)
{
	Vector3 squares = halfSizes.componentProduct(halfSizes);
	setInertiaTensorCoeffs(0.3f*mass*(squares.y + squares.z),
		0.3f*mass*(squares.x + squares.z),
		0.3f*mass*(squares.x + squares.y));
}

void Matrix3::setSkewSymmetric(const Vector3 vector)
{
	data[0] = data[4] = data[8] = 0;
	data[1] = -vector.z;
	data[2] = vector.y;
	data[3] = vector.z;
	data[5] = -vector.x;
	data[6] = -vector.y;
	data[7] = vector.x;
}

void Matrix3::setComponents(const Vector3 &compOne, const Vector3 &compTwo, const Vector3 &compThree)
{
	data[0] = compOne.x;
	data[1] = compTwo.x;
	data[2] = compThree.x;
	data[3] = compOne.y;
	data[4] = compTwo.y;
	data[5] = compThree.y;
	data[6] = compOne.z;
	data[7] = compTwo.z;
	data[8] = compThree.z;
}

Vector3 Matrix3::transformTranspose(const Vector3 &vector) const
{
	return Vector3(
		vector.x * data[0] + vector.y * data[3] + vector.z * data[6],
		vector.x * data[1] + vector.y * data[4] + vector.z * data[7],
		vector.x * data[2] + vector.y * data[5] + vector.z * data[8]
		);
}

void Matrix3::setInverse(const Matrix3 &m)
{
	double t4 = m.data[0] * m.data[4];
	double t6 = m.data[0] * m.data[5];
	double t8 = m.data[1] * m.data[3];
	double t10 = m.data[2] * m.data[3];
	double t12 = m.data[1] * m.data[6];
	double t14 = m.data[2] * m.data[6];

	// Calculate the determinant
	double t16 = (t4*m.data[8] - t6*m.data[7] - t8*m.data[8] +
		t10*m.data[7] + t12*m.data[5] - t14*m.data[4]);

	// Make sure the determinant is non-zero.
	if (t16 == (double)0.0f) return;
	double t17 = 1 / t16;

	data[0] = (m.data[4] * m.data[8] - m.data[5] * m.data[7])*t17;
	data[1] = -(m.data[1] * m.data[8] - m.data[2] * m.data[7])*t17;
	data[2] = (m.data[1] * m.data[5] - m.data[2] * m.data[4])*t17;
	data[3] = -(m.data[3] * m.data[8] - m.data[5] * m.data[6])*t17;
	data[4] = (m.data[0] * m.data[8] - t14)*t17;
	data[5] = -(t6 - t10)*t17;
	data[6] = (m.data[3] * m.data[7] - m.data[4] * m.data[6])*t17;
	data[7] = -(m.data[0] * m.data[7] - t12)*t17;
	data[8] = (t4 - t8)*t17;
}

Matrix3 Matrix3::inverse() const
{
	Matrix3 result;
	result.setInverse(*this);
	return result;
}

void Matrix3::setTranspose(const Matrix3 &m)
{
	data[0] = m.data[0];
	data[1] = m.data[3];
	data[2] = m.data[6];
	data[3] = m.data[1];
	data[4] = m.data[4];
	data[5] = m.data[7];
	data[6] = m.data[2];
	data[7] = m.data[5];
	data[8] = m.data[8];
}

Matrix3 Matrix3::transpose() const
{
	Matrix3 result;
	result.setTranspose(*this);
	return result;
}

void Matrix3::setOrientation(const Quaternion &q)
{
	data[0] = 1 - (2 * q.j*q.j + 2 * q.k*q.k);
	data[1] = 2 * q.i*q.j + 2 * q.k*q.r;
	data[2] = 2 * q.i*q.k - 2 * q.j*q.r;
	data[3] = 2 * q.i*q.j - 2 * q.k*q.r;
	data[4] = 1 - (2 * q.i*q.i + 2 * q.k*q.k);
	data[5] = 2 * q.j*q.k + 2 * q.i*q.r;
	data[6] = 2 * q.i*q.k + 2 * q.j*q.r;
	data[7] = 2 * q.j*q.k - 2 * q.i*q.r;
	data[8] = 1 - (2 * q.i*q.i + 2 * q.j*q.j);
}

void Matrix3::setColumns(Vector3 col1, Vector3 col2, Vector3 col3)
{
	data[0] = col1.x;
	data[3] = col1.y;
	data[6] = col1.z;

	data[1] = col2.x;
	data[4] = col2.y;
	data[7] = col2.z;

	data[2] = col3.x;
	data[5] = col3.y;
	data[8] = col3.z;
}


Matrix3 Matrix3::operator*(const Matrix3 &o) const
{
	return Matrix3(
		data[0] * o.data[0] + data[1] * o.data[3] + data[2] * o.data[6],
		data[0] * o.data[1] + data[1] * o.data[4] + data[2] * o.data[7],
		data[0] * o.data[2] + data[1] * o.data[5] + data[2] * o.data[8],

		data[3] * o.data[0] + data[4] * o.data[3] + data[5] * o.data[6],
		data[3] * o.data[1] + data[4] * o.data[4] + data[5] * o.data[7],
		data[3] * o.data[2] + data[4] * o.data[5] + data[5] * o.data[8],

		data[6] * o.data[0] + data[7] * o.data[3] + data[8] * o.data[6],
		data[6] * o.data[1] + data[7] * o.data[4] + data[8] * o.data[7],
		data[6] * o.data[2] + data[7] * o.data[5] + data[8] * o.data[8]
		);
}

Vector3 Matrix3::operator*(const Vector3 &vector) const
{
	return Vector3(
		vector.x * data[0] + vector.y * data[1] + vector.z * data[2],
		vector.x * data[3] + vector.y * data[4] + vector.z * data[5],
		vector.x * data[6] + vector.y * data[7] + vector.z * data[8]
		);
}

void Matrix3::operator*=(const Matrix3 &o)
{
	double t1;
	double t2;
	double t3;

	t1 = data[0] * o.data[0] + data[1] * o.data[3] + data[2] * o.data[6];
	t2 = data[0] * o.data[1] + data[1] * o.data[4] + data[2] * o.data[7];
	t3 = data[0] * o.data[2] + data[1] * o.data[5] + data[2] * o.data[8];
	data[0] = t1;
	data[1] = t2;
	data[2] = t3;

	t1 = data[3] * o.data[0] + data[4] * o.data[3] + data[5] * o.data[6];
	t2 = data[3] * o.data[1] + data[4] * o.data[4] + data[5] * o.data[7];
	t3 = data[3] * o.data[2] + data[4] * o.data[5] + data[5] * o.data[8];
	data[3] = t1;
	data[4] = t2;
	data[5] = t3;

	t1 = data[6] * o.data[0] + data[7] * o.data[3] + data[8] * o.data[6];
	t2 = data[6] * o.data[1] + data[7] * o.data[4] + data[8] * o.data[7];
	t3 = data[6] * o.data[2] + data[7] * o.data[5] + data[8] * o.data[8];
	data[6] = t1;
	data[7] = t2;
	data[8] = t3;
}

void Matrix3::operator*=(const double scalar)
{
	data[0] *= scalar; data[1] *= scalar; data[2] *= scalar;
	data[3] *= scalar; data[4] *= scalar; data[5] *= scalar;
	data[6] *= scalar; data[7] *= scalar; data[8] *= scalar;
}

void Matrix3::operator+=(const Matrix3 &o)
{
	data[0] += o.data[0]; data[1] += o.data[1]; data[2] += o.data[2];
	data[3] += o.data[3]; data[4] += o.data[4]; data[5] += o.data[5];
	data[6] += o.data[6]; data[7] += o.data[7]; data[8] += o.data[8];
}