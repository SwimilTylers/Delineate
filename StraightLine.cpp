#include "StraightLine.h"



StraightLine::StraightLine(GeometricLine& description): orignal(description)
{
}


StraightLine::~StraightLine()
{
}

std::vector<std::pair<int, int>> StraightLine::Vertices(Window& window_now)
{
	std::vector<std::pair<int, int>> ret;
	GeometricLine* compatible_line = orignal.compatibility(window_now);
	if (compatible_line == nullptr)
		return ret;
	if (compatible_line->getGradient() == 0 
		|| compatible_line->getGradient() == INFINITY 
		|| compatible_line->getGradient() == NAN)
	{
		return internal_link_str8(compatible_line->get_vertices());
	}
	else
	{
		// regularize
		const bool isTensorExchange(abs(compatible_line->getGradient()) > 1);
		const bool isGradientNegative(compatible_line->getGradient() < 0);

		const std::pair<std::pair<int, int>, std::pair<int, int >> vtx = compatible_line->get_vertices();
		std::pair<int, int> sta = vtx.first;
		std::pair<int, int> end = vtx.second;
		std::pair<int, int> deltas(abs(compatible_line->get_deltas().first), abs(compatible_line->get_deltas().second));

		delete compatible_line;

		if (isTensorExchange)
		{
			Exchange_Tensor(sta);
			Exchange_Tensor(end);
			Exchange_Tensor(deltas);
		}

		if (sta.first > end.first)
			Exchange_Vector(sta, end);
		const int displacement = end.first - sta.first;


		// output
		return Wrapping(internal_xinc_l2r_asc(sta, deltas, displacement), isTensorExchange, isGradientNegative);

	}
}


// regularied drawing
std::vector<std::pair<int, int>> StraightLine::internal_xinc_l2r_asc(std::pair<int, int>& leftdown,
	std::pair<int, int>& deltas, const int xincs)
{
	int p = 2 * deltas.second - deltas.first;
	std::vector<std::pair<int, int>> ret;
	std::pair<int, int> point(leftdown);
	ret.push_back(leftdown);
	point.first++;
	for (int i = 0; i < xincs; i++, point.first++) {
		if (p > 0)
		{
			point.second++;
			p = p + 2 * deltas.second - 2 * deltas.first;
		}
		else
		{
			p = p + 2 * deltas.second;
		}
		ret.push_back(point);
	}
	return ret;
}
