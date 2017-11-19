#include "GLPlayer.h"
#include <GL/glut.h>
#include <utility>
#include "Outline.h"
#include "Graphic.h"
using namespace std;


GLPlayer::GLPlayer()
{
}

void GLPlayer::DrawOutline(Outline& outline)
{
	glBegin(GL_POINTS);
	for (const pair<int,int> element : outline.Vertices(WindowNow))
	{
		glVertex2d(element.first, element.second);
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
		glVertex2d(element.first, element.second);
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
