#include "RectangleRim.h"



RectangleRim::RectangleRim(std::pair<int, int> leftdown, std::pair<int, int> rightup): PolygonRim(regularize(leftdown,rightup))
{
	centr.first = (leftdown.first + rightup.first) / 2;
	centr.second = (leftdown.second + rightup.second) / 2;
}

RectangleRim::~RectangleRim()
{
}

std::pair<int, int> RectangleRim::getCentr() const
{
	return centr;
}
