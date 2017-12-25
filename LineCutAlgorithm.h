#pragma once
#include <vector>
#include <utility>
#include "RectangleRim.h"

class GeometricLine;

class LineCutAlgorithm
{
public:
	LineCutAlgorithm();
	virtual ~LineCutAlgorithm();

	std::pair<std::pair<int, int>, std::pair<int, int>> operator()(const GeometricLine& line, const RectangleRim& window)
	{
		return LineCutKernel(line, window);
	}

	virtual std::pair<std::pair<int, int>, std::pair<int, int>> LineCutKernel(const GeometricLine& line, const RectangleRim& window) = 0;
};

