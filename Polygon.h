#pragma once
#include "Graphic.h"
#include "PolygonRim.h"

class Polygon :
	public Graphic
{
public:
	Polygon(RectangleRim& uttermost, PolygonRim &profile, std::vector<float>& RimColor, 
		std::vector<std::pair<std::pair<int, int>, std::vector<float>>>& CGenerators);
	~Polygon();

protected:
	void generateCGProfile() override;
private:
	PolygonRim profile;
};

