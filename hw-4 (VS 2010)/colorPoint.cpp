#include "colorPoint.h"
#include"GP142.H"
#include"GP142LIB.H"
#include<fstream>
using namespace std;

void fillColorForColorPoint(int x, int y ,int currentAppliedColor, int currentSelectedColor)
{
	

	if (currentSelectedColor == currentAppliedColor)
		return;
	else if (currentAppliedColor != getPixelColor(x, y))
		return;
	else if (x < -698)
		return;
	else if (y < -293)
		return;

	GP142_pixelXY(currentSelectedColor, x, y);
	//GP142_flush();

	fillColorForColorPoint(x + 1, y,currentAppliedColor, currentSelectedColor);
	//GP142_flush();
	fillColorForColorPoint(x - 1, y,currentAppliedColor,  currentSelectedColor);
	//GP142_flush();
	fillColorForColorPoint(x, y + 1, currentAppliedColor, currentSelectedColor);
	//GP142_flush();
	fillColorForColorPoint(x, y - 1,currentAppliedColor, currentSelectedColor);

}






colorPoint::colorPoint()
{
}


colorPoint::colorPoint(int xp, int yp, int clr)
{
	x = xp;
	y = yp;
	color = clr;
}

void colorPoint::draw()
{
	int currentAppliedColor = getPixelColor(x, y);;
	fillColorForColorPoint(x, y, currentAppliedColor, color);
}

bool colorPoint::contains(point p)
{
	return false;
}

void colorPoint::serialize(ostream &file)
{
	file << "colorpoint" << endl;

	file.write((char*)&color, sizeof(color));
	file.write((char*)&x, sizeof(x));
	file.write((char*)&y, sizeof(y));
}


void colorPoint::deserialize(string &filename, istream &file)
{
	
	file.read((char*)&color, sizeof(color));
	file.read((char*)&x, sizeof(x));
	file.read((char*)&y, sizeof(y));
}


colorPoint::~colorPoint()
{
}
