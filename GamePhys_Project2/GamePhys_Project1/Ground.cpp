#include "Ground.h"

Ground::Ground(double x, double y, double z, Color c)
	:Particle()
{

	size = Vector3(10, 0.5f, 10);
	name = "Ground";
	mass = -1;
	startPosition = Vector3(x, y, z);
	startVelocity = Vector3(0, 0, 0);
	position = startPosition;
	velocity = startVelocity;
	color.r = c.r;
	color.g = c.g;
	color.b = c.b;
	color.a = c.a;

	initPosition.copy(position);
	initAcceleration.copy(acceleration);
	initRotation.copy(rotation);
	initVelocity.copy(velocity);

}

void Ground::draw()
{

	GLUquadricObj *s;
	s = gluNewQuadric();

	glLoadIdentity();
	glPushMatrix();

	//translate
	glTranslatef((float)(position.x),
		(float)(position.y - (size.y * 0.5f) ),
		(float)(position.z));

	//rotate
	glRotatef((float)rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef((float)rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef((float)rotation.z, 0.0f, 0.0f, 1.0f);

	glColor4f(color.r, color.g, color.b, color.a);

	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	// Top face (y = 1.0f)
	// Define vertices in counter-clockwise (CCW) order with normal pointing out
	glVertex3f( (float)(size.x), (float)(size.y), (float)(-size.z) );
	glVertex3f( (float)(-size.x), (float)(size.y), (float)(-size.z) );
	glVertex3f( (float)(-size.x), (float)(size.y), (float)(size.z) );
	glVertex3f( (float)(size.x), (float)(size.y), (float)(size.z) );

	// Bottom face (y = -1.0f)
	glVertex3f( (float)(size.x), (float)(-size.y), (float)(size.z) );
	glVertex3f( (float)(-size.x), (float)(-size.y), (float)(size.z) );
	glVertex3f( (float)(-size.x), (float)(-size.y), (float)(-size.z) );
	glVertex3f( (float)(size.x), (float)(-size.y), (float)(-size.z) );

	// Front face  (z = 1.0f)
	glVertex3f( (float)(size.x), (float)(size.y), (float)(size.z) );
	glVertex3f( (float)(-size.x), (float)(size.y), (float)(size.z) );
	glVertex3f( (float)(-size.x), (float)(-size.y), (float)(size.z) );
	glVertex3f( (float)(size.x), (float)(-size.y), (float)(size.z) );

	// Back face (z = -1.0f)
	glVertex3f( (float)(size.x), (float)(-size.y), (float)(-size.z) );
	glVertex3f( (float)(-size.x), (float)(-size.y), (float)(-size.z) );
	glVertex3f( (float)(-size.x), (float)(size.y), (float)(-size.z) );
	glVertex3f( (float)(size.x), (float)(size.y), (float)(-size.z) );

	// Left face (x = -1.0f)
	glVertex3f( (float)(-size.x), (float)(size.y), (float)(size.z) );
	glVertex3f( (float)(-size.x), (float)(size.y), (float)(-size.z) );
	glVertex3f( (float)(-size.x), (float)(size.y), (float)(-size.z) );
	glVertex3f( (float)(-size.x), (float)(-size.y), (float)(size.z) );

	// Right face (x = 1.0f)
	glVertex3f( (float)(size.x), (float)(size.y), (float)(-size.z) );
	glVertex3f( (float)(size.x), (float)(size.y), (float)(size.z) );
	glVertex3f( (float)(size.x), (float)(-size.y), (float)(size.z) );
	glVertex3f( (float)(size.x), (float)(-size.y), (float)(-size.z) );
	glEnd();

	

	glPopMatrix();
	gluDeleteQuadric(s);
}