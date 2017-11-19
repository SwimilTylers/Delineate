#pragma once
#include <utility>
#include "Window.h"

class GeometricCircle
{
public:
	GeometricCircle(std::pair<int,int> centroid, int radius);
	virtual ~GeometricCircle();

	void setRadius(int newRadius);
	int getRadius() const;
	void setCentroid(std::pair<int, int> newCentroid);
	std::pair<int, int> getCentroid() const;
	virtual bool out_range(const Window& window);
	virtual bool complete_image(const Window& window);
private:
	std::pair<int, int> centroid;
	int radius;
};

