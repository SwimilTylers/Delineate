#pragma once
#include <vector>
#include "Typedef.h"

class Window;

class Outline
{
public:
	Outline();
	virtual ~Outline();
	virtual std::vector<std::pair<int, int>> Vertices(Window &window_now) = 0;

	void setColor(const pencolor_t edgecolor) { color = edgecolor; }
	std::vector<float> getColor() const {
		return color;
	}

private:
	pencolor_t color;
};

