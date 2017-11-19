#pragma once
#include "Window.h"
class Graphic;
class Outline;

class GLPlayer
{
public:
	GLPlayer();
	void DrawOutline(Outline &outline);
	void FillGraphic(Graphic &graphic) const;
	Window& getWindow();
	void setWindow(Window& Now);
	~GLPlayer();

private:
	Window WindowNow;
};

