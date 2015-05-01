#include "ForceGenerator.h"

void Gravity::updateForce(RigidBody *body, double duration)
{
	if (!body->hasFiniteMass()) return;

	body->addForce(gravity * body->getMass());
}

Spring::Spring(Vector3 localConnectionPt, RigidBody *otherOb,
	Vector3 otherConnectionPt, double sc, double length)
{
	/*cout << "Initialized spring:" << endl
		<< "lcp: " << localConnectionPt.toString() << endl
		<< "other: " << (otherOb != NULL) << endl
		<< "ocp: " << otherConnectionPt.toString() << endl
		<< "sc: " << sc << endl
		<< "length: " << length << endl;*/

	connectionPoint = localConnectionPt;
	otherConnectionPoint = otherConnectionPt;
	other = otherOb;
	springConstant = sc;
	restLength = length;
}

void Spring::updateForce(RigidBody *body, double duration)
{
	Vector3 lws = body->getPointInWorldSpace(connectionPoint);
	Vector3 ows = other->getPointInWorldSpace(otherConnectionPoint);

	Vector3 force = lws - ows;
	double magnetude = force.getMagnitude();
	magnetude *= springConstant;
	force.normalize();
	force *= -magnetude;
	body->addForceAtPoint(force, lws);
}