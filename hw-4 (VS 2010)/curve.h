#pragma once
#include "openShape.h"
#include"GP142.H"
//#include"GP142LIB.H"
class curve : public openShape
{
public:
	curve();
	curve(int clr, bool style, int mouse_x, int mouse_y);
	~curve();
	void draw();
	void changeColor();
	bool contains(point p);
	void serialize(ostream &file);
	void deserialize(string & filename, istream & in);
};

