#pragma once
#include "Graphic.h"
#include "PolygonRim.h"

class Polygon :
	public Graphic
{
public:
	Polygon(PolygonRim &profile, const float Red, const float Green, const float Blue);
	~Polygon();
	std::vector<std::pair<int, int>> Vertices(Window& window) override;

private:
	PolygonRim profile;
	std::vector<std::vector<GeometricLine::ScanBucket>> active_edge_list;
	int start_y = 0;
	bool isComplete = false;
	bool is_total_in(Window &window);
	std::vector<StraightLine>& compatible(Window &window);

	std::vector<std::vector<GeometricLine::ScanBucket>>& generate_sorted_edge_list();
	void generate_active_edge_list();

	std::vector<std::pair<int, int>>& fill();
};

