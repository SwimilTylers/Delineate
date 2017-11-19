#include "GLPlayer.h"
#include <GL/glut.h>
#include <utility>
#include "Outline.h"
#include "Graphic.h"
using namespace std;


GLPlayer::GLPlayer(Window& InitWindow)
{
	WindowNow = InitWindow;
}

void GLPlayer::DrawOutline(Outline& outline)
{
	glBegin(GL_POINTS);
	for (const pair<int,int> element : outline.Vertices(WindowNow))
	{
		glVertex3f(float(element.first) / WindowNow.getWindowSize().first - 1,
			float(element.second) / WindowNow.getWindowSize().second - 1, 0.0);
	}
	glEnd();
}

void GLPlayer::FillGraphic(Graphic& graphic) const
{
	float* color = graphic.getColor();
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_POINTS);
	for (const pair<int, int> element : graphic.Vertices(WindowNow))
	{
		glVertex3f(float(element.first) / WindowNow.getWindowSize().first - 1, 
			float(element.second) / WindowNow.getWindowSize().second - 1, 0.0);
	}
	glEnd();
}

Window& GLPlayer::getWindow()
{
	return WindowNow;
}

void GLPlayer::setWindow(Window& Now)
{
	WindowNow = Now;
}


GLPlayer::~GLPlayer()
{
}
