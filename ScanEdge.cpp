#include "ScanEdge.h"
#include <algorithm>


ScanEdge::ScanEdge(std::vector<GeometricLine>& Lines)
{
	int max(0), min(0x7fffffff);
	std::for_each(Lines.begin(), Lines.end(), [&max, &min](GeometricLine& line)
	{
		int now = line.scan_bucket_start_y();
		max = max > now ? max : now;
		min = min < now ? min : now;
	});
	OrderedEdgeList.resize(max - min + 1);
	ActiveEdgeList.resize(max - min + 1);
	min_y = min;

	
}


ScanEdge::~ScanEdge()
{
}

void ScanEdge::GenerateOrderedEdgeList()
{
	for (auto element : Lines)
	{
		OrderedEdgeList[element.scan_bucket_start_y() - min_y].push_back(element.scan_bucket());
	}

	for (auto element : OrderedEdgeList)
	{
		std::sort(element.begin(), element.end());
	}
}

void ScanEdge::GenerateActiveEdgeList()
{
}
