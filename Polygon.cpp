#include "Polygon.h"
#include <vector>

#define debug_171214_polygon true
#undef debug_171214_polygon

Polygon::Polygon(PolygonRim& profile, std::vector<float>& RimColor,
	std::vector<std::pair<std::pair<int, int>, std::vector<float>>>& CGenerators)
	: Graphic(sketchout(profile), new PolygonRim(profile), RimColor, CGenerators)
	, profile(profile), oel_server(profile.DeployOEL())
{
}

void Polygon::generateCGProfile()
{
	auto OEL = oel_server.get_ordered_edge_list();
	const auto least_y = oel_server.getRangeY().first;

	auto& Profile = CGeneratorProfile;
	std::for_each(OEL.begin(), OEL.end(), [&Profile](std::vector<GeometricLine::ScanBucket>& line)
	{
		std::vector<CGeneratorBarrier*> buf;
		std::for_each(line.begin(), line.end(), [&buf](GeometricLine::ScanBucket& element)
		{
			buf.push_back(new GeometricLine::ScanBucket(element));
		});
		Profile.push_back(buf);
	});

	/*
	for (auto& element : OEL)
	{
		std::vector<CGeneratorBarrier*> buf;
		for (auto& i_element : element)
		{
			buf.push_back(&i_element);
		}
		CGeneratorProfile.push_back(buf);
	}
	*/

	std::vector<CGeneratorBarrier*> buf;
	auto this_y = least_y;
	for (auto& element : CGeneratorProfile)
	{
		element.insert(element.end(), buf.begin(), buf.end());
		std::sort(element.begin(), element.end(), [](CGeneratorBarrier* x, CGeneratorBarrier* y)->bool
		{
			return x->get_x() < y->get_x();
		});
		buf.clear();
#ifndef debug_171214_polygon
		std::for_each(element.begin(), element.end(), [&buf, &this_y](CGeneratorBarrier* i_element)
		{
			auto chk = i_element->getNextBarrier(this_y);
			if (chk != nullptr)	buf.push_back(chk);
		});

#else
		for (auto& i_element : element)
		{
			auto chk = i_element->getNextBarrier(this_y);
			if(chk != nullptr)	buf.push_back(chk);
		}
#endif

		this_y++;
	}
}

RectangleRim& Polygon::sketchout(PolygonRim& profile)
{
	auto vertices = profile.getApexes();
	std::pair<int, int> max, min;
	std::for_each(vertices.begin(), vertices.end(), [&max, &min](std::pair<int,int> element)
	{
		max.first = max.first > element.first ? max.first : element.first;
		max.second = max.second > element.second ? max.second : element.second;

		min.first = min.first < element.first ? min.first : element.first;
		min.first = min.second < element.second ? min.second : element.second;
	});
	return *(new RectangleRim(min, max));
}

Polygon Polygons::getNewPolygon(std::vector<float> edge_color, cgeneratorlist_t cgenerators,
	std::initializer_list<std::pair<int, int>> vertices)
{
	auto&& rim = PolygonRims().getNewRim(vertices);
	return Polygon(rim, edge_color, cgenerators);
}

Polygon::~Polygon()
{
}

