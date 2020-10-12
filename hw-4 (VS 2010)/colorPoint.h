#pragma once
#include "shape.h"
class colorPoint : public shape
{
protected:
	int color, x, y;
public:
	colorPoint();
	colorPoint(int xp, int yp, int clr);
	void draw();
	bool contains(point p);
	void serialize(ostream &file);
	void deserialize(string & filename, istream & file);
	~colorPoint();
};

