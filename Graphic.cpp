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
	std::for_each(CGeneratorProfile.begin(), CGeneratorProfile.end(), [](std::vector<CGeneratorBarrier*>& line)
	{
		std::for_each(line.begin(),line.end(), [](CGeneratorBarrier* element)
		{
			delete element;
		});
	});
}

std::vector<float> Graphic::getEdgeColor() const
{
	return Rim.color;
}
