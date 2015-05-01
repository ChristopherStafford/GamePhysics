#include "Camera.h"

Camera::Camera()
{
	init();
	initialPosition = position;
	initialRotation = rotation;
}

Camera::Camera(float x, float y, float z)
{
	init();
	position = Vector3(x,y,z);
	initialPosition = position;
	initialRotation = rotation;
}

void Camera::init()
{
	position = Vector3();
	rotation = Vector3(30, 0, 0);
	camSpecs = CamSpecs();
	moveSpeed = 1;
	offset = Vector3(0, 0, 100);
	//debugText = Text();
	targeted = false;
}

void Camera::setCamSpecs(float fov, float aspectRatio, float nearClip, float farClip)
{
	camSpecs.fov = fov;
	camSpecs.aspectRatio = aspectRatio;
	camSpecs.nearClip = nearClip;
	camSpecs.farClip = farClip;
}
double Camera::degToRad(double angle)
{
	return angle * (3.1415f / 180.0f);
}

void Camera::draw(Vector2 mouseDelta)
{
	glLoadIdentity();
	gluPerspective(camSpecs.fov, camSpecs.aspectRatio,
		camSpecs.nearClip, camSpecs.farClip);

	//rotation.x += mouseDelta.y;
	//rotation.y += mouseDelta.x;

	if (rotation.x < -90.0f)
	{
		rotation.x = -90.0f;
	}
	if (rotation.x > 90.0f)
	{
		rotation.x = 90.0f;
	}

	if (rotation.y < -180.0f)
	{
		rotation.y += 360.0f;
	}
	if (rotation.y > 180.0f)
	{
		rotation.y -= 360.0f;
	}


	//handleMovement();
	
	/*
	if (lookTarget != NULL )
	{

		gluLookAt(position.x, position.y, position.z,
			lookTarget->getPosition().x,
			lookTarget->getPosition().y,
			lookTarget->getPosition().z,
			0.0f, 1.0f, 0.0f);
		
		if (showDebug)
		{
			stringstream ss;
			

			ss << lookTarget->getName();
			debugText.myText.push_back(ss.str());
			ss.str("");

			ss << "Position: " << lookTarget->getPosition().x <<
				" :: " << lookTarget->getPosition().y <<
				" :: " << lookTarget->getPosition().z;
			debugText.myText.push_back(ss.str());
			ss.str("");

			ss << "Velocity: " << lookTarget->getVelocity().x <<
				" :: " << lookTarget->getVelocity().y <<
				" :: " << lookTarget->getVelocity().z;
			debugText.myText.push_back(ss.str());
			ss.str("");

			ss << "Mass: " << lookTarget->getMass();
			debugText.myText.push_back(ss.str());
			ss.str("");
		}
			debugText.draw();
	}*/

	glRotatef((float)rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef((float)rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef((float)rotation.z, 0.0f, 0.0f, 1.0f);

	glTranslatef((float)(-position.x), (float)(-position.y), (float)(-position.z));
}


void Camera::setTarget(Particle* p)
{
	lookTarget = p;
	targeted = true;
}

void Camera::reset()
{
	position = initialPosition;
	rotation = initialRotation;
	lookTarget = NULL;
}

void Camera::handleMovement()
{
	double pitch;
	double yaw;

	if (forwardDown)
	{
		pitch = cos(degToRad(rotation.x));
		yaw = float(cos(degToRad(rotation.x)));

		position.x += (moveSpeed * sin(degToRad(rotation.y))) * pitch;
		position.y += moveSpeed * sin(degToRad(rotation.x)) * -1.0f;
		position.z += (moveSpeed * cos(degToRad(rotation.y)) * -1.0f) * yaw;


	}
	else if (backwardDown)
	{
		pitch = cos(degToRad(rotation.x));
		yaw = cos(degToRad(rotation.x));

		position.x += (moveSpeed * sin(degToRad(rotation.y)) * -1.0f) * pitch;
		position.y += moveSpeed * sin(degToRad(rotation.x));
		position.z += (moveSpeed * cos(degToRad(rotation.y))) * yaw;
	}

	double yRotRad;

	if (rightDown)
	{
		yRotRad = degToRad(rotation.y);
		position.x += moveSpeed * cos(yRotRad);
		position.z += moveSpeed * sin(yRotRad);
	}
	else if (leftDown)
	{
		yRotRad = degToRad(rotation.y);
		position.x += -moveSpeed * cos(yRotRad);
		position.z += -moveSpeed * sin(yRotRad);
	}
}