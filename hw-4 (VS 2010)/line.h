#pragma once
#include "openShape.h"
#include"GP142.H"
//#include"GP142LIB.H"
class line : public openShape
{
public:
	line();
	line(int color, bool style, int mouse_x,int mouse_y);
	void draw();
	void changeColor();
	bool contains(point p);
	void serialize(ostream &file);
	void deserialize(string & filename, istream & in);
	~line();
};

void drawDottedLine(int clr, int x1, int y1, int x2, int y2);