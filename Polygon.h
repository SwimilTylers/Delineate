#pragma once
#include "Graphic.h"
#include "PolygonRim.h"
#include "Typedef.h"

class Polygon :
	public Graphic
{
public:
	Polygon(PolygonRim &profile, std::vector<float>& RimColor, 
		std::vector<std::pair<std::pair<int, int>, std::vector<float>>>& CGenerators);
	~Polygon();

	std::pair<int, int>& getRangeY() override
	{
		return oel_server.getRangeY();
	}

protected:
	void generateCGProfile() override;
private:
	PolygonRim profile;
	PolygonRim::OELServer oel_server;

	static RectangleRim& sketchout(PolygonRim& profile);
};

class Polygons
{
public:
	static Polygon getNewPolygon(std::vector<float> edge_color, cgeneratorlist_t cgenerators, std::initializer_list<std::pair<int, int>> vertices);
};

