#include "PolygonRim.h"



PolygonRim::PolygonRim(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> vertex_pairs)
{
	for (const auto element : vertex_pairs)
	{
		GeometricLine dscp(element.first, element.second);
		const StraightLine new_edge(dscp);
		edges.push_back(new_edge);
		vertices.push_back(element.first);
		vertices.push_back(element.second);
	}
	std::sort(vertices.begin(), vertices.end());
	vertices.erase(std::unique(vertices.begin(), vertices.end()), vertices.end());
}

PolygonRim::~PolygonRim()
{
}

std::vector<std::pair<int, int>> PolygonRim::Vertices(Window& window_now)
{
	if(not_collide(window_now) && isComplete)
	{
		return Trajectory;
	}
	else
	{
		Trajectory.clear();
		const auto compatible_outlines = compatibility(window_now);
		for (auto element : compatible_outlines)
		{
			auto buf = element.Vertices(window_now);
			Trajectory.insert(Trajectory.end(), buf.begin(), buf.end());
		}
		isComplete = true;
		return Trajectory;
	}
}

std::vector<Outline> PolygonRim::getEdge() const
{
	auto ret = edges;
	return ret;
}

std::vector<StraightLine>& PolygonRim::compatibility(Window& window)
{
	return edges;
}

bool PolygonRim::not_collide(Window& window)
{
	return true;
}
