#include <iostream>
#include <string>
#include <Windows.h>
#include <GL\glut.h>
#include "ReactionServer.h"
#include "Reaction.h"
using namespace std;

ReactionServer server;
extern char WorkPath[_MAX_PATH];
extern HANDLE hOut, hIn;

void PromptInteraction(int key, int x, int y) {
	
	string prompt;

	server.DisableIsReady();

	switch (key)
	{
	case GLUT_KEY_INSERT:
		SetConsoleTextAttribute(hOut,
			FOREGROUND_GREEN |
			FOREGROUND_BLUE |
			FOREGROUND_INTENSITY);
		cout << "Delineate Control Prompt ";
		SetConsoleTextAttribute(hOut,
			FOREGROUND_RED |
			FOREGROUND_GREEN |
			FOREGROUND_INTENSITY);
		cout << "@";
		SetConsoleTextAttribute(hOut,
			FOREGROUND_RED |
			FOREGROUND_INTENSITY);
		cout << WorkPath << endl;
		SetConsoleTextAttribute(hOut,
			FOREGROUND_RED |
			FOREGROUND_GREEN |
			FOREGROUND_BLUE |
			FOREGROUND_INTENSITY);
		while (!server.isReadyToExport()) {
			cout << ">: ";
			getline(std::cin, prompt);
			server(prompt);
		}
		clog << "Dialog Terminated" << endl;
		Display();
		break;
	default:
		break;
	}
}