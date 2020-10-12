#pragma once
#include "shape.h"
#include"GP142.H"


class text : public shape
{
private:
	char* str;
	int size;
public:
	text();
	text(char*s, int clr, int si);
	text(int clr, int mouse_x, int mouse_y);
	~text();
	void changeColor(int clr);
	void changeSize(int s);
	void draw();
	bool contains(point p);
	void serialize(ostream &file);
	void deserialize(string & filename, istream & in);
	
};

