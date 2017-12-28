#pragma once
#include <vector>
#include "Typedef.h"

namespace reaction {
	enum class Buttom {
		Line, Ellipse, Rectangle, Polygon, PROMPT, PAINT, CLOSEPAINT, DEPAINT, EDGECOLOR,
		BLACK, WHITE, RED, YELLOW, BLUE, GREEN, PURPLE, CYAN, GREY, 
		ROTATE, MOVE, SCALE, CUT, SELECT, IDLE
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
	std::vector<std::string> sendPrompt() {
		isReadyPrompt = false;
		return prompt_set;
	}

private:
	class lightRectangleRim {
	public:
		lightRectangleRim(std::vector<std::pair<int, int>>& vtx) {
			min_x = 0x7fffffff; min_y = 0x7fffffff;
			max_x = 0x80000000, max_y = 0x80000000;

			for each (auto&& point in vtx)
			{
				min_x = min_x < point.first ? min_x : point.first;
				max_x = max_x > point.first ? max_x : point.first;
				
				min_y = min_y < point.second ? min_y : point.second;
				max_y = max_y > point.second ? max_y : point.second;
			}
		}
		bool isIn(std::pair<int, int> point) {
			return point.first <= max_x && point.first >= min_x
				&& point.second <= max_y && point.second >= min_y;
		}
	private:
		int min_x, min_y, max_x, max_y;
	};

	bool shouldAwakeKeyborad;
	bool isReadyPrompt;
	bool isReadyPrompt_mark;
	bool isPaint;

	std::vector<std::string> prompt_set;
	std::vector<std::pair<int, int>> vertices;
	std::vector<std::pair<std::string, Delegate::lightRectangleRim*>> foci;
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

	void paint(bool, std::pair<int, int>);
	void depaint(bool, std::pair<int, int>);
};

