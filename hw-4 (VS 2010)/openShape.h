#pragma once
#include "shape.h"
class openShape : public shape
{
protected:
	bool style;
public:
	openShape();
	openShape(bool stl);
	~openShape();
	virtual void changeColor() = 0;
};

