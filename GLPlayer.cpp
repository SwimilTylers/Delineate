#include "GLPlayer.h"
#include <GL/glut.h>
#include <utility>
#include "Outline.h"
#include "Graphic.h"
using namespace std;

#define FLOAT_PRINT true

GLPlayer::GLPlayer(Window& InitWindow)
{
	WindowNow = InitWindow;
}

void GLPlayer::DrawOutline(Outline& outline) const
{
	glBegin(GL_POINTS);
	for (const pair<int,int> element : outline.Vertices(WindowNow))
	{
#if FLOAT_PRINT
  		glVertex3f(float(element.first) / WindowNow.getWindowSize().first - 1,
			float(element.second) / WindowNow.getWindowSize().second - 1, 0.0);
#else
		glVertex3d(element.first, element.second, 0);
#endif

	}
	glEnd();
}

void GLPlayer::FillGraphic(Graphic& graphic) const
{
	float* color = graphic.getColor();
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_POINTS);
	for (const pair<int, int> element : graphic.EdgeVertices(WindowNow))
	{
#if FLOAT_PRINT
  		glVertex3f(float(element.first) / WindowNow.getWindowSize().first - 1, 
			float(element.second) / WindowNow.getWindowSize().second - 1, 0.0);
#else
		glVertex3d(element.first, element.second, 0);
#endif

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
