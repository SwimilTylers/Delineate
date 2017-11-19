#pragma once
#include "GeometricCircle.h"
class GeometricEllipse :
	public GeometricCircle
{
public:
	GeometricEllipse(std::pair<int, int> centroid, int s_major, int s_minor);
	~GeometricEllipse();

	int get_semi_major_axis() const;
	void set_semi_major_axis(int s_major);
	int get_semi_minor_axis() const;
	void get_semi_minor_axis(int s_minor);
	double get_focus_length() const;
	std::pair<std::pair<int, int>, std::pair<int, int>> get_foci() const;
private:
	int semi_major_axis;
	int semi_minor_axis;
	double focus;
	std::pair<std::pair<int, int>, std::pair<int, int>> foci;
};

