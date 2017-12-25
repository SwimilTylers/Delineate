#pragma once
#include "PolygonCutAlgorithm.h"
class Weiler_Atherton_Algorithm :
	public PolygonCutAlgorithm
{
public:
	Weiler_Atherton_Algorithm();
	~Weiler_Atherton_Algorithm();
	std::vector<PolygonRim> PolygonCutKernel(const PolygonRim& line,
		const RectangleWindowRim& window) const override;
};

