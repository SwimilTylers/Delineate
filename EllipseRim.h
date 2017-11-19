#pragma once
#include "CircleRim.h"
#include "GeometricEllipse.h"

class EllipseRim :
	public CircleRim
{
public:
	EllipseRim(GeometricEllipse& description);
	~EllipseRim();
private:
	GeometricEllipse* ellipse;
	void internal_FirstQuadrant_Upper() override;
	void toQuadrant() override;
};

