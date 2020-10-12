#pragma once
#include<vector>
using namespace std;

struct point
{
	int x, y;
};

class shape
{
protected:
	int color;
	int numOfPoints;
	point* Points;

public:
	shape();
	shape(int clr, int nop, point* ps);
	shape(int clr, int nop);
	~shape();
	virtual void draw() = 0;
	virtual bool contains(point p) = 0;
	virtual void serialize(ostream &fname) {}
	virtual void deserialize(string &filename, istream &in)=0;

	friend void performAction(int currentShape, int previousColor, int currentColor, int mouse_x, int mouse_y, vector<shape*>&allShapes);
	friend void eraser(point &p, vector<shape*>&allShapes);
};





//point_pushback is for functions in which number of clicks is to be 
//determined by the user. This function creates and manages the Points
// array according to the number of clicks of user.
//It stores the co-ordinates of each click passed to it as a point

void point_pushback(point &p, point *&arr, int &numOfPoints);
