#include <iostream>
#include <GL/glut.h>
#include "GLPlayer.h"
#include "GeometricLine.h"
#include "StraightLine.h"
using namespace std;

#define DEBUG 1

#if DEBUG
  void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	static Window window(pair<int, int>(1000, 800));
	static GLPlayer Player(window);
	static GeometricLine geometric_line(pair<int, int>(0, 800), pair<int, int>(0, 0));
	static GeometricLine geometric_line_2(pair<int, int>(0, 0), pair<int, int>(200, 300));
	static GeometricLine geometric_line_3(pair<int, int>(0, 0), pair<int, int>(1000, 0));
	static StraightLine line(geometric_line);
	static StraightLine line_2(geometric_line_2);
	static StraightLine line_3(geometric_line_3);
	Player.DrawOutline(line);
	Player.DrawOutline(line_2);
	Player.DrawOutline(line_3);
	glFlush();
}
#elif TEST_ONE
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(10);
	
	glBegin(GL_POINTS);
	glVertex2d(1, 1);
	glVertex2d(2, 2);
	glVertex2d(3, 3);
	glVertex2d(4, 4);
	glVertex2d(5, 5);
	glVertex2d(6, 6);
	glVertex2d(7, 7);
	glVertex2d(8, 8);
	glVertex2d(9, 9);
	glEnd();

	glPointSize(1);

	glRectd(2.2, 3.1, 12.2, 13.1);
}
#else
void TEST()
  {
	glPointSize(10);
  	glBegin(GL_POINTS);
	

	glVertex3f(0.25, 0.25, 0.0);
	glVertex3f(0.75, 0.25, 0.0);
	glVertex3f(0.75, 0.75, 0.0);
	glVertex3f(0.25, 0.75, 0.0);
	glEnd();

	glFlush();
  }

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	TEST();
	glFlush();
}
#endif


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInit(&argc, argv);                           //初始化GLUT并处理命令行参数  
	glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);      //指定模式：单缓存OR双缓存；RGBA模式OR颜色索引模式  
	glutInitWindowSize(1000, 800);                    //指定窗口大小（像素）  
	glutInitWindowPosition(0, 0);                //指定窗口左上角在屏幕上的位置  
	glutCreateWindow("Delineate");                      //使用OpenGL场景创建一个窗口，参数为窗口名称  
	glClearColor(1.0, 1.0, 1.0, 1.0);
//	glShadeModel(GL_FLAT);
	
	glutDisplayFunc(&Display);

	glutMainLoop();
	return 0;
}