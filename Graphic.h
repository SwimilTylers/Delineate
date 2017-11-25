#pragma once
#include "Window.h"
#include <vector>
#include "Outline.h"
#include "StraightLine.h"

class Graphic
{
public:
	Graphic(std::vector<Outline> profile, float Red, float Green, float Blue);
	virtual ~Graphic();
	virtual std::vector<std::pair<int,int>> Vertices(Window& window) = 0;
	float* getColor();
	void setColor(float Red, float Green, float Blue);

protected:
	std::vector<StraightLine>& outlines_surround;
	float color[3];
};

