#include "Graphic.h"



Graphic::Graphic(RectangleRim& uttermost, Outline* Rim, std::vector<float>& RimColor,
	std::vector<std::pair<std::pair<int, int>, std::vector<float>>>& CGenerators): uttermost(uttermost)
{
	this->Rim.profile = Rim;
	this->Rim.color = RimColor;
	this->CGenerators = CGenerators;
}

Graphic::~Graphic()
{
}

std::vector<float> Graphic::getEdgeColor() const
{
	return Rim.color;
}
