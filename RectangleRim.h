#pragma once
#include "PolygonRim.h"
class RectangleRim :
	public PolygonRim
{
public:
	RectangleRim(std::pair<int, int> leftdown, std::pair<int, int> rightup);
	~RectangleRim();

	static std::vector<std::pair<std::pair<int,int>,std::pair<int,int>>> regularize(std::pair<int, int>& leftdown, std::pair<int, int>& rightup)
	{
		std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> ret;
		std::pair<int, int> leftup(std::pair<int, int>(leftdown.first, rightup.second)),
			rightdown(std::pair<int, int>(rightup.first, leftdown.second));
		ret.push_back(std::pair<std::pair<int, int>, std::pair<int, int>>(leftdown, leftup));
		ret.push_back(std::pair<std::pair<int, int>, std::pair<int, int>>(rightup, leftup));
		ret.push_back(std::pair<std::pair<int, int>, std::pair<int, int>>(rightup, rightdown));
		ret.push_back(std::pair<std::pair<int, int>, std::pair<int, int>>(leftdown, rightdown));
		return ret;
	}
};

