#include <iostream>
#include <string>
#include <Windows.h>
#include <GL\glut.h>
#include "ReactionServer.h"
#include "Reaction.h"
using namespace std;

ReactionServer server;
static bool lock = false;
extern char WorkPath[_MAX_PATH];
extern HANDLE hOut, hIn;
extern int PAGE_HEIGHT, PAGE_WIDTH;

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
	case GLUT_KEY_F1:
		clog << "F1" << endl;
		delegater.invoked(reaction::Buttom::PAINT);
		if (delegater.ifReadyPrompt()) {
			auto&& cmdset = delegater.sendPrompt();
			for each (auto&& prompt in cmdset)
			{
				std::clog << prompt << std::endl;
				server(prompt);
				if (server.isReadyToExport())	Display();
			}
		}
		break;
	case GLUT_KEY_F2:
		clog << "F2" << endl;
		if (!lock) {
			lock = true;
			Player.TextWords("Paint", std::pair<int, int>(2 * PAGE_WIDTH - 145, 2 * PAGE_HEIGHT - 70));
			Display();
			delegater.invoked(reaction::Buttom::PAINT);
		}
		else {
			lock = false;
			Player.TextWords("Paint", std::pair<int, int>(2 * PAGE_WIDTH - 145, 2 * PAGE_HEIGHT - 70));
			Display();
			delegater.invoked(reaction::Buttom::CLOSEPAINT);
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
		break;
	default:
		break;
	}
}