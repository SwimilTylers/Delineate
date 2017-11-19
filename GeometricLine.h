#pragma once
#include <utility>
#include "Window.h"

class GeometricLine
{
public:
	GeometricLine(std::pair<int, int> point_1, std::pair<int, int> point_2);
	~GeometricLine();

	double getGradient() const;
	std::pair<int, int> get_deltas() const;
	std::pair<std::pair<int, int>, std::pair<int, int>> get_vertices();
	GeometricLine *compatibility(Window& window);

private:
	std::pair<int, int> deltas;
	std::pair<int, int> start, end;
	double gradient;
};

