#pragma once
#include "Window.h"
#include <vector>
#include "Outline.h"

class Graphic
{
public:
	Graphic();
	virtual ~Graphic();
	virtual std::vector<std::pair<int,int>> Vertices(const Window& window) = 0;
	float* getColor();
	void setColor(float Red, float Green, float Blue);

private:
	std::vector<Outline> outlines_surround;
	float color[3];
};

