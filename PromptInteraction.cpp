#include <iostream>
#include <string>
#include <Windows.h>
#include "ReactionServer.h"
#include "ColorPrint.h"
using namespace std;

ReactionServer server;
extern char WorkPath[_MAX_PATH];

void PromptInteraction(unsigned char key, int x, int y) {
	string prompt;
	
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

	server.DisableIsReady();

	switch (key)
	{
	case 'P':
	case 'p':
		SetConsoleTextAttribute(hOut,
			FOREGROUND_RED |
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
			cout << ">";
			getline(std::cin, prompt);
			server(prompt);
		}
		break;
	default:
		break;
	}
}