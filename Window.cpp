#include "Window.h"


Window::Window()
{
}

Window::Window(std::pair<int, int> size)
{
	WindowSize = size;
}


Window::~Window()
{
}

void Window::setWindowSize(const std::pair<int, int> size)
{
	WindowSize = size;
}

std::pair<int, int> Window::getWindowSize() const
{
	return WindowSize;
}
