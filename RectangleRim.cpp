#include "RectangleRim.h"



RectangleRim::RectangleRim(std::pair<int, int> leftdown, std::pair<int, int> rightup): PolygonRim(regularize(leftdown,rightup))
{
}

RectangleRim::~RectangleRim()
{
}
