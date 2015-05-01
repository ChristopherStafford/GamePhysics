#include "Connection.h"


double Connection::currentLength()
{
	Vector3 relativePos = particle[0]->getPosition() - particle[1]->getPosition();
	return relativePos.getMagnitude();
}