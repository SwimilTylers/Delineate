#include "GeometricCircle.h"



GeometricCircle::GeometricCircle(const std::pair<int, int> centroid, const int radius)
{
	this->centroid = centroid;
	this->radius = radius;
}


GeometricCircle::~GeometricCircle()
{
}

void GeometricCircle::setRadius(const int newRadius)
{
	radius = newRadius;
}

int GeometricCircle::getRadius() const
{
	return radius;
}

void GeometricCircle::setCentroid(const std::pair<int, int> newCentroid)
{
	centroid = newCentroid;
}

std::pair<int, int> GeometricCircle::getCentroid() const
{
	return centroid;
}

bool GeometricCircle::out_range(const Window& window)
{
	return false;
}

bool GeometricCircle::complete_image(const Window& window)
{
	return true;
}
