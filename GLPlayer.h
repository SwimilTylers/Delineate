#pragma once
#include "Window.h"
class Graphic;
class Outline;

class GLPlayer
{
public:
	GLPlayer(Window& InitWindow);
	void DrawOutline(Outline &outline) const;
	void FillGraphic(Graphic &graphic) const;
	Window& getWindow();
	void setWindow(Window& Now);
	~GLPlayer();

private:
	Window& WindowNow;
};

