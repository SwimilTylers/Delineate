#include "Polygon.h"
#include <valarray>


Polygon::Polygon(RectangleRim& uttermost, PolygonRim& profile, std::vector<float>& RimColor,
	std::vector<std::pair<std::pair<int, int>, std::vector<float>>>& CGenerators)
	: Graphic(uttermost, new PolygonRim(profile), RimColor, CGenerators), profile(profile)
{
}

void Polygon::generateCGProfile()
{
	auto OEL = profile.get_ordered_edge_list();
	const auto least_y = profile.getRangeY().first;

	for (auto element : OEL)
	{
		std::vector<CGeneratorBarrier*> buf;
		for (auto i_element : element)
		{
			buf.push_back(&i_element);
		}
		CGeneratorProfile.push_back(buf);
	}

	std::vector<CGeneratorBarrier*> buf;
	auto this_y = least_y;
	for (auto element : CGeneratorProfile)
	{
		element.insert(element.end(), buf.begin(), buf.end());
		buf.clear();
		for (auto i_element : element)
		{
			auto chk = i_element->Update(this_y);
			if(chk != nullptr)	buf.push_back(chk);
		}
		this_y++;
	}
}

Polygon::~Polygon()
{
}

