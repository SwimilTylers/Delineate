#pragma once
#include "RectangleRim.h"
#include "LineCutAlgorithm.h"
#include "PolygonCutAlgorithm.h"
#include <utility>

class RectangleWindowRim :
	public RectangleRim
{
public:
	RectangleWindowRim(std::pair<int, int>& leftdown, std::pair<int, int>& rightup, LineCutAlgorithm* line_cut_server, PolygonCutAlgorithm* polygon_cut_server);
	~RectangleWindowRim();

	std::pair<std::pair<int, int>, std::pair<int, int>> CutLine(const GeometricLine& line) const;
	std::vector<PolygonRim> PolygonCut(const PolygonRim&) const;

	std::pair<int,int> getHorizontalStartAndEnd() const
	{
		return std::pair<int, int>(left, right);
	}

	std::pair<int, int> getVerticalStartAndEnd() const
	{
		return std::pair<int, int>(down, up);
	}

private:
	LineCutAlgorithm* line_cut_server;
	PolygonCutAlgorithm* polygon_cut_server;
};

