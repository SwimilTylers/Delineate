#include "GeometricEllipse.h"



GeometricEllipse::GeometricEllipse(const std::pair<int,int> centroid, const int s_major, const int s_minor): GeometricCircle(centroid, s_major)
{
	semi_major_axis = s_major;
	semi_minor_axis = s_minor;
	focus = sqrt(abs(semi_major_axis*semi_major_axis - semi_minor_axis*semi_minor_axis));
	foci = std::pair<std::pair<int, int>, std::pair<int, int>>
		(std::pair<int, int>(centroid.first - focus, centroid.second),
			std::pair<int, int>(centroid.first + focus, centroid.second));
}


GeometricEllipse::~GeometricEllipse()
{
}

int GeometricEllipse::get_semi_major_axis() const
{
	return semi_major_axis;
}

void GeometricEllipse::set_semi_major_axis(const int s_major)
{
	semi_major_axis = s_major;
}

int GeometricEllipse::get_semi_minor_axis() const
{
	return semi_minor_axis;
}

void GeometricEllipse::get_semi_minor_axis(const int s_minor)
{
	semi_minor_axis = s_minor;
}

double GeometricEllipse::get_focus_length() const
{
	return focus;
}

std::pair<std::pair<int, int>, std::pair<int, int>> GeometricEllipse::get_foci() const
{
	return foci;
}
