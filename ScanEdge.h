#pragma once
#include "GeometricLine.h"

class ScanEdge
{
public:
	ScanEdge(std::vector<GeometricLine>& Lines);
	~ScanEdge();

	void GenerateOrderedEdgeList();
	void GenerateActiveEdgeList();

private:
	std::vector<GeometricLine> Lines;
	std::vector<std::vector<GeometricLine::ScanBucket>> OrderedEdgeList;
	std::vector<std::vector<GeometricLine::ScanBucket>> ActiveEdgeList;

	int min_y;
};

