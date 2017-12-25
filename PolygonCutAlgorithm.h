#pragma once
#include <utility>
#include "RectangleRim.h"
class PolygonRim;

class PolygonCutAlgorithm
{
public:
	PolygonCutAlgorithm();
	virtual ~PolygonCutAlgorithm();

	std::vector<PolygonRim> operator()(const PolygonRim& line, const RectangleRim& window) const
	{
		return PolygonCutKernel(line, window);
	}

	virtual std::vector<PolygonRim> PolygonCutKernel(const PolygonRim& line, const RectangleRim& window) const = 0;
};

