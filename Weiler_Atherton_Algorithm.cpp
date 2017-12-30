#include "Weiler_Atherton_Algorithm.h"
#include <deque>
#include "Liang_Barsky_Algorithm.h"
#include "Delegate.h"
#include <cassert>

inline bool polygon_validation_check(std::vector<std::pair<int, int>>& vtx) {
	int min_x = 0x7fffffff, min_y = 0x7fffffff;
	int max_x = 0x80000000, max_y = 0x80000000;

	for each (auto&& point in vtx)
	{
		min_x = min_x < point.first ? min_x : point.first;
		max_x = max_x > point.first ? max_x : point.first;

		min_y = min_y < point.second ? min_y : point.second;
		max_y = max_y > point.second ? max_y : point.second;
	}

	return min_x != max_x && min_y != max_y;
}

Weiler_Atherton_Algorithm::Weiler_Atherton_Algorithm()
{
}


Weiler_Atherton_Algorithm::~Weiler_Atherton_Algorithm()
{
}

std::vector<PolygonRim> Weiler_Atherton_Algorithm::PolygonCutKernel(const PolygonRim& Cut,
	const RectangleWindowRim& window) const
{
	std::deque<std::pair<crosspoint_t, std::pair<int, int>>> Cutv, Winv;
	Liang_Barsky_Algorithm().LineCutIOMark(Cut, Cutv, window, Winv);
	std::vector<std::pair<int, int>> ret_point;
	std::vector<PolygonRim> ret;
	int start_iter = 0;
	for (; start_iter < Cutv.size() && Cutv.at(start_iter).first != rect::CROSSPOINT::IN; ++start_iter);
	if (start_iter == Cutv.size())	return ret;
	while (start_iter < Cutv.size())
	{
		int first_in = start_iter;
		do
		{
			ret_point.push_back(Cutv.at(first_in).second);
			int first_out = first_in + 1;
			for (; first_out != first_in; ++first_out)
			{
				first_out = first_out < Cutv.size() ? first_out : first_out - Cutv.size();
				ret_point.push_back(Cutv.at(first_out).second);
				if (Cutv.at(first_out).first == rect::CROSSPOINT::OUT)
					break;
			}
			assert(first_in != first_out && Cutv.at(first_out).first == rect::CROSSPOINT::OUT);
			int s_first_out = 0;
			for (; s_first_out < Winv.size(); ++s_first_out)
			{
				if (Winv.at(s_first_out).first == rect::CROSSPOINT::OUT)
					if (Winv[s_first_out].second == Cutv[first_out].second)
						break;
			}
			assert(Winv.at(s_first_out).first == rect::CROSSPOINT::OUT && Winv[s_first_out].second == Cutv[first_out].second);
			int s_first_in = s_first_out + 1;
			for (; s_first_in != s_first_out; ++s_first_in)
			{
				s_first_in = s_first_in < Winv.size() ? s_first_in : s_first_in - Winv.size();
				ret_point.push_back(Winv.at(s_first_in).second);
				if (Winv.at(s_first_in).first == rect::CROSSPOINT::IN)
					break;
			}
			assert(s_first_in != s_first_out && Winv.at(s_first_in).first == rect::CROSSPOINT::IN);
			ret_point.pop_back();
			Winv.at(s_first_in).first = rect::CROSSPOINT::ET_CETERA;
			for (first_in = 0; first_in < Cutv.size(); ++first_in)
			{
				if (Cutv.at(first_in).first == rect::CROSSPOINT::IN)
					if (Cutv[first_in].second == Winv[s_first_in].second)
						break;
			}
			assert(Cutv.at(first_in).first == rect::CROSSPOINT::IN && Cutv[first_in].second == Winv[s_first_in].second);
			Cutv.at(first_in).first = rect::CROSSPOINT::ET_CETERA;	// neutralize visited node
		} while (first_in != start_iter);
		if(polygon_validation_check(ret_point))
			ret.push_back(PolygonRims().getNewRim(ret_point));
		ret_point.clear();
		for (; start_iter < Cutv.size() && Cutv.at(start_iter).first != rect::CROSSPOINT::IN; ++start_iter);
	}

	return ret;
}
