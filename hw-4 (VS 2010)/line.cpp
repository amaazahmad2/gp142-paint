#include "line.h"
#include<cmath>
#include<fstream>

void drawDottedLine(int clr, int x1, int y1, int x2, int y2)
{

		if (x1 > x2)
		{
			int temp = x2;
			x2 = x1;
			x1 = temp;

			temp = y2;
			y2 = y1;
			y1 = temp;
		}
		

		int dy = y2 - y1;
		int dx = x2 - x1;
		for (int x = x1,y; x <= x2; x=x+3)
		{
			y = y1 + dy * (x - x1) / dx;
			GP142_pixelXY(clr, x, y);
		}
}

line::line()
{
}

line::line(int clr, bool stl, int mouse_x, int mouse_y)
	:openShape(stl)
{
	Points = new point[2];
	point p;
	char key_pressed = 0;;
	color = clr;
	numOfPoints = 2;
	Points[0].x = mouse_x;
	Points[0].y = mouse_y;

	mouse_x = -701;
	mouse_y = -296;
	while ((mouse_x < -700 || mouse_y < -295) && key_pressed == 0)
	{

		GP142_await_event(&mouse_x, &mouse_y, &key_pressed);
		if (key_pressed != 0)
		{
			key_pressed = 0;
			mouse_x = -701;
			mouse_y = -296;
		}

	}
	Points[1].x = mouse_x;
	Points[1].y = mouse_y;
}

line::~line()
{
}

void line::draw()
{
	if (style == 1)
		GP142_lineXY(color, Points[0].x, Points[0].y, Points[1].x, Points[1].y, 1);
	else
		drawDottedLine(color, Points[0].x, Points[0].y, Points[1].x, Points[1].y);
}

void line::changeColor()
{

}

bool line::contains(point p)
{
	int d1 = sqrt(pow(p.x - Points[0].x, 2) + pow(p.y - Points[0].y, 2));
	int d2 = sqrt(pow(p.x - Points[1].x, 2) + pow(p.y - Points[1].y, 2));
	int totalLength = sqrt(pow(Points[0].x - Points[1].x, 2) + pow(Points[0].y - Points[1].y, 2));
	if (d1 + d2 == totalLength)
		return true;
	else
		return false;
}


void line::serialize(ostream &file)
{
	file << "line" << endl;
	file.write((char*)&color, sizeof(color));
	
	file.write((char*)&Points[0], sizeof(Points[0]));
	file.write((char*)&Points[1], sizeof(Points[1]));
	file.write((char*)&style, sizeof(style));
}

void line::deserialize(string &filename, istream &file)
{
	file.read((char*)&color, sizeof(color));
	Points = new point[2];
	file.read((char*)&Points[0], sizeof(Points[0]));
	file.read((char*)&Points[1], sizeof(Points[1]));
	file.read((char*)&style, sizeof(style));
}