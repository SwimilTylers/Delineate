#include "Graphic.h"



Graphic::Graphic()
{
}


Graphic::~Graphic()
{
}

float* Graphic::getColor()
{
	float* ret = new float[3];
	ret[0] = color[0];
	ret[1] = color[1];
	ret[2] = color[2];
	return ret;
}

void Graphic::setColor(const float Red, const float Green, const float Blue)
{
	color[0] = Red;
	color[1] = Green;
	color[2] = Blue;
}
