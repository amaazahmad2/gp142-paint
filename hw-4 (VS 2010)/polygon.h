#pragma once
#include "shape.h"
#include"GP142.H"
//#include"GP142LIB.H"
class polygon : public shape
{
protected:
	int fillColor;

public:
	polygon();
	polygon(int clr, int mouse_x, int mouse_y);
	~polygon();
	virtual void draw();
	virtual bool contains(point p);
	virtual void fill(int clr);
	void serialize(ostream &file);
	void deserialize(string & filename, istream & in);
};



