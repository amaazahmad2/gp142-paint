#include "openShape.h"

//Points array is NOT created in the constructor of 'shape' because
//the number of vertexes are to be determined by the clicks of the user.


//point_pushback creates and manages the Points array in the constructor
//according to the number of clicks of user


openShape::openShape()
{
}

openShape::openShape(bool stl)  
	:style(stl)
{}



openShape::~openShape()
{
}
