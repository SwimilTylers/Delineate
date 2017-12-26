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

inline void CharToTchar(const char * _char, TCHAR * tchar)
{
	int iLength;

	iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
}

void setConsole() {
	TCHAR work_path[_MAX_PATH] = { 0 };
	GetModuleFileName(NULL, work_path, _MAX_PATH);
	TcharToChar(work_path, WorkPath);
	TCHAR Name[255];
	CharToTchar("Whisper", Name);
	SetConsoleTitle(Name);
}

void setGlut() {
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);      //指定模式：单缓存OR双缓存；RGBA模式OR颜色索引模式  
	glutInitWindowSize(PAGE_WIDTH, PAGE_HEIGHT);                    //指定窗口大小（像素）  
	glutInitWindowPosition(0, 0); 
	glutCreateWindow("Delineate");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutSpecialFunc(PromptInteraction);
	glutDisplayFunc(Display);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);  
	setGlut();

	setConsole();

	glutMainLoop();
	return 0;
}