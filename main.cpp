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
	glutInit(&argc, argv);                           //��ʼ��GLUT�����������в���  
	glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);      //ָ��ģʽ��������OR˫���棻RGBAģʽOR��ɫ����ģʽ  
	glutInitWindowSize(400, 400);                    //ָ�����ڴ�С�����أ�  
	glutInitWindowPosition(0, 0);                //ָ���������Ͻ�����Ļ�ϵ�λ��  
	glutCreateWindow("Delineate");                      //ʹ��OpenGL��������һ�����ڣ�����Ϊ��������  
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glShadeModel(GL_FLAT);
	
	glutDisplayFunc(&Display);

	glutMainLoop();
	return 0;
}