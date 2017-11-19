#include "GeometricLine.h"



GeometricLine::GeometricLine(const std::pair<int, int> point_1, const std::pair<int, int> point_2)
{
	start = point_1;
	end = point_2;
	deltas = std::pair<int, int>(point_1.first - point_2.first, point_1.second - point_2.second);
	gradient = double(deltas.second) / deltas.first;
}


GeometricLine::~GeometricLine()
{
}

double GeometricLine::getGradient() const
{
	return gradient;
}

std::pair<int, int> GeometricLine::get_deltas() const
{
	return deltas;
}

std::pair<std::pair<int, int>, std::pair<int, int>> GeometricLine::get_vertices()
{
	return std::pair<std::pair<int, int>, std::pair<int, int>>(start, end);
}

GeometricLine* GeometricLine::compatibility(Window& window)
{
	return new GeometricLine(*this);
}
