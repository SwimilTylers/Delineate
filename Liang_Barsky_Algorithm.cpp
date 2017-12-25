#include "Liang_Barsky_Algorithm.h"
#include "GeometricLine.h"
#include "RectangleWindowRim.h"
#include <string>

enum class WINDOW_EDGE { LEFT, RIGHT, UP, DOWN };
struct Liang_Barsky_Algorithm_Record
{
	std::pair<std::pair<int, int>, std::pair<int, int>> crossline;
	std::pair<std::pair<int, int>, std::pair<int, int>> hitwindowedge;
	WINDOW_EDGE hitwindowedge_type;
	std::pair<int, int> hitpoint;
	crosspoint_t type;

	Liang_Barsky_Algorithm_Record(const GeometricLine& line, const RectangleWindowRim& window, const WINDOW_EDGE hit_edge, double u, crosspoint_t cross_type)
	{
		const auto window_left(window.getHorizontalStartAndEnd().first);
		const auto window_right(window.getHorizontalStartAndEnd().second);
		const auto window_down(window.getVerticalStartAndEnd().first);
		const auto window_up(window.getVerticalStartAndEnd().second);
		const auto LBA_start(line.get_vertices().second);

		crossline = line.get_vertices();

		hitwindowedge_type = hit_edge;
		if (hit_edge == WINDOW_EDGE::LEFT)
		{
			hitwindowedge.first.first = window_left;
			hitwindowedge.first.second = window_down;

			hitwindowedge.second.first = window_left;
			hitwindowedge.second.second = window_up;
		}
		else if (hit_edge == WINDOW_EDGE::UP)
		{
			hitwindowedge.first.first = window_left;
			hitwindowedge.first.second = window_up;

			hitwindowedge.second.first = window_right;
			hitwindowedge.second.second = window_up;
		}
		else if (hit_edge == WINDOW_EDGE::RIGHT)
		{
			hitwindowedge.first.first = window_right;
			hitwindowedge.first.second = window_up;

			hitwindowedge.second.first = window_right;
			hitwindowedge.second.second = window_down;
		}
		else if (hit_edge == WINDOW_EDGE::DOWN)
		{
			hitwindowedge.first.first = window_right;
			hitwindowedge.first.second = window_down;

			hitwindowedge.second.first = window_left;
			hitwindowedge.second.second = window_down;
		}
		else
		{
			throw nullptr;
		}

		hitpoint.first = static_cast<int>(LBA_start.first + u * line.get_deltas().first + 0.5);
		hitpoint.second = static_cast<int>(LBA_start.second + u * line.get_deltas().second + 0.5);

		type = cross_type;
	}

	std::pair<crosspoint_t, std::pair<int, int>> getHitpoint() const
	{
		return std::pair<crosspoint_t, std::pair<int, int>>(type, hitpoint);
	}
};

Liang_Barsky_Algorithm::Liang_Barsky_Algorithm()
{
}


Liang_Barsky_Algorithm::~Liang_Barsky_Algorithm()
{
}

