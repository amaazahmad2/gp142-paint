#include "curve.h"
#include<cmath>
#include<fstream>


curve::curve()
{
}

curve::curve(int clr, bool stl, int mouse_x, int mouse_y)
	:openShape(stl)
{
	point p;
	char key_pressed;
	color = clr;
	p.x = mouse_x;
	p.y = mouse_y;
	numOfPoints = 0;
	point_pushback(p, Points, numOfPoints);
	while (GP142_await_event(&mouse_x, &mouse_y, &key_pressed) != GP142_KBD)
	{
		if (mouse_x < -700 || mouse_y < -295)
			continue;
		p.x = mouse_x; p.y = mouse_y;
		point_pushback(p, Points, numOfPoints);
	}
}


curve::~curve()
{
}

void curve::draw()
{
	for (int i = 1; i < numOfPoints; i++)
	{
		GP142_lineXY(color, Points[i - 1].x, Points[i - 1].y, Points[i].x, Points[i].y, 1);
	}
}

void curve::changeColor()
{

}

bool curve::contains(point p)
{
	for (int i = 1; i < numOfPoints; i++)
	{
		int d1 = sqrt(pow(p.x - Points[i-1].x, 2) + pow(p.y - Points[i-1].y, 2));
		int d2 = sqrt(pow(p.x - Points[i].x, 2) + pow(p.y - Points[i].y, 2));
		int totalLength = sqrt(pow(Points[i-1].x - Points[i].x, 2) + pow(Points[i-1].y - Points[i].y, 2));
		if (d1 + d2 == totalLength)
			return true;
		else
			return false;
	}
}

void curve::serialize(ostream &fname)
{
	fname << "oval" << endl;
	fname.write((char*)&Points[0], sizeof(Points[0]));
	fname.write((char*)&Points[1], sizeof(Points[1]));
	fname.write((char*)&color, sizeof(color));
}

void curve::deserialize(string &filename, istream &in)
{
	in.read((char*)&Points[0], sizeof(Points[0]));
	in.read((char*)&Points[1], sizeof(Points[1]));
	in.read((char*)&color, sizeof(color));
}
