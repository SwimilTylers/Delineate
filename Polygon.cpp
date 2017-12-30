#include "Polygon.h"
#include <vector>
#include "Matrix.h"
#include "RectangleWindowRim.h"

#define debug_171214_polygon true
//#undef debug_171214_polygon
#define debug_polygon_171215 true
#undef debug_polygon_171215

Polygon::Polygon(PolygonRim& profile, std::vector<float>& RimColor,
	std::vector<std::pair<std::pair<int, int>, std::vector<float>>>& CGenerators)
	: Graphic(sketchout(profile), new PolygonRim(profile), RimColor, CGenerators)
	, profile(profile), oel_server(profile.DeployOEL())
{
}

const PolygonRim& Polygon::getAccessToRim() const
{
	return *static_cast<const PolygonRim*>(Rim.profile);
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
	std::pair<int, int> max(0x80000000,0x80000000), min(0x7fffffff, 0x7fffffff);
	std::for_each(vertices.begin(), vertices.end(), [&max, &min](std::pair<int,int> element)
	{
		max.first = max.first > element.first ? max.first : element.first;
		max.second = max.second > element.second ? max.second : element.second;

		min.first = min.first < element.first ? min.first : element.first;
		min.second = min.second < element.second ? min.second : element.second;
	});
	return *(new RectangleRim(min, max));
}

Polygon Polygons::getNewPolygon(std::vector<float> edge_color, cgeneratorlist_t cgenerators,
	std::vector<std::pair<int, int>> vertices)
{
	auto&& rim = PolygonRims().getNewRim(vertices);
	return Polygon(rim, edge_color, cgenerators);
}

Polygon Polygons::getNewPolygon(std::vector<float> edge_color, cgeneratorlist_t cgenerators,
	std::initializer_list<std::pair<int, int>> vertices)
{
	auto&& rim = PolygonRims().getNewRim(vertices);
	return Polygon(rim, edge_color, cgenerators);
}

Polygon Polygons::getRelocatedNewPolygon(Polygon& old_polygon, const std::pair<int, int> new_centr)
{
	const auto old_centr = old_polygon.getUttermost().getCentr();
	auto&& matrix = mtx::relocate(std::pair<int,int>(new_centr.first - old_centr.first, new_centr.second - old_centr.second));
	
	// std::cout << matrix.toString();
	
	auto&& vertices = old_polygon.getProfile().getApexes();
#ifndef debug_polygon_171215
	std::for_each(vertices.begin(), vertices.end(), [& matrix](std::pair<int,int>& point)
	{
		point = (matrix * point).coordinate();
	});
#else
	for (auto && vertex : vertices)
	{
		vertex = (matrix * vertex).coordinate();
	}
#endif
	auto cgenerators = old_polygon.getCGenerators();

	std::for_each(cgenerators.begin(), cgenerators.end(), [&matrix](std::pair<std::pair<int, int>, pencolor_t>& cgenerator)
	{
		cgenerator.first = (matrix * cgenerator.first).coordinate();
	});

	return getNewPolygon(old_polygon.getEdgeColor(), cgenerators, vertices);
}

Polygon Polygons::getScaledNewPolygon(Polygon& old_polygon, const std::pair<double,double> ratio)
{
	const auto old_centr = old_polygon.getUttermost().getCentr();
	auto&& matrix = mtx::relocate(std::pair<int, int>(old_centr.first, old_centr.second))
		* (mtx::scale(ratio)
		* mtx::relocate(std::pair<int, int>(-old_centr.first, -old_centr.second)));
	auto&& vertices = old_polygon.getProfile().getApexes();
	std::for_each(vertices.begin(), vertices.end(), [&matrix](std::pair<int, int>& point)
	{
		point = (matrix * point).coordinate();
	});
	auto cgenerators = old_polygon.getCGenerators();

	std::for_each(cgenerators.begin(), cgenerators.end(), [&matrix](std::pair<std::pair<int, int>, pencolor_t>& cgenerator)
	{
		cgenerator.first = (matrix * cgenerator.first).coordinate();
	});

	return getNewPolygon(old_polygon.getEdgeColor(), cgenerators, vertices);
}

Polygon Polygons::getRotatedNewPolygon(Polygon& old_polygon, const double rad)
{
	const auto old_centr = old_polygon.getUttermost().getCentr();
	auto&& matrix = mtx::relocate(std::pair<int, int>(old_centr.first, old_centr.second))
		* (mtx::rotate(rad)
		* mtx::relocate(std::pair<int, int>(-old_centr.first, -old_centr.second)));
	auto&& vertices = old_polygon.getProfile().getApexes();

//	std::cout << matrix.toString();

	std::for_each(vertices.begin(), vertices.end(), [&matrix](std::pair<int, int>& point)
	{
		point = (matrix * point).coordinate();
	});
	auto cgenerators = old_polygon.getCGenerators();

	std::for_each(cgenerators.begin(), cgenerators.end(), [&matrix](std::pair<std::pair<int, int>, pencolor_t>& cgenerator)
	{
		cgenerator.first = (matrix * cgenerator.first).coordinate();
	});

	return getNewPolygon(old_polygon.getEdgeColor(), cgenerators, vertices);
}

Polygon Polygons::getManipulatedNewPolygon(Polygon& old_polygon, const std::pair<int, int> disp,
                                           const std::pair<double, double> ratio, const double rad)
{
	const auto old_centr = old_polygon.getUttermost().getCentr();
	auto&& matrix = mtx::relocate(std::pair<int, int>(old_centr.first + disp.first, old_centr.second + disp.second))
		* mtx::rotate(rad) * mtx::scale(ratio)
			* mtx::relocate(std::pair<int, int>(-old_centr.first, -old_centr.second));
	auto&& vertices = old_polygon.getProfile().getApexes();
	std::for_each(vertices.begin(), vertices.end(), [&matrix](std::pair<int, int>& point)
	{
		point = (matrix * point).coordinate();
	});
	auto cgenerators = old_polygon.getCGenerators();

	std::for_each(cgenerators.begin(), cgenerators.end(), [&matrix](std::pair<std::pair<int, int>, pencolor_t>& cgenerator)
	{
		cgenerator.first = (matrix * cgenerator.first).coordinate();
	});

	return getNewPolygon(old_polygon.getEdgeColor(), cgenerators, vertices);
}

std::vector<Polygon> Polygons::getCutNewPolygon(Polygon& old_polygon, RectangleWindowRim& cutRim)
{
	std::vector<Polygon> ret;
	bool isOut = true;
	switch (rect::RectangleRelation(cutRim, old_polygon.getUttermost()))
	{
	case rect::NON_INTERSECT: return ret;
	case rect::IDENTICAL:
	case rect::IMPLICATE_SUPER:	ret.push_back(old_polygon);	return ret;
	case rect::IMPLICATE_SUB:
	case rect::INTERSECT:
		break;
	default: throw std::string("corrupted response");
	}
	auto rim = cutRim.PolygonCut(old_polygon.getProfile());
	for (size_t i = 0; i < rim.size(); i++)
	{
		if (rim[i].getApexes().empty())	continue;
		auto&& cgs = old_polygon.getCGenerators();
		if (!cgs.empty()) {
			cgs[0].first = rim[i].getApexes().at(0);
		}
		ret.push_back(Polygon(rim[i], old_polygon.getEdgeColor(), cgs));
	}
	return ret;
}

