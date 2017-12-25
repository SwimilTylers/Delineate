#pragma once
#include <vector>
#include <utility>

class GeometricLine;
class RectangleWindowRim;

class LineCutAlgorithm
{
public:
	LineCutAlgorithm();
	virtual ~LineCutAlgorithm();

	std::pair<std::pair<int, int>, std::pair<int, int>> operator()(const GeometricLine& line, const RectangleWindowRim& window)
	{
		return LineCutKernel(line, window);
	}

	virtual std::pair<std::pair<int, int>, std::pair<int, int>> LineCutKernel(const GeometricLine& line, const RectangleWindowRim& window) = 0;
};

