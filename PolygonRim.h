#pragma once
#include "Outline.h"
#include "StraightLine.h"

class PolygonRim :
	public Outline
{
public:
	explicit PolygonRim(std::vector<std::pair<std::pair<int,int>,std::pair<int,int>>> vertex_pairs);
	virtual ~PolygonRim();
	std::vector<std::pair<int, int>> Vertices(Window& window_now) override;
	std::vector<StraightLine> getEdge() const;

	std::vector<std::vector<GeometricLine::ScanBucket>>& get_ordered_edge_list();
	std::pair<int,int>& getRangeY()
	{
		return RangeY;
	}

protected:
	std::vector<StraightLine> edges;
	std::vector<std::pair<int, int>> vertices;
	std::vector<StraightLine>& compatibility(Window& window);
	bool not_collide(Window& window);

	bool isComplete = false;
	std::vector<std::pair<int, int>> Trajectory;

	std::vector<std::vector<GeometricLine::ScanBucket>> ordered_edge_list;
	std::pair<int, int> RangeY;

	void RegularizeOEL(std::vector<double>& gradients, std::vector<std::pair<int, GeometricLine::ScanBucket>>& sbbuf);
};

