#pragma once
#include "shape.h"
#include"GP142.H"
#include"GP142LIB.H"
class circle : public shape
{
protected:
	double radius;
	int fillColor;

public:
	circle();
	circle(int clr, int nop, point* ps, int fillclr, double rad);
	circle(int clr,int mouse_x, int mouse_y);
	~circle();
	void fill(int clr);
	void draw();
	bool contains(point p);
	void serialize(ostream &file);
	void deserialize(string & filename, istream & in);

	friend void eraser(point &p, vector<shape*>&allShapes);
};

