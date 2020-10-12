#pragma once
#include "polygon.h"
#include"GP142.H"
#include"GP142LIB.H"
#include<fstream>

bool point_on_line(int x1, int y1, int x, int y, int x2, int y2)
{

	if (x <= max(x1, x2) && x >= min(x1, x2) && y <= max(y1, y2) && y >= min(y1, y2))
	{
		return true;
	}

	return false;
}

int orientation(int x1, int y1, int x, int y, int x2, int y2)
{
	int ori = (y - y1)*(x2 - x) - (x - x1)*(y2 - y);

	if (ori == 0)
	{
		return 0;
	}

	else if (ori > 0)
	{
		return 1;
	}

	else
	{
		return 2;
	}


}

bool intersects(int p1x, int p1y, int q1x, int q1y, int p2x, int p2y, int q2x, int q2y)
{
	int ori1, ori2, ori3, ori4;
	ori1 = orientation(p1x, p1y, q1x, q1y, p2x, p2y);
	ori2 = orientation(p1x, p1y, q1x, q1y, q2x, q2y);
	ori3 = orientation(p2x, p2y, q2x, q2y, p1x, p1y);
	ori4 = orientation(p2x, p2y, q2x, q2y, q1x, q1y);

	if (ori1 != ori2 && ori3 != ori4)
	{
		return true;
	}

	if (ori1 == 0 && point_on_line(p1x, p1y, p2x, p2y, q1x, p1y))
	{
		return true;
	}

	if (ori1 == 0 && point_on_line(p1x, p1y, q2x, q2y, q1x, q1y))
	{
		return true;
	}

	if (ori1 == 0 && point_on_line(p2x, p2y, p1x, p1y, q2x, p2y))
	{
		return true;
	}

	if (ori1 == 0 && point_on_line(p2x, p2y, q1x, q1y, q2x, q2y))
	{
		return true;
	}

	return false;

}




polygon::polygon()
{

}

polygon::polygon(int clr, int mouse_x, int mouse_y)
{
	point p;
	char key_pressed;
	color = clr;
	numOfPoints = 0;
	p.x = mouse_x;
	p.y = mouse_y;
	point_pushback(p, Points, numOfPoints);
	while (GP142_await_event(&mouse_x, &mouse_y, &key_pressed) != GP142_KBD)
	{
		if (mouse_x < -700 || mouse_y < -295)
			continue;
		p.x = mouse_x; p.y = mouse_y;
		point_pushback(p, Points, numOfPoints);
		
	}
	fillColor = -1;
}



polygon::~polygon()
{
}

void polygon::draw()
{
	for (int i = 1; i < numOfPoints; i++)
	{
		GP142_lineXY(color, Points[i - 1].x, Points[i - 1].y, Points[i].x, Points[i].y, 1);
	}
	GP142_lineXY(color,Points[numOfPoints - 1].x, Points[numOfPoints - 1].y, Points[0].x, Points[0].y, 1);
	//GP142_lineXY(color, Points[0].x, Points[0].y, Points[numOfPoints - 1].x, Points[numOfPoints - 1].y, 1);
}

bool polygon::contains(point p)
{
	/*
	point max = { 493, p.y };
	int count = 0, i = 0;

	do
	{
		int next_point = (i + 1) % numOfPoints;
		if (intersects(Points[i].x, Points[i].y, Points[next_point].x, Points[next_point].y, p.x, p.y, max.x, max.y))
		{
			if (orientation(Points[i].x, Points[i].y, p.x, p.y, Points[next_point].x, Points[next_point].y) == 0)
			{
				return point_on_line(Points[i].x, Points[i].y, p.x, p.y, Points[next_point].x, Points[next_point].y);
			}
			count++;
		}
		i = next_point;
	} while (i != 0);

	return (count % 2 == 1);
	*/
	int i, j, nvert = numOfPoints;
	bool c = false;

	for (i = 0, j = nvert - 1; i < nvert; j = i++) {
		if (((Points[i].y >= p.y) != (Points[j].y >= p.y)) &&
			(p.x <= (Points[j].x - Points[i].x) * (p.y - Points[i].y) / (Points[j].y - Points[i].y) + Points[i].x)
			)
			c = !c;
	}
	return c;
}

void polygon::fill(int clr)
{

}

void polygon::serialize(ostream &fname)
{
	
	fname << endl << "polygon" << endl;
	fname << numOfPoints ;
	fname.write((char*)&color, sizeof(color));

	for (int i = 0; i < numOfPoints; i++)
	{
		fname.write((char*)&Points[i], sizeof(Points[i]));
	}
}

void polygon::deserialize(string &filename, istream &in)
{
	int buff ;
	in >> buff;
	Points = new point[buff];
	numOfPoints = buff;
	in.read((char*)&color, sizeof(color));

	for (int i = 0; i < numOfPoints; i++)
	{
		in.read((char*)&Points[i], sizeof(Points[i]));
	}
}