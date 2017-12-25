#pragma once
#include <utility>
#include "RectangleRim.h"

class RectangleWindowRim;
class PolygonRim;

class PolygonCutAlgorithm
{
public:
	PolygonCutAlgorithm();
	virtual ~PolygonCutAlgorithm();

	std::vector<PolygonRim> operator()(const PolygonRim& line, const RectangleWindowRim& window) const
	{
		return PolygonCutKernel(line, window);
	}

	virtual std::vector<PolygonRim> PolygonCutKernel(const PolygonRim& line, const RectangleWindowRim& window) const = 0;
};

