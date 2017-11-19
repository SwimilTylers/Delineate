#include <iostream>
#include <GL/glut.h>
#include "GLPlayer.h"
#include "GeometricLine.h"
#include "StraightLine.h"
using namespace std;

static GLPlayer Player;

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	static GeometricLine geometric_line(pair<int, int>(0, 0), pair<int, int>(55, 55));
	static StraightLine line(geometric_line);
	Player.DrawOutline(line);

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInit(&argc, argv);                           //初始化GLUT并处理命令行参数  
	glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);      //指定模式：单缓存OR双缓存；RGBA模式OR颜色索引模式  
	glutInitWindowSize(400, 400);                    //指定窗口大小（像素）  
	glutInitWindowPosition(0, 0);                //指定窗口左上角在屏幕上的位置  
	glutCreateWindow("Delineate");                      //使用OpenGL场景创建一个窗口，参数为窗口名称  
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glShadeModel(GL_FLAT);
	
	glutDisplayFunc(&Display);

	glutMainLoop();
	return 0;
}