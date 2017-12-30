#include <iostream>
#include <string>
#include <Windows.h>
#include <GL\glut.h>
#include "ReactionServer.h"
#include "Reaction.h"
using namespace std;

ReactionServer server;
static bool lock[] = { false,false,false };
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
		clog << "Get rid of paintings" << endl;
		delegater.invoked(reaction::Buttom::DEPAINT);
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
		if (!lock[0]) {
			lock[0] = true;
			clog << "Paint color choose" << endl;
			delegater.invoked(reaction::Buttom::PAINT);
		}
		else {
			lock[0] = false;
			clog << "Paint color choose terminated" << endl;
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
	case GLUT_KEY_F3:
		if (!lock[1]) {
			lock[1] = true;
			clog << "Get edges" << endl;
			delegater.invoked(reaction::Buttom::OPENEDGE);
			if (delegater.ifReadyPrompt()) {
				auto&& cmdset = delegater.sendPrompt();
				for each (auto&& prompt in cmdset)
				{
					std::clog << prompt << std::endl;
					server(prompt);
					if (server.isReadyToExport())	Display();
				}
			}
		}
		else {
			lock[1] = false;
			clog << "Get rid of edges" << endl;
			delegater.invoked(reaction::Buttom::CLOSEEDGE);
			if (delegater.ifReadyPrompt()) {
				auto&& cmdset = delegater.sendPrompt();
				for each (auto&& prompt in cmdset)
				{
					std::clog << prompt << std::endl;
					server(prompt);
					if (server.isReadyToExport())	Display();
				}
			}
		}
		break;
	case GLUT_KEY_F4:
		if (!lock[2]) {
			lock[2] = true;
			clog << "Edge color choose" << endl;
			delegater.invoked(reaction::Buttom::EDGECOLOR);
		}
		else {
			lock[2] = false;
			clog << "Edge color choose terminated" << endl;
			delegater.invoked(reaction::Buttom::CLOSEEDGECOLOR);
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