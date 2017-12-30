#pragma once
#include "PolygonRim.h"
#include "Typedef.h"

class RectangleRim;

namespace rect
{
	enum RECT_RELATION
	{
		NON_INTERSECT, 
		INTERSECT, 
		IMPLICATE_SUB, 
		IMPLICATE_SUPER, 
		IDENTICAL
	};

	relation_t RectangleRelation(RectangleRim& x, RectangleRim& y);
}

class RectangleRim :
	public PolygonRim
{
public:
	RectangleRim(std::pair<int, int> leftdown, std::pair<int, int> rightup);
	~RectangleRim();

	std::pair<int, int> getCentr() const;
	bool isIn(std::pair<int,int>& point) const
	{
		return point.first >= left && point.first <= right && point.second >= down && point.second <= up;
	}

	static std::vector<std::pair<std::pair<int,int>,std::pair<int,int>>> regularize(std::pair<int, int>& leftdown, std::pair<int, int>& rightup)
	{
		std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> ret;
		std::pair<int, int> leftup(std::pair<int, int>(leftdown.first, rightup.second)),
			rightdown(std::pair<int, int>(rightup.first, leftdown.second));
		ret.push_back(std::pair<std::pair<int, int>, std::pair<int, int>>(leftdown, leftup));
		ret.push_back(std::pair<std::pair<int, int>, std::pair<int, int>>(leftup, rightup));
		ret.push_back(std::pair<std::pair<int, int>, std::pair<int, int>>(rightup, rightdown));
		ret.push_back(std::pair<std::pair<int, int>, std::pair<int, int>>(rightdown, leftdown));
		return ret;
	}

	friend relation_t rect::RectangleRelation(RectangleRim& x, RectangleRim& y);

protected:
	std::pair<int, int> centr;
	int left, right, up, down;
};

