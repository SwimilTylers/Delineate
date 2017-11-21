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

protected:
	std::vector<StraightLine> edges;
	std::vector<std::pair<int, int>> vertices;
	std::vector<StraightLine>& compatibility(Window& window);
	bool not_collide(Window& window);

	bool isComplete = false;
	std::vector<std::pair<int, int>> Trajectory;
};

