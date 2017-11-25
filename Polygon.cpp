#include "Polygon.h"



Polygon::Polygon(PolygonRim &profile, const float Red, const float Green, const float Blue)
	: Graphic(profile.getEdge(), Red, Green, Blue), profile(profile)
{
}


Polygon::~Polygon()
{
}

std::vector<std::pair<int, int>> Polygon::Vertices(Window& window)
{
	if(!is_total_in(window))
	{
		
	}
	return fill();
}

bool Polygon::is_total_in(Window &window)
{
	return true;
}

std::vector<StraightLine>& Polygon::compatible(Window &window)
{
	return outlines_surround;
}

std::vector<std::vector<GeometricLine::ScanBucket>>& Polygon::generate_sorted_edge_list()
{
}

void Polygon::generate_active_edge_list()
{
	
}

std::vector<std::pair<int, int>>& Polygon::fill()
{
	std::vector<std::pair<int, int>> ret;
	for (auto element : active_edge_list)
	{
		while(true)
		{
			
		}
	}
	return ret;
}
