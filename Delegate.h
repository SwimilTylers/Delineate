#pragma once
#include <vector>
#include "Typedef.h"
#include "Matrix.h"

namespace reaction {
	enum class Buttom {
		Line, Ellipse, Rectangle, Polygon, PROMPT, 
		PAINT, CLOSEPAINT, DEPAINT, EDGECOLOR, CLOSEEDGECOLOR, OPENEDGE, CLOSEEDGE,
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
		bool isValid() const {
			return min_x != max_x && min_y != max_y;
		}
		bool isIn(std::pair<int, int> point) {
			return point.first <= max_x && point.first >= min_x
				&& point.second <= max_y && point.second >= min_y;
		}
		std::pair<int, int> centriod()const {
			return std::pair<int, int>((max_x + min_x) / 2, (max_y + min_y) / 2);
		}
		void rotate(double rad) {
			auto centr = std::pair<int, int>((max_x + min_x) / 2, (max_y + min_y) / 2);
			auto&& matrix = mtx::relocate(std::pair<int, int>(centr.first, centr.second))
				* (mtx::rotate(rad)
					* mtx::relocate(std::pair<int, int>(-centr.first, -centr.second)));
			std::vector<std::pair<int, int>> vertices(4);
			vertices[0] = std::pair<int, int>(min_x, min_y);
			vertices[1] = std::pair<int, int>(min_x, max_y);
			vertices[2] = std::pair<int, int>(max_x, max_y);
			vertices[3] = std::pair<int, int>(max_x, min_y);

			std::for_each(vertices.begin(), vertices.end(), [&matrix](std::pair<int, int>& point)
			{
				point = (matrix * point).coordinate();
			});

			for each (auto&& point in vertices)
			{
				min_x = min_x < point.first ? min_x : point.first;
				max_x = max_x > point.first ? max_x : point.first;

				min_y = min_y < point.second ? min_y : point.second;
				max_y = max_y > point.second ? max_y : point.second;
			}
		}
		void scale(std::pair<double, double> ratio) {
			auto centr = std::pair<int, int>((max_x + min_x) / 2, (max_y + min_y) / 2);
			min_x = centr.first - (centr.first - min_x)*ratio.first;
			max_x = centr.first + (centr.first - min_x);

			min_y = centr.second - (centr.second - min_y)*ratio.second;
			max_y = centr.second + (centr.second - min_y);
		}
		void move(std::pair<int,int> disp) {
			min_x += disp.first;	max_x += disp.first;
			min_y += disp.second;	max_y += disp.second;
		}
	private:
		int min_x, min_y, max_x, max_y;
	};

	bool shouldAwakeKeyborad;
	bool isReadyPrompt;
	bool isReadyPrompt_mark;
	bool isPaint, isEdgeColor;
	bool isOpenEdge, isCloseEdge, isDePaint;

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

		/*
		isPaint = false;
		isCloseEdge = false;
		isOpenEdge = false;
		isEdgeColor = false;
		isDePaint = false;
		*/
	}

	void straightline(bool, std::pair<int, int>);
	void ellipse(bool, std::pair<int, int>);
	void rectangle(bool, std::pair<int, int>);
	void polygon(bool, std::pair<int, int>);

	void paint(bool, std::pair<int, int>);
	void depaint(bool, std::pair<int, int>);

	void edgecolor(bool isDown, std::pair<int, int> coord);
	void openedge(bool isDown, std::pair<int, int> coord);
	void closeedge(bool isDown, std::pair<int, int> coord);

	void rotate(bool isDown, std::pair<int, int> coord);
	void scale(bool, std::pair<int, int>);
	void move(bool, std::pair<int, int>);

	void cut(bool isDown, std::pair<int, int> coord);
};

