#include "oval.h"
#include<cmath>
#include<fstream>

oval::oval()
{
}

oval::oval (int clr, int nop, point* ps, int fillclr)
	:shape(clr,2,ps),fillColor(fillclr)
{
	
}


oval::oval(int clr, int mouse_x, int mouse_y)
	:shape(clr,2)
{
	char key_pressed=0;
	
		Points[0].x = mouse_x;
		Points[0].y = mouse_y;

		mouse_x = -701; //to enter the loop below
		mouse_y = -296;
		
		while ((mouse_x < -700 || mouse_y < -295) && key_pressed==0)
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

oval::~oval()
{
}

void oval::fill(int clr)
{
	fillColor = clr;
}

void oval::draw()
{
	GP142_ovalXY(color, Points[0].x, Points[0].y, Points[1].x, Points[1].y, 1);
}

bool oval::contains(point p)
{
	int ry = Points[1].y - Points[0].y;
	int rx = Points[1].x - Points[0].x;

	ry = abs(ry / 2);
	rx = abs(rx / 2);

	int midX = (Points[0].x + Points[1].x) / 2;
	int midY = (Points[0].y + Points[1].y) / 2;

	int ans = (pow((p.x - midX), 2) / pow(rx, 2)) + pow((p.y - midY), 2) / pow(ry, 2);
	if (ans <= 1)
		return true;
	else
		return false;


}


void oval::serialize(ostream &file)
{
	file << "oval" << endl;

	file.write((char*)&Points[0], sizeof(Points[0]));
	file.write((char*)&Points[1], sizeof(Points[1]));
	file.write((char*)&fillColor, sizeof(fillColor));
	file.write((char*)&color, sizeof(color));
}

void oval::deserialize(string &filename, istream &in)
{
	Points = new point[2];
	in.read((char*)&Points[0], sizeof(Points[0]));
	in.read((char*)&Points[1], sizeof(Points[1]));
	in.read((char*)&fillColor, sizeof(fillColor));
	in.read((char*)&color, sizeof(color));
}