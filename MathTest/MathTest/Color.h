#ifndef COLOR_H
#define COLOR_H


class Color
{
public:
	Color();
	Color(float red, float green, float blue);
	Color(float red, float green, float blue, float alpha);

	float r;
	float g;
	float b;
	float a;


	static Color red(){ return Color(1, 0, 0); };
	static Color blue(){ return Color(0, 0, 1); };
	static Color green(){ return Color(0, 1, 0); };

	static Color yellow(){ return Color(1, 1, 0); };
	static Color magenta(){ return Color(1, 0, 1); };
	static Color cyan(){ return Color(0, 1, 1); };

	static Color white(){ return Color(1, 1, 1); };
	static Color black(){ return Color(0, 0, 0); };
	static Color clear(){ return Color(0, 0, 0, 0); };

	Color operator=(const Color& right);
	void copy(Color other);
};

#endif