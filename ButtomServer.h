#pragma once
#include <vector>
#include <deque>
#include "Graphic.h"
#include "Delegate.h"

extern int PAGE_HEIGHT;
extern int PAGE_WIDTH;

class ButtomServer
{
public:
	ButtomServer(Delegate* delegater);
	~ButtomServer();

	void getCurrent(bool isDown, int raw_x, int raw_y);
	std::vector<Graphic*>& VisualizeButtom() { return buttom; }
	std::vector<std::pair<std::string, std::pair<int, int>>>& TextifyButtom() { return buttomText; }

private: 
	std::pair<int, int> current;
	std::vector<Graphic*> buttom;
	std::vector<std::pair<std::string, std::pair<int, int>>> buttomText;
	std::vector<pencolor_t> colorlist;

	bool idle;

	Delegate* delegater = nullptr;
};

