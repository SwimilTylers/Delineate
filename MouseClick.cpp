#include <GL/glut.h>
#include <iostream>
#include <Windows.h>
#include <GL\glut.h>
#include "Reaction.h"

Delegate delegater;
ButtomServer clickserver(&delegater);
extern char WorkPath[_MAX_PATH];
extern HANDLE hOut, hIn;

void MouseClick(int button, int state, int x, int y)
{
	switch(button)
	{
	case GLUT_LEFT_BUTTON: 
		if (state == GLUT_DOWN) {
			clickserver.getCurrent(true, x, y);
			delegater.invoked(true, x, y);
		}
		else if (state == GLUT_UP) {
			clickserver.getCurrent(false, x, y);
			delegater.invoked(false, x, y);
		}
		break;
	case GLUT_RIGHT_BUTTON: break;
	case GLUT_MIDDLE_BUTTON: break;
	default: break;
	}

	
	if (delegater.ifReadyPrompt()) {
		auto&& cmdset = delegater.sendPrompt();
		for each (auto&& prompt in cmdset)
		{
			std::clog << prompt << std::endl;
			server(prompt);
			if (server.isReadyToExport())	Display();
		}
	}
	else if (delegater.ifAwakeKeyborad()) {
		std::string prompt;
		SetConsoleTextAttribute(hOut,
			FOREGROUND_GREEN |
			FOREGROUND_BLUE |
			FOREGROUND_INTENSITY);
		std::cout << "Delineate Control Prompt ";
		SetConsoleTextAttribute(hOut,
			FOREGROUND_RED |
			FOREGROUND_GREEN |
			FOREGROUND_INTENSITY);
		std::cout << "@";
		SetConsoleTextAttribute(hOut,
			FOREGROUND_RED |
			FOREGROUND_INTENSITY);
		std::cout << WorkPath << std::endl;
		SetConsoleTextAttribute(hOut,
			FOREGROUND_RED |
			FOREGROUND_GREEN |
			FOREGROUND_BLUE |
			FOREGROUND_INTENSITY);
		while (!server.isReadyToExport()) {
			std::cout << ">: ";
			getline(std::cin, prompt);
			server(prompt);
		}
		std::clog << "Dialog Terminated" << std::endl;
		Display();
	}
}
