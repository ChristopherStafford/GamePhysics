#ifndef TEXT_H
#define TEXT_H

#include "Shape.h"
#include "Color.h"
#include <string>
#include <vector>
using namespace std;

class Text : public Shape
{
private:
	
	Color color;
	void init();

public:
	vector<string> myText;
	Text();
	Text(float x, float y, float z);
	void draw();
	void drawString(float x, float y, string text, Color color);

	void clearText();
};
#endif