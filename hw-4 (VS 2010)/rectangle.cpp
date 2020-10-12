#include "rectangle.h"
#include<fstream>


rectangle::rectangle()
{}


rectangle::rectangle(int clr, int mouse_x, int mouse_y)
{
	color = clr;
	numOfPoints = 0;
	point *p = new point[2];
	point tempPoint;
	char key_pressed = 0;;
	color = clr;
	p[0].x = mouse_x;
	p[0].y = mouse_y;

	mouse_x = -701; //to enter the loop below
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

	p[1].x = mouse_x;
	p[1].y = mouse_y;

	point_pushback(p[0], Points, numOfPoints);
	
	

	tempPoint.y = p[0].y;
	tempPoint.x = p[1].x;


	
	
	point_pushback(tempPoint, Points, numOfPoints);

	point_pushback(p[1], Points, numOfPoints);


	tempPoint.x = p[0].x;
	tempPoint.y = p[1].y;

	
	point_pushback(tempPoint, Points, numOfPoints);



	fillColor = -1;
}


rectangle::~rectangle()
{
}

void rectangle::draw()
{
	polygon::draw();
}

void rectangle::fill(int clr)
{

}

bool rectangle::contains(point p)
{
	int maxX, maxY, minX, minY;

	if (Points[0].x > Points[2].x)
	{
		maxX = Points[0].x;
		minX = Points[2].x;
	}
	else
	{
		maxX = Points[2].x;
		minX = Points[0].x;
	}

	if (Points[0].y > Points[2].y)
	{
		maxY = Points[0].y;
		minY = Points[2].y;
	}
	else
	{
		maxY = Points[2].y;
		minY = Points[0].y;
	}

	if (p.x > maxX || p.x <minX || p.y > maxY || p.y < minY)
		return false;
	else
		return true;
}


void rectangle::serialize(ostream &fname)
{
	fname << "rectangle" << endl;
	fname.write((char*)&Points[0], sizeof(Points[0]));
	fname.write((char*)&Points[1], sizeof(Points[1]));
	fname.write((char*)&Points[2], sizeof(Points[2]));
	fname.write((char*)&Points[3], sizeof(Points[3]));
	fname.write((char*)&color, sizeof(color));
}

void rectangle::deserialize(string &filename, istream &in)
{
	Points = new point[4];
	numOfPoints = 4;
	in.read((char*)&Points[0], sizeof(Points[0]));
	in.read((char*)&Points[1], sizeof(Points[1]));
	in.read((char*)&Points[2], sizeof(Points[2]));
	in.read((char*)&Points[3], sizeof(Points[3]));
	in.read((char*)&color, sizeof(color));
}