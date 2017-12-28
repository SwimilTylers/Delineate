#pragma once
#include <vector>
#include "Typedef.h"

namespace reaction {
	enum class Buttom {
		Line, Ellipse, Rectangle, Polygon, PROMPT, COLOR, BLACK, WHITE, RED, YELLOW, BLUE, GREEN, PURPLE, CYAN, GREY, ROTATE, MOVE, SCALE, CUT, SELECT, IDLE
	};
}

class Delegate
{
public:
	Delegate();
	~Delegate();

	void invoked(reaction::Buttom reaction);
	void invoked(bool isDown, int raw_x, int raw_y);
	bool ifAwakeKeyborad() const { return shouldAwakeKeyborad; }
	bool ifReadyPrompt() const { return isReadyPrompt; }
	std::string sendPrompt() {
		isReadyPrompt = false;
		return prompt;
	}

private:
	bool shouldAwakeKeyborad;
	bool isReadyPrompt;
	bool isReadyPrompt_mark;

	std::string prompt;
	std::vector<std::pair<int, int>> vertices;
	std::vector<std::pair<int, int>> foci;
	pencolor_t color;

	std::vector<std::string> name_buf;

	void(Delegate::*routine)(bool, std::pair<int, int>);

	int line_count = 0;
	int ellipse_count = 0;
	int rect_count = 0;
	int polygon_count = 0;

	void idle(bool, std::pair<int, int>){
		shouldAwakeKeyborad = false;
		if(!isReadyPrompt_mark) isReadyPrompt = false;
		isReadyPrompt_mark = false;
	}

	void straightline(bool, std::pair<int, int>);
	void ellipse(bool, std::pair<int, int>);
	void rectangle(bool, std::pair<int, int>);
	void polygon(bool, std::pair<int, int>);
};

