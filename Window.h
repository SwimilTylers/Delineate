#pragma once
#include <utility>

class Window
{
public:
	Window();
	Window(std::pair<int, int> size);
	~Window();
	void setWindowSize(std::pair<int, int> size);
	std::pair<int, int> getWindowSize() const;

private:
	std::pair<int, int> WindowSize;
};

