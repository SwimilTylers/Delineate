#pragma once
#include "LineCutAlgorithm.h"
#include <deque>
#include "PolygonRim.h"
#include "Typedef.h"


struct Liang_Barsky_Algorithm_Record;

class Liang_Barsky_Algorithm :
	public LineCutAlgorithm
{
public:
	Liang_Barsky_Algorithm();
	~Liang_Barsky_Algorithm();
	std::pair<std::pair<int, int>, std::pair<int, int>> LineCutKernel(const GeometricLine& line, const RectangleWindowRim& window) override;

	void LineCutIOMark(const PolygonRim& Cut, std::deque<std::pair<crosspoint_t, std::pair<int, int>>>& Cutv,
		const RectangleWindowRim& Win, std::deque<std::pair<crosspoint_t, std::pair<int, int>>>& Winv);

private:
	std::vector<Liang_Barsky_Algorithm_Record> logserver;
};

namespace rect {
	enum CROSSPOINT { NOTCROSSPOINT, IN, OUT, ET_CETERA};
}
