#include "circle.h"
#include<fstream>


circle::circle()
{
	numOfPoints = 1;
}

circle::circle(int clr, int nop, point* ps, int fillclr, double rad)
	:shape(clr,nop,ps),fillColor(fillclr),radius(rad)
{
}

circle::circle(int clr, int mouse_x, int mouse_y)
	: shape(clr, 1)
{
	
	char key_pressed;
	Points->x = mouse_x;
	Points->y = mouse_y;
	if (GP142_await_event(&mouse_x, &mouse_y, &key_pressed) == GP142_MOUSE)
	{
		point p2; p2.x = mouse_x; p2.y = mouse_y;
		radius = sqrt(pow(p2.x - Points->x, 2) + pow(p2.y - Points->y, 2));

		point_pushback(p2, Points, numOfPoints);
	}
	
	numOfPoints = 2;
	
}

circle::~circle()
{
}

void circle::fill(int clr)
{
	fillColor = clr;
	GP142_circleXY(clr, Points[0].x, Points[0].y, radius-1);
}

void circle::draw()
{
	int x, y;
	for (int xValues = Points->x; xValues <= Points->x + radius; xValues++)
	{
		if (xValues < -700)
			continue;
		y = Points->y + sqrt(pow(radius, 2) - pow((xValues - Points->x), 2));
		if (y < -295)
			continue;
		GP142_pixelXY(color, xValues, y);
		y = Points->y - sqrt(pow(radius, 2) - pow((xValues - Points->x), 2));
		if (y < -295)
			continue;
		GP142_pixelXY(color, xValues, y);

	}

	for (int xValues = Points->x; xValues >= Points->x - radius; xValues--)
	{
		if (xValues < -700)
			continue;
		y = Points->y + sqrt(pow(radius, 2) - pow((xValues - Points->x), 2));
		if (y < -295)
			continue;
		GP142_pixelXY(color, xValues, y);
		y = Points->y - sqrt(pow(radius, 2) - pow((xValues - Points->x), 2));
		if (y < -295)
			continue;
		GP142_pixelXY(color, xValues, y);

	}

	for (int yValues = Points->y; yValues <= Points->y + radius; yValues++)
	{
		if(yValues < -295)
			continue;
		x = Points->x + sqrt(pow(radius, 2) - pow((yValues - Points->y), 2));
		if (x < -700)
			continue;
		GP142_pixelXY(color, x, yValues);

		x = Points->x - sqrt(pow(radius, 2) - pow((yValues - Points->y), 2));
		if (x < -700)
			continue;
		GP142_pixelXY(color, x, yValues);
	}

	for (int yValues = Points->y; yValues >= Points->y - radius; yValues--)
	{
		if (yValues < -295)
			continue;
		x = Points->x + sqrt(pow(radius, 2) - pow((yValues - Points->y), 2));
		if (x < -700)
			continue;
		GP142_pixelXY(color, x, yValues);
		x = Points->x - sqrt(pow(radius, 2) - pow((yValues - Points->y), 2));
		if (x < -700)
			continue;
		GP142_pixelXY(color, x, yValues);
	}
}

bool circle::contains(point p)
{
	int d = sqrt(pow(p.x - Points->x, 2) + pow(p.y - Points->y, 2));
	if (d > radius)
		return false;
	else
		return true;
}

void circle::serialize(ostream& file)
{
	
	file << "circle" << endl;

	file.write((char*)&color, sizeof(color));
	file.write((char*)&radius, sizeof(radius));
	file.write((char*)&Points[0], sizeof(Points[0]));
	file.write((char*)&Points[1], sizeof(Points[1]));
	file.write((char*)&fillColor, sizeof(fillColor));

}

void circle::deserialize(string &filename, istream &in)
{
	in.read((char*)&color, sizeof(color));
	in.read((char*)&radius, sizeof(radius));
	Points = new point[2];
	numOfPoints = 2;
	in.read((char*)&Points[0], sizeof(Points[0]));
	in.read((char*)&Points[1], sizeof(Points[1]));
	in.read((char*)&fillColor, sizeof(fillColor));
}