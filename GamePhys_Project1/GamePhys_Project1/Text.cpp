#include "Text.h"

Text::Text()
	:Shape()
{
	init();
}

Text::Text(float x, float y, float z)
	: Shape(x, y, z)
{
	init();
}

void Text::init()
{
	myText = vector<string>();
	myText.push_back("You can't play movies on a seashell.");
	color = Color::white();
}

void Text::draw()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);

	glEnable(GL_DEPTH_TEST);

	glColor4f(color.r, color.g, color.b, color.a);
	for (int i = 0; i < myText.size(); i++)
		drawString(-1, 0.95f - (i * 0.05f), myText[i], color);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


void Text::drawString(float x, float y, string text, Color color)
{
	const char* temp = text.c_str();

	glRasterPos2f(x, y);

	char buf[300];
	sprintf_s(buf, temp);

	const char *p = buf;

	glColor4f(color.r, color.g, color.b, color.a);

	do glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);
	while (*(++p));
}

void Text::clearText()
{
	myText.clear();
}