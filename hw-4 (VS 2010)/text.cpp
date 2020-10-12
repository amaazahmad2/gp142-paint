#pragma once
#include "text.h"
#include<fstream>

int lengthOnScreen(char*arr, int size)
{
	int count = 0;
	for (int i = 0; i < strlen(arr); i++)
	{
		if (arr[i] > 'A'-1 && arr[i] < 'Z'+1)
		{
			count++;
		}
	}

	return (strlen(arr)*size/2 )  +(count * size/4);
	
}


text::text()
	:shape(1,1),size(10)
{
	str = nullptr;
}

text::text(char*s, int clr, int si)
	:shape(clr,1),size(si)
{
	str = new char[strlen(s) + 1];
	strcpy(str, s);
}

text::text(int clr, int mouse_x, int mouse_y)
	:shape(clr,1)
{
	char*tempStr = new char[100000];
	GP142_gets("ENTER THE STRING TO BE PRINTED", tempStr);
	str = new char[strlen(tempStr) + 1];
	strcpy(str, tempStr);
	GP142_gets("ENTER THE FONT SIZE", tempStr);
	size = atoi(tempStr);
	delete[] tempStr;

	Points->x = mouse_x;
	Points->y = mouse_y;

}

text::~text()
{
	delete[] str;
}

void text::changeColor(int clr)
{
	color = clr;
	GP142_printfXY(color, Points->x, Points->y, 10, str);
}

void text::draw()
{

	//int len = lengthOnScreen(str, size);
	GP142_printfXY(color, Points->x, Points->y, size, str);
	//GP142_rectangleXY(color, Points->x, Points->y, Points->x +len, Points->y + size, 1);
	
}

void text::changeSize(int s)
{
	size =s;
}

bool text::contains(point p)
{
	int len = lengthOnScreen(str, size);
	if (p.x < Points->x || p.x > Points->x + len || p.y < Points->y || p.y > Points->y + size)
	{
		return false;
	}
	return true;
}

void text::serialize(ostream &fname)
{
	fname << "text" << endl;
	fname << str << endl;
	fname.write((char*)&Points[0], sizeof(Points[0]));
	fname.write((char*)&color, sizeof(color));
	fname.write((char*)&size, sizeof(size));
}

void text::deserialize(string &filename, istream &in)
{
	char buff[500];
	numOfPoints = 1;
	in.getline(buff, 500);
	str = new char[strlen(buff) + 1];
	strcpy(str, buff);
	Points = new point;
	in.read((char*)&Points[0], sizeof(Points[0]));
	in.read((char*)&color, sizeof(color));
	in.read((char*)&size, sizeof(size));
}

