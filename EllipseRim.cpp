#include "EllipseRim.h"
#include "GeometricEllipse.h"


EllipseRim::EllipseRim(GeometricEllipse &description): CircleRim(description)
{
	ellipse = static_cast<GeometricEllipse*>(&description);
}


EllipseRim::~EllipseRim()
{
	ellipse = nullptr;
}

void EllipseRim::internal_FirstQuadrant_Upper()
{
	Trajectory.clear();
	const double r_x(ellipse->get_semi_major_axis());
	const double r_y(ellipse->get_semi_minor_axis());
	const double square_r_x = r_x * r_x;
	const double square_r_y = r_y * r_y;
	double p = square_r_y - square_r_x * r_y + square_r_x / 4;
	std::pair<int, int> point(0, int(r_y));
	Trajectory.push_back(point);
	while (square_r_x * point.second > square_r_y * point.first) {
		if (p >= 0)
		{
			point.second--;
			p = p + 2 * point.first * square_r_y - 2 * point.second * square_r_x - 2 * square_r_x + 3 * square_r_y;
		}
		else
		{
			p = p + 2 * point.first * square_r_y + 3 * square_r_y;
		}
		point.first++;
		Trajectory.push_back(point);
	}
	p = (0.5 + point.first) * square_r_y * (point.first + 0.5) 
		+ square_r_x * (point.second - 1)* (point.second - 1) 
		- square_r_x * square_r_y;
	while (point.second > 0) {
		if (p <= 0)
		{
			point.first++;
			p = p + 2 * point.first * square_r_y - 2 * point.second * square_r_x - 2 * square_r_y + 3 * square_r_x;
		}
		else
		{
			p = p - 2 * point.second * square_r_x + 3 * square_r_x;
		}
		point.second--;
		Trajectory.push_back(point);
	}
}

void EllipseRim::toQuadrant()
{
}
