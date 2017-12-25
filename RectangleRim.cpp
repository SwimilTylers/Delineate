#include "RectangleRim.h"


RectangleRim::RectangleRim(std::pair<int, int> leftdown, std::pair<int, int> rightup): PolygonRim(regularize(leftdown,rightup))
{
	centr.first = (leftdown.first + rightup.first) / 2;
	centr.second = (leftdown.second + rightup.second) / 2;

	left = leftdown.first < rightup.first ? leftdown.first : rightup.first;
	right = leftdown.first > rightup.first ? leftdown.first : rightup.first;
	up = leftdown.second > rightup.second ? leftdown.second : rightup.second;
	down = leftdown.second < rightup.second ? leftdown.second : rightup.second;
}

RectangleRim::~RectangleRim()
{
}

std::pair<int, int> RectangleRim::getCentr() const
{
	return centr;
}

relation_t rect::RectangleRelation(RectangleRim& x, RectangleRim& y)
{
	if (x.left > y.right || x.right < y.left || x.up<y.down || x.down>y.up)
		return rect::NON_INTERSECT;
	if (x.left == y.left&&x.right == y.right&&x.up == y.up&&x.down == y.down)
		return rect::IDENTICAL;
	if (x.left > y.left&&x.right < y.right&&x.up < y.up&&x.down > y.down)
		return rect::IMPLICATE_SUB;
	if (x.left < y.left&&x.right > y.right&&x.up > y.up&&x.down < y.down)
		return rect::IMPLICATE_SUPER;
	return rect::INTERSECT;
}
