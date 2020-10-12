#include "shape.h"
void point_pushback(point &p, point *&arr, int &numOfPoints)
{
	if (arr == nullptr)
	{
		arr = new point;
		arr->x = p.x;
		arr->y = p.y;
		numOfPoints++;
		return;
	}

	point*temp = new point[numOfPoints + 1];
	for (int i = 0; i < numOfPoints; i++)
	{
		temp[i].x = arr[i].x;
		temp[i].y = arr[i].y;
	}
	temp[numOfPoints].x = p.x;
	temp[numOfPoints].y = p.y;
	delete[]arr;
	arr = temp;
	numOfPoints++;

}


shape::shape()
{
	Points = nullptr;
}


shape::~shape()
{
	delete Points;
}

shape::shape(int clr, int nop, point*ps)
	:color(clr),numOfPoints(nop)
{
	Points = new point[nop];
	for (int i = 0; i < nop; i++) 
	{
		Points[i].x = ps[i].x;
		Points[i].y = ps[i].y;
	}
}

shape::shape(int clr, int nop)
	:color(clr), numOfPoints(nop)
{
	Points = new point[nop];
}

