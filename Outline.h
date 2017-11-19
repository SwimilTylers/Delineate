#pragma once
#include <vector>

class Window;

class Outline
{
public:
	Outline();
	virtual ~Outline();
	virtual std::vector<std::pair<int, int>> Vertices(Window &window_now) = 0;
};

