#include "Reaction.h"

typedef void(Delegate::*SERVICE)(bool, std::pair<int, int>);


Delegate::Delegate()
{
	shouldAwakeKeyborad = false;
	isReadyPrompt = false;
	isReadyPrompt_mark = false;
	color.resize(3, 0);
	routine = (SERVICE)(&Delegate::idle);
}


void Delegate::invoked(reaction::Buttom Reaction) {
	vertices.clear();
	shouldAwakeKeyborad = false;
	isReadyPrompt = false;

	// specials:
	if (Reaction == reaction::Buttom::PROMPT) {
		shouldAwakeKeyborad = true;
	}
	else if (Reaction == reaction::Buttom::IDLE) {
		if (routine == (SERVICE)(&Delegate::idle)) {
			prompt.clear();
			prompt = "export trash Explicit\nexport trash Idle\nat ease @clear-ans immediate#";
			foci.clear();

			line_count = 0;
			ellipse_count = 0;
			rect_count = 0;
			polygon_count = 0;

			isReadyPrompt = true;
			isReadyPrompt_mark = true;
		}
		else	routine = (SERVICE)(&Delegate::idle);
	}

	// creates:
	else if (Reaction == reaction::Buttom::Line) {
		foci.clear();
		routine = (SERVICE)(&Delegate::straightline);
	}
	else if (Reaction == reaction::Buttom::Ellipse) {
		foci.clear();
		routine = (SERVICE)(&Delegate::ellipse);
	}
	else if (Reaction == reaction::Buttom::Rectangle) {
		foci.clear();
		routine = (SERVICE)(&Delegate::rectangle);
	}
	else if (Reaction == reaction::Buttom::Polygon) {
		foci.clear();
		routine = (SERVICE)(&Delegate::polygon);
	}

	// colors:
	else if (Reaction == reaction::Buttom::BLACK) {
		color.clear();
		color.resize(3, 0);
	}
	else if (Reaction == reaction::Buttom::WHITE) {
		color.clear();
		color.resize(3, 1);
	}
	else if (Reaction == reaction::Buttom::RED) {
		color.clear();
		color.resize(3, 0);
		color[0] = 1;
	}
	else if (Reaction == reaction::Buttom::YELLOW) {
		color.clear();
		color.resize(3, 0);
		color[0] = 1;
		color[1] = 1;
	}
	else if (Reaction == reaction::Buttom::BLUE) {
		color.clear();
		color.resize(3, 0);
		color[2] = 1;
	}
	else if (Reaction == reaction::Buttom::GREEN) {
		color.clear();
		color.resize(3, 0);
		color[1] = 1;
	}
	else if (Reaction == reaction::Buttom::PURPLE) {
		color.clear();
		color.resize(3, 0);
		color[0] = 1;
		color[2] = 1;
	}
	else if (Reaction == reaction::Buttom::CYAN) {
		color.clear();
		color.resize(3, 0);
		color[1] = 1;
		color[2] = 1;
	}
	else if (Reaction == reaction::Buttom::GREY) {
		color.clear();
		color.resize(3, 0.5);
	}
}

void Delegate::invoked(bool isDown, int raw_x, int raw_y) {
	std::pair<int, int> coord(raw_x * 2, (PAGE_HEIGHT - raw_y) * 2);
	(this->*routine)(isDown, coord);
}

void Delegate::straightline(bool isDown, std::pair<int, int> coord) {
	if(isDown)	vertices.push_back(coord);
	if (coord.first < 150) vertices.clear();
	else if(vertices.size() == 2){
		char prompt_str[200];
		char name[20];
		sprintf(name, "line_%d", line_count);
		++line_count;

		sprintf(prompt_str, "import temp outline immediate# -n %s -t L -p --focus --set-color [%f,%f,%f] $", name, color[0], color[1], color[2]);
		
		prompt.clear();
		prompt = prompt_str;

		std::string V(" -v");
		char buf[32];
		sprintf(buf, " [%d,%d]", vertices[0].first, vertices[0].second);
		V += buf;
		sprintf(buf, " [%d,%d]", coord.first, coord.second);
		V += buf;
		V += " $";

		prompt += V;

		isReadyPrompt = true;
		vertices.clear();
	}
}


void Delegate::ellipse(bool isDown, std::pair<int, int> coord) {
	if (isDown)	vertices.push_back(coord);
	if (coord.first < 150) vertices.clear();
	else if (!isDown && vertices.size() == 1) {
		char prompt_str[200];
		char name[20];
		sprintf(name, "circ_%d", ellipse_count);
		++ellipse_count;

		sprintf(prompt_str, "import temp outline immediate# -n %s -t E -p --focus --set-color [%f,%f,%f] --uttermost $", name, color[0], color[1], color[2]);

		prompt.clear();
		prompt = prompt_str;

		std::string V(" -v");
		char buf[32];
		sprintf(buf, " [%d,%d]", vertices[0].first, vertices[0].second);
		V += buf;
		sprintf(buf, " [%d,%d]", coord.first, coord.second);
		V += buf;
		V += " $";

		prompt += V;

		isReadyPrompt = true;
		vertices.clear();
	}
}


void Delegate::rectangle(bool isDown, std::pair<int, int> coord) {
	if (isDown)	vertices.push_back(coord);
	if (coord.first < 150) vertices.clear();
	else if (!isDown && vertices.size() == 1) {
		char prompt_str[200];
		char name[20];
		sprintf(name, "rect_%d", rect_count);
		++rect_count;

		sprintf(prompt_str, "import temp outline immediate# -n %s -t P -p --focus --set-color [%f,%f,%f] $", name, color[0], color[1], color[2]);

		prompt.clear();
		prompt = prompt_str;

		std::string V(" -v");
		char buf[32];
		sprintf(buf, " [%d,%d]", vertices[0].first, vertices[0].second);
		V += buf;
		sprintf(buf, " [%d,%d]", coord.first, coord.second);
		V += buf;
		V += " $";

		prompt += V;

		isReadyPrompt = true;
		vertices.clear();
	}
}


void Delegate::polygon(bool isDown, std::pair<int, int> coord) {
	if (isDown)	vertices.push_back(coord);

	if (coord.first < 150) vertices.clear();
	else if (isDown && vertices.size() >= 3 && abs(vertices[0].first - coord.first) + abs(vertices[0].second - coord.second) < 30) {
		char prompt_str[200];
		char name[20];
		sprintf(name, "poly_%d", polygon_count);
		++polygon_count;

		sprintf(prompt_str, "import temp outline immediate# -n %s -t P -p --focus --set-color [%f,%f,%f] $", name, color[0], color[1], color[2]);

		prompt.clear();
		prompt = prompt_str;

		std::string V(" -v");
		char buf[32];
		for each (auto&& point in vertices)
		{
			sprintf(buf, " [%d,%d]", point.first, point.second);
			V += buf;
		}
		V += " $";

		prompt += V;

		isReadyPrompt = true;
		vertices.clear();
	}
}


Delegate::~Delegate()
{
}
