#include "Transform.h"

Transform::Transform()
{

}

void Transform::update()
{
	position += velocity * deltaTime + acceleration * deltaTime * deltaTime * 0.5f;
}

void Transform::integrate(double duration)
{
	/*if (inverseMass <= 0)
		return;

	assert(duration > 0.0);

	position.addScaledVector(velocity, duration);

	Vector3 resultingAcc = acceleration;

	velocity.addScaledVector(resultingAcc, duration);

	velocity *= powf(dampening, duration);

	clearAccumulator();

	*/
}