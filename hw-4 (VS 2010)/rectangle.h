#pragma once
#include "polygon.h"
#include"GP142.H"
//#include"GP142LIB.H"
class rectangle : public polygon
{

public:
	rectangle();
	rectangle(int clr,int mouse_x, int mouse_y);
	~rectangle();
	void draw();
	bool contains(point p);
	void fill(int clr);
	void serialize(ostream &file);
	void deserialize(string & filename, istream & in);
};

