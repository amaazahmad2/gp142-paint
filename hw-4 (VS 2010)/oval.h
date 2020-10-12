#pragma once
#include "shape.h"
#include"GP142.H"
//#include"GP142LIB.H"
class oval : public shape
{
private:
	int fillColor;

public:
	oval();
	~oval();
	oval(int clr, int nop, point* ps, int fillclr);
	oval(int clr, int mouse_x, int mouse_y);
	void fill(int clr);
	void draw();
	bool contains(point p);

	void serialize(ostream &file);
	void deserialize(string & filename, istream & in);
};

