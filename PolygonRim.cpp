#include "PolygonRim.h"



PolygonRim::PolygonRim(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> vertex_pairs)
{
	std::vector<std::pair<int,GeometricLine::ScanBucket>> sbbuf;
	std::vector<double> gradients;
	for (const auto element : vertex_pairs)
	{
		GeometricLine dscp(element.first, element.second);
		const StraightLine new_edge(dscp);
		edges.push_back(new_edge);
		vertices.push_back(element.first);
		vertices.push_back(element.second);

		sbbuf.push_back(new_edge.getScanBucket());
		gradients.push_back(new_edge.getGradient());
	}
	std::sort(vertices.begin(), vertices.end());
	vertices.erase(std::unique(vertices.begin(), vertices.end()), vertices.end());

	RegularizeOEL(gradients, sbbuf);
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

std::vector<StraightLine> PolygonRim::getEdge() const
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

std::vector<std::vector<GeometricLine::ScanBucket>>& PolygonRim::get_ordered_edge_list()
{
	return ordered_edge_list;
}

void PolygonRim::RegularizeOEL(std::vector<double>& gradients, std::vector<std::pair<int, GeometricLine::ScanBucket>>& sbbuf)
{
	int min_y(0x7FFFFFFF), max_y(0);
	std::for_each(sbbuf.begin(),sbbuf.end(), [&min_y, &max_y](std::pair<int,GeometricLine::ScanBucket>& x)
	{
		min_y = x.first < min_y ? x.first : min_y;
		max_y = x.second.get_max_y() > max_y ? x.second.get_max_y() : max_y;
	});

	ordered_edge_list.resize(max_y - min_y + 1);

	for (int i = 1; i < ordered_edge_list.size(); ++i)
	{
		const int rela_y = sbbuf[i].first - min_y;
		auto buf = sbbuf[i].second;
		if (!((gradients[i - 1] * gradients[i]) > 0))
		{
			const auto bufptr = buf.updata(rela_y + 1);
			if(bufptr != nullptr)
			{
				ordered_edge_list[rela_y + 1].push_back(*bufptr);
			}
		}
		else
		{
			ordered_edge_list[rela_y].push_back(buf);
		}
	}
	std::for_each(ordered_edge_list.begin(), ordered_edge_list.end(), 
		[](std::vector<GeometricLine::ScanBucket> &element) {std::sort(element.begin(), element.end()); });
	RangeY.first = min_y;
	RangeY.second = max_y;
}
