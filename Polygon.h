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

	std::pair<int, int>& getRangeY() override
	{
		return oel_server.getRangeY();
	}
	PolygonRim getProfile() const
	{
		return profile;
	}

	virtual const PolygonRim& getAccessToRim() const override;

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
	static Polygon getNewPolygon(std::vector<float> edge_color, cgeneratorlist_t cgenerators, std::vector<std::pair<int, int>> vertices);
	static Polygon getNewPolygon(std::vector<float> edge_color, cgeneratorlist_t cgenerators, std::initializer_list<std::pair<int, int>> vertices);
	static Polygon getRelocatedNewPolygon(Polygon& old_polygon, std::pair<int, int> new_centr);
	static Polygon getScaledNewPolygon(Polygon& old_polygen, std::pair<double, double> ratio);
	static Polygon getRotatedNewPolygon(Polygon& old_polygon, double rad);
	static Polygon getManipulatedNewPolygon(Polygon& old_polygon, std::pair<int, int> disp, std::pair<double, double> ratio, double rad);
	static Polygon getCutNewPolygon(Polygon& old_polygon, RectangleRim& cutRim);
};