std::pair<std::pair<int, int>, std::pair<int, int>> Liang_Barsky_Algorithm::LineCutKernel(
	const GeometricLine& line, const RectangleWindowRim& window)
{
	int p[4], q[4];
	double u[2];	// u[0] is umax, u[1] is umin
	const auto LBA_start(line.get_vertices().second);

	const auto window_left(window.getHorizontalStartAndEnd().first);
	const auto window_right(window.getHorizontalStartAndEnd().second);
	const auto window_down(window.getVerticalStartAndEnd().first);
	const auto window_up(window.getVerticalStartAndEnd().second);

	// get ps and qs
	p[0] = -line.get_deltas().first;			q[0] = LBA_start.first - window_left;
	p[1] = line.get_deltas().first;			q[1] = window_right - LBA_start.first;
	p[2] = -line.get_deltas().second;		q[2] = LBA_start.second - window_down;
	p[3] = line.get_deltas().second;		q[3] = window_up - LBA_start.second;

	// check if parallel to any window side
	if (!(p[0] && p[2] && p[1] && p[3]))
	{
		if (p[0] == 0) {
			if (q[0] < 0 || q[1] < 0)
				throw std::string("outside the rectangle");

			if (p[2] > 0) {
				// u[0] is umax, u[1] is umin
				u[0] = static_cast<double>(q[2]) / p[2];
				u[1] = static_cast<double>(q[3]) / p[3];

				u[0] = u[0] < 1 ? u[0] : 1;
				u[1] = u[1] > 0 ? u[0] : 0;

			}
			else
			{
				// u[0] is umax, u[1] is umin
				u[0] = static_cast<double>(q[3]) / p[3];
				u[1] = static_cast<double>(q[2]) / p[2];

				u[0] = u[0] < 1 ? u[0] : 1;
				u[1] = u[1] > 0 ? u[0] : 0;
			}

			if (u[0] < u[1])
				throw std::string("outside the rectangle");
		}
		else if (p[2] == 0) {
			if (q[2] < 0 || q[3] < 0)
				throw std::string("outside the rectangle");

			if (p[0] > 0) {
				// u[0] is umax, u[1] is umin
				u[0] = static_cast<double>(q[0]) / p[0];
				u[1] = static_cast<double>(q[1]) / p[1];

				u[0] = u[0] < 1 ? u[0] : 1;
				u[1] = u[1] > 0 ? u[0] : 0;
			}
			else
			{
				// u[0] is umax, u[1] is umin
				u[0] = static_cast<double>(q[1]) / p[1];
				u[1] = static_cast<double>(q[0]) / p[0];

				u[0] = u[0] < 1 ? u[0] : 1;
				u[1] = u[1] > 0 ? u[0] : 0;
			}

			if (u[0] < u[1])
				throw std::string("outside the rectangle");
		}
	}
	else
	{
		int positive_idx[2], negative_idx[2];

		positive_idx[0] = p[0] > 0 ? 0 : 1;
		negative_idx[0] = p[0] < 0 ? 0 : 1;

		positive_idx[1] = p[2] > 0 ? 2 : 3;
		negative_idx[1] = p[2] < 0 ? 2 : 3;

		// u[0] is umax, u[1] is umin
		u[0] = static_cast<double>(q[positive_idx[0]]) / p[positive_idx[0]] < 1 ? static_cast<double>(q[positive_idx[0]]) / p[positive_idx[0]] : 1;
		u[1] = static_cast<double>(q[negative_idx[0]]) / p[negative_idx[0]] < 1 ? static_cast<double>(q[negative_idx[0]]) / p[negative_idx[0]] : 1;

		u[0] = static_cast<double>(q[positive_idx[1]]) / p[positive_idx[1]] < 1 ? static_cast<double>(q[positive_idx[1]]) / p[positive_idx[1]] : 1;
		u[1] = static_cast<double>(q[negative_idx[1]]) / p[negative_idx[1]] < 1 ? static_cast<double>(q[negative_idx[1]]) / p[negative_idx[1]] : 1;

		if (u[0] < u[1])
			throw std::string("outside the rectangle");
	}



	std::pair<int, int> after_start, after_end;

	after_start.first = static_cast<int>(LBA_start.first + u[1] * line.get_deltas().first + 0.5);
	after_start.second = static_cast<int>(LBA_start.second + u[1] * line.get_deltas().second + 0.5);

	after_end.first = static_cast<int>(LBA_start.first + u[0] * line.get_deltas().first + 0.5);
	after_end.second = static_cast<int>(LBA_start.second + u[0] * line.get_deltas().second + 0.5);

	return std::pair<std::pair<int, int>, std::pair<int, int>>(after_start, after_end);
}

void Liang_Barsky_Algorithm::LineCutIOMark(const PolygonRim& Cut, std::deque<std::pair<crosspoint_t, std::pair<int, int>>>& Cutv,
	const RectangleWindowRim& Win, std::deque<std::pair<crosspoint_t, std::pair<int, int>>>& Winv)
{
	for (auto && apex : Cut.getApexes())
	{
		Cutv.push_back(std::pair<crosspoint_t, std::pair<int, int>>(rect::NOTCROSSPOINT, apex));
	}

	const auto window_left(Win.getHorizontalStartAndEnd().first);
	const auto window_right(Win.getHorizontalStartAndEnd().second);
	const auto window_down(Win.getVerticalStartAndEnd().first);
	const auto window_up(Win.getVerticalStartAndEnd().second);

	std::pair<int, int> left_down(window_left, window_down), left_up(window_left, window_up),
		right_up(window_right, window_up), right_down(window_right, window_down);
	std::deque<std::pair<crosspoint_t, std::pair<int, int>>> left, right, up, down;

	auto iter = Cutv.begin();
	for (auto && edge : Cut.getEdge())
	{
		try	{	LineCutKernel(edge.getOriginal(), Win);	}
		catch (std::string)	{}
		for (auto && entry : logserver)
		{
			iter = Cutv.insert(iter, entry.getHitpoint());
			if (entry.hitwindowedge_type == WINDOW_EDGE::LEFT) { left.push_back(entry.getHitpoint()); }
			else if (entry.hitwindowedge_type == WINDOW_EDGE::RIGHT) { right.push_back(entry.getHitpoint()); }
			else if (entry.hitwindowedge_type == WINDOW_EDGE::UP) { up.push_back(entry.getHitpoint()); }
			else if (entry.hitwindowedge_type == WINDOW_EDGE::DOWN) { down.push_back(entry.getHitpoint()); }
			else throw nullptr;
		}
		++iter;
	}

	Winv.push_back(std::pair<crosspoint_t, std::pair<int, int>>(rect::CROSSPOINT::NOTCROSSPOINT, left_down));
	Winv.insert(Winv.end(), left.begin(), left.end());
	Winv.push_back(std::pair<crosspoint_t, std::pair<int, int>>(rect::CROSSPOINT::NOTCROSSPOINT, left_up));
	Winv.insert(Winv.end(), up.begin(), up.end());
	Winv.push_back(std::pair<crosspoint_t, std::pair<int, int>>(rect::CROSSPOINT::NOTCROSSPOINT, right_up));
	Winv.insert(Winv.end(), right.begin(), right.end());
	Winv.push_back(std::pair<crosspoint_t, std::pair<int, int>>(rect::CROSSPOINT::NOTCROSSPOINT, right_down));
	Winv.insert(Winv.end(), down.begin(), down.end());

	logserver.clear();
}
