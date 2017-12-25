#include <iostream>
#include <GL/glut.h>
#include <Windows.h>
#include "Reaction.h"


using namespace std;

int PAGE_HEIGHT = 800;
int PAGE_WIDTH = 1000;
char WorkPath[_MAX_PATH];

inline void TcharToChar(const TCHAR * tchar, char * _char)
{
	int iLength; 
	iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);  
	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);                           //��ʼ��GLUT�����������в���  
	glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);      //ָ��ģʽ��������OR˫���棻RGBAģʽOR��ɫ����ģʽ  
	glutInitWindowSize(PAGE_WIDTH, PAGE_HEIGHT);                    //ָ�����ڴ�С�����أ�  
	glutInitWindowPosition(0, 0);                //ָ���������Ͻ�����Ļ�ϵ�λ��  
	glutCreateWindow("Delineate");                      //ʹ��OpenGL��������һ�����ڣ�����Ϊ��������  
	glClearColor(1.0, 1.0, 1.0, 1.0);
//	glShadeModel(GL_FLAT);
	glutKeyboardFunc(PromptInteraction);
	glutDisplayFunc(Display);

	TCHAR work_path[_MAX_PATH] = { 0 };
	GetModuleFileName(NULL, work_path, _MAX_PATH);
	TcharToChar(work_path, WorkPath);

	glutMainLoop();
	return 0;
}