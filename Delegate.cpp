#include "Reaction.h"
#include <iostream>
typedef void(Delegate::*SERVICE)(bool, std::pair<int, int>);


Delegate::Delegate()
{
	shouldAwakeKeyborad = false;
	isReadyPrompt = false;
	isReadyPrompt_mark = false;
	isPaint = false;
	isDePaint = false;
	isEdgeColor = false;
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
		if (isDePaint) {
			std::clog << "DECOLOR" << std::endl;
			routine = (SERVICE)(&Delegate::depaint);
		}
		else if (isCloseEdge) {
			std::clog << "EDGE: OFF" << std::endl;
			routine = (SERVICE)(&Delegate::closeedge);
		}
		else if (isOpenEdge) {
			std::clog << "EDGE: ON" << std::endl;
			routine = (SERVICE)(&Delegate::openedge);
		}
		else if (routine == (SERVICE)(&Delegate::idle)) {
			std::clog << "CLEAN" << std::endl;
			prompt_set.clear();
			prompt_set.push_back("export trash Explicit");
			prompt_set.push_back("export trash Idle");
			prompt_set.push_back("at ease @clear-ans immediate#");
			// foci.clear();

			line_count = 0;
			ellipse_count = 0;
			rect_count = 0;
			polygon_count = 0;

			isReadyPrompt = true;
			isReadyPrompt_mark = true;

			isPaint = false;
			isCloseEdge = false;
			isOpenEdge = false;
			isEdgeColor = false;
			isDePaint = false;
		}
		else	routine = (SERVICE)(&Delegate::idle);
	}

	// creates:
	else if (Reaction == reaction::Buttom::Line) {
		for each (auto&& var in foci) { delete var.second; }
		foci.clear();
		routine = (SERVICE)(&Delegate::straightline);
	}
	else if (Reaction == reaction::Buttom::Ellipse) {
		for each (auto&& var in foci) { delete var.second; }
		foci.clear();
		routine = (SERVICE)(&Delegate::ellipse);
	}
	else if (Reaction == reaction::Buttom::Rectangle) {
		routine = (SERVICE)(&Delegate::rectangle);
	}
	else if (Reaction == reaction::Buttom::Polygon) {
		routine = (SERVICE)(&Delegate::polygon);
	}

	// rotate, move, scale, cut
	else if (Reaction == reaction::Buttom::ROTATE) {
		routine = (SERVICE)(&Delegate::rotate);
	}
	else if (Reaction == reaction::Buttom::MOVE) {
		routine = (SERVICE)(&Delegate::move);
	}
	else if (Reaction == reaction::Buttom::SCALE) {
		routine = (SERVICE)(&Delegate::scale);
	}
	else if (Reaction == reaction::Buttom::CUT) {
		routine = (SERVICE)(&Delegate::cut);
	}

	// depaint/paint
	else if (Reaction == reaction::Buttom::PAINT)
		isPaint = true;
	else if (Reaction == reaction::Buttom::CLOSEPAINT)
		isPaint = false;
	else if (Reaction == reaction::Buttom::DEPAINT)
		isDePaint = true;
	else if (Reaction == reaction::Buttom::EDGECOLOR)
		isEdgeColor = true;
	else if (Reaction == reaction::Buttom::CLOSEEDGECOLOR)
		isEdgeColor = false;
	else if (Reaction == reaction::Buttom::OPENEDGE) {
		isOpenEdge = true;
		isCloseEdge = false;
	}
	else if (Reaction == reaction::Buttom::CLOSEEDGE) {
		isOpenEdge = false;
		isCloseEdge = true;
	}	

	// colors:
	else if (Reaction == reaction::Buttom::BLACK) {
		color.clear();
		color.resize(3, 0);
		if (isPaint) {
			std::clog << "BLACK" << std::endl;
			routine = (SERVICE)(&Delegate::paint);
		}
		if (isEdgeColor) {
			std::clog << "BLACK" << std::endl;
			routine = (SERVICE)(&Delegate::edgecolor);
		}
	}
	else if (Reaction == reaction::Buttom::WHITE) {
		color.clear();
		color.resize(3, 1);
		if (isPaint) {
			std::clog << "WHITE" << std::endl;
			routine = (SERVICE)(&Delegate::paint);
		}
		if (isEdgeColor) {
			std::clog << "WHITE" << std::endl;
			routine = (SERVICE)(&Delegate::edgecolor);
		}
	}
	else if (Reaction == reaction::Buttom::RED) {
		color.clear();
		color.resize(3, 0);
		color[0] = 1;
		if (isPaint) {
			std::clog << "RED" << std::endl;
			routine = (SERVICE)(&Delegate::paint);
		}
		if (isEdgeColor) {
			std::clog << "RED" << std::endl;
			routine = (SERVICE)(&Delegate::edgecolor);
		}
	}
	else if (Reaction == reaction::Buttom::YELLOW) {
		color.clear();
		color.resize(3, 0);
		color[0] = 1;
		color[1] = 1;
		if (isPaint) {
			std::clog << "YELLOW" << std::endl;
			routine = (SERVICE)(&Delegate::paint);
		}
		if (isEdgeColor) {
			std::clog << "YELLOW" << std::endl;
			routine = (SERVICE)(&Delegate::edgecolor);
		}
	}
	else if (Reaction == reaction::Buttom::BLUE) {
		color.clear();
		color.resize(3, 0);
		color[2] = 1;
		if (isPaint) {
			std::clog << "BLUE" << std::endl;
			routine = (SERVICE)(&Delegate::paint);
		}
		if (isEdgeColor) {
			std::clog << "BLUE" << std::endl;
			routine = (SERVICE)(&Delegate::edgecolor);
		}
	}
	else if (Reaction == reaction::Buttom::GREEN) {
		color.clear();
		color.resize(3, 0);
		color[1] = 1;
		if (isPaint) {
			std::clog << "GREEN" << std::endl;
			routine = (SERVICE)(&Delegate::paint);
		}
		if (isEdgeColor) {
			std::clog << "GREEN" << std::endl;
			routine = (SERVICE)(&Delegate::edgecolor);
		}
	}
	else if (Reaction == reaction::Buttom::PURPLE) {
		color.clear();
		color.resize(3, 0);
		color[0] = 1;
		color[2] = 1;
		if (isPaint) {
			std::clog << "PURPLE" << std::endl;
			routine = (SERVICE)(&Delegate::paint);
		}
		if (isEdgeColor) {
			std::clog << "PURPLE" << std::endl;
			routine = (SERVICE)(&Delegate::edgecolor);
		}
	}
	else if (Reaction == reaction::Buttom::CYAN) {
		color.clear();
		color.resize(3, 0);
		color[1] = 1;
		color[2] = 1;
		if (isPaint) {
			std::clog << "CYAN" << std::endl;
			routine = (SERVICE)(&Delegate::paint);
		}
		if (isEdgeColor) {
			std::clog << "CYAN" << std::endl;
			routine = (SERVICE)(&Delegate::edgecolor);
		}
	}
	else if (Reaction == reaction::Buttom::GREY) {
		color.clear();
		color.resize(3, 0.5);
		if (isPaint) {
			std::clog << "GREY" << std::endl;
			routine = (SERVICE)(&Delegate::paint);
		}
		if (isEdgeColor) {
			std::clog << "GREY" << std::endl;
			routine = (SERVICE)(&Delegate::edgecolor);
		}
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

		sprintf(prompt_str, "import temp outline immediate# -n %s -t L -p --focus --set-color [%.1f,%.1f,%.1f] $", name, color[0], color[1], color[2]);
		
		prompt_set.clear();
		std::string _prompt(prompt_str);

		std::string V(" -v");
		char buf[32];
		sprintf(buf, " [%d,%d]", vertices[0].first, vertices[0].second);
		V += buf;
		sprintf(buf, " [%d,%d]", coord.first, coord.second);
		V += buf;
		V += " $";

		_prompt += V;

		prompt_set.push_back(_prompt);

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

		sprintf(prompt_str, "import temp outline immediate# -n %s -t E -p --focus --set-color [%.1f,%.1f,%.1f] --uttermost $", name, color[0], color[1], color[2]);

		prompt_set.clear();
		std::string _prompt(prompt_str);

		std::string V(" -v");
		char buf[32];
		sprintf(buf, " [%d,%d]", vertices[0].first, vertices[0].second);
		V += buf;
		sprintf(buf, " [%d,%d]", coord.first, coord.second);
		V += buf;
		V += " $";

		_prompt += V;
		prompt_set.push_back(_prompt);

		isReadyPrompt = true;
		vertices.clear();
	}
}


void Delegate::rectangle(bool isDown, std::pair<int, int> coord) {
	if (isDown)	vertices.push_back(coord);
	if (coord.first < 150) vertices.clear();
	else if (!isDown && vertices.size() == 1) {
		if (abs(vertices[0].first - coord.first) + abs(vertices[0].second - coord.second) < 30) {
			vertices.clear();
			isReadyPrompt = false;
			return;
		}
		
		char prompt_str[200];
		char name[20];
		sprintf(name, "rect_%d", rect_count);
		++rect_count;

		sprintf(prompt_str, "import temp outline -n %s -t P -p --duplicated-graphic --set-color [%.1f,%.1f,%.1f] $", name, color[0], color[1], color[2]);

		prompt_set.clear();
		std::string _prompt = prompt_str;

		std::string V(" -v");
		char buf[32];
		sprintf(buf, " [%d,%d]", vertices[0].first, vertices[0].second);
		V += buf;
		sprintf(buf, " [%d,%d]", coord.first, coord.second);
		V += buf;
		V += " $";

		_prompt += V;
		prompt_set.push_back(_prompt);

		sprintf(prompt_str, "store graphic -n %s -p --focus", name);
		prompt_set.push_back(prompt_str);
		sprintf(prompt_str, "export trash outline -n %s", name);
		prompt_set.push_back(prompt_str);
		prompt_set.push_back("at ease immediate#");

		vertices.push_back(coord);
		for each (auto&& var in foci) { delete var.second; }
		foci.clear();
		foci.push_back(std::pair<std::string, Delegate::lightRectangleRim*>(name, new lightRectangleRim(vertices)));

		isReadyPrompt = true;
		vertices.clear();
	}
}


void Delegate::polygon(bool isDown, std::pair<int, int> coord) {
	if (isDown)	vertices.push_back(coord);
	else return;

	if (coord.first < 150) {
		vertices.clear(); 
		char prompt_str[200];
		prompt_set.clear();
		for each (auto&& name in name_buf)
		{
			sprintf(prompt_str, "export trash outline -n %s", name.c_str());
			prompt_set.push_back(prompt_str);
		}
		name_buf.clear();
		if (!prompt_set.empty())	isReadyPrompt = true;
		return;
	}
	if (abs(vertices[0].first - coord.first) + abs(vertices[0].second - coord.second) < 30 && vertices.size() >= 3) {
		vertices.pop_back();
		char prompt_str[200];
		char name[20];
		sprintf(name, "poly_%d", polygon_count);
		++polygon_count;

		sprintf(prompt_str, "import temp outline -n %s -t P -p --duplicated-graphic --set-color [%.1f,%.1f,%.1f] $", name, color[0], color[1], color[2]);

		prompt_set.clear();
		std::string _prompt = prompt_str;

		std::string V(" -v");
		char buf[32];
		for each (auto&& point in vertices)
		{
			sprintf(buf, " [%d,%d]", point.first, point.second);
			V += buf;
		}
		V += " $";

		_prompt += V;
		prompt_set.push_back(_prompt);

		sprintf(prompt_str, "store graphic -n %s -p --focus", name);
		prompt_set.push_back(prompt_str);
		sprintf(prompt_str, "export trash outline -n %s", name);
		prompt_set.push_back(prompt_str);

		for each (auto&& var in foci) { delete var.second; }
		foci.clear();
		foci.push_back(std::pair<std::string, Delegate::lightRectangleRim*>(name, new lightRectangleRim(vertices)));

		isReadyPrompt = true;
		vertices.clear();

		for each (auto&& name in name_buf)
		{
			sprintf(prompt_str, "export trash outline -n %s", name.c_str());
			prompt_set.push_back(prompt_str);
		}

		prompt_set.push_back("at ease immediate#");

		name_buf.clear();
	}
	else if (vertices.size() >= 2) {
		char prompt_str[200];
		char name[20];
		sprintf(name, "%d-%08x", polygon_count, rand()*rand());
		name_buf.push_back(std::string(name));

		sprintf(prompt_str, "import temp outline immediate# -n %s -t L -p --set-color [%.1f,%.1f,%.1f] $", name, color[0], color[1], color[2]);

		prompt_set.clear();
		std::string _prompt = prompt_str;

		std::string V(" -v");
		char buf[32];
		sprintf(buf, " [%d,%d]", (vertices.end() - 2)->first, (vertices.end() - 2)->second);
		V += buf;
		sprintf(buf, " [%d,%d]", (vertices.end() - 1)->first, (vertices.end() - 1)->second);
		V += buf;
		V += " $";

		_prompt += V;
		prompt_set.push_back(_prompt);

		isReadyPrompt = true;
	}
	
}


void Delegate::paint(bool isDown, std::pair<int, int> coord) {
	if (foci.empty() || !isDown)	return;
	if (isDown && foci[0].second->isIn(coord) && coord.first >= 150) {
		char prompt_str[200];
		vertices.clear();
		/*
		sprintf(prompt_str, "Paint(%.1f:%.1f:%.1f)", color[0], color[1], color[2]);
		std::clog << prompt_str << std::endl;
		*/
		prompt_set.clear();
		sprintf(prompt_str, "record points -v [%d,%d] @release-points", coord.first, coord.second);
		prompt_set.push_back(prompt_str);
		sprintf(prompt_str, "record cgs -p --set-color [%.1f, %.1f, %.1f] $ @release-cgs release-points#", color[0], color[1], color[2]);
		prompt_set.push_back(prompt_str);
		sprintf(prompt_str, "makechange graphic -p --paint replace $ immediate# release-cgs#");
		prompt_set.push_back(prompt_str);

		isReadyPrompt = true;
	}
}

void Delegate::depaint(bool, std::pair<int, int>) {
	prompt_set.clear();
	prompt_set.push_back("makechange graphic -p --paint default $ immediate# release-cgs# release-points#");

	isReadyPrompt = true;
	isDePaint = false;
}


void Delegate::edgecolor(bool, std::pair<int, int>) {
	char prompt_str[200];
	vertices.clear();
	prompt_set.clear();
	sprintf(prompt_str, "makechange graphic -p --set-color [%.1f, %.1f, %.1f] $ immediate#", color[0], color[1], color[2]);
	prompt_set.push_back(prompt_str);

	isReadyPrompt = true;
}

void Delegate::closeedge(bool, std::pair<int, int>) {
	isCloseEdge = false;

	prompt_set.clear();
	prompt_set.push_back("makechange graphic -p --drop-edge $ immediate#");
	isReadyPrompt = true;
}

void Delegate::openedge(bool, std::pair<int, int>) {
	prompt_set.clear();
	prompt_set.push_back("makechange graphic -p --set-edge $ immediate#");
	isReadyPrompt = true;

	isOpenEdge = false;
}


void Delegate::move(bool isDown, std::pair<int, int> coord) {
	if (foci.empty())	return;
	if (isDown && coord.first >= 150) {
		vertices.clear();
		vertices.push_back(coord);
	}
	else if (vertices.size() == 1) {
		prompt_set.clear();
		char prompt_str[640];
		sprintf(prompt_str, "let's go -p --disp [%d,%d] $ immediate#", 
			coord.first - vertices[0].first, coord.second - vertices[0].second);
		prompt_set.push_back(prompt_str);

		foci[0].second->move(std::pair<int,int>(coord.first - vertices[0].first, coord.second - vertices[0].second));

		isReadyPrompt = true;
		vertices.clear();
	}
}


void Delegate::scale(bool isDown, std::pair<int, int> coord) {
	if (foci.empty())	return;
	if (isDown && coord.first >= 150) {
		vertices.clear();
		vertices.push_back(coord);
	}
	else if (vertices.size() == 1) {
		auto&& centr = foci[0].second->centriod();
		std::pair<int, int> a(vertices[0].first - centr.first, vertices[0].second - centr.second),
			b(coord.first - centr.first, coord.second - centr.second);

		prompt_set.clear();
		char prompt_str[640];
		sprintf(prompt_str, "let's go -p --scale [%lf,%lf] $ immediate# ", 
			static_cast<double>(b.first) / a.first, static_cast<double>(b.second) / a.second);
		prompt_set.push_back(prompt_str);

		foci[0].second->scale(std::pair<double,double>(static_cast<double>(b.first) / a.first, static_cast<double>(b.second) / a.second));

		isReadyPrompt = true;
		vertices.clear();
	}
}


void Delegate::rotate(bool isDown, std::pair<int, int> coord) {
	if (foci.empty())	return;
	if (isDown && coord.first >= 150) {
		vertices.clear();
		vertices.push_back(coord);
	}
	else if (vertices.size() == 1) {
		auto&& centr = foci[0].second->centriod();
		std::pair<double, double> a(vertices[0].first - centr.first, vertices[0].second - centr.second),
			b(coord.first - centr.first, coord.second - centr.second);
		auto len_a(sqrt(a.first*a.first + a.second*a.second)), len_b(sqrt(b.first*b.first + b.second*b.second));
		a.first /= len_a;	a.second /= len_a;
		b.first /= len_b;	b.second /= len_b;

		double rad = acos(b.first) - acos(a.first);

		//double chk((a.first*a.first + a.second*a.second) * (b.first*b.first + b.second*b.second)), cgkt(a.first*b.first + a.second*b.second);

		prompt_set.clear();
		char prompt_str[640];
		sprintf(prompt_str, "let's go -p --rotate %lf $ immediate# ", rad);
		prompt_set.push_back(prompt_str);

		foci[0].second->rotate(rad);

		isReadyPrompt = true;
		vertices.clear();
	}
}


void Delegate::cut(bool isDown, std::pair<int, int> coord) {
	if (isDown)	vertices.push_back(coord);
	if (coord.first < 150) vertices.clear();
	else if (!isDown && vertices.size() == 1) {
		if (abs(vertices[0].first - coord.first) + abs(vertices[0].second - coord.second) < 30) {
			vertices.clear();
			isReadyPrompt = false;
			return;
		}

		prompt_set.clear();
		std::string _prompt = "get rid of clear-select# immediate#";

		std::pair<int, int> left_down, right_up;

		left_down.first = vertices[0].first < coord.first ? vertices[0].first : coord.first;
		left_down.second = vertices[0].second < coord.second ? vertices[0].second : coord.second;

		right_up.first = vertices[0].first > coord.first ? vertices[0].first : coord.first;
		right_up.second = vertices[0].second > coord.second ? vertices[0].second : coord.second;

		std::string V(" -v");
		char buf[32];
		sprintf(buf, " [%d,%d]", vertices[0].first, vertices[0].second);
		V += buf;
		sprintf(buf, " [%d,%d]", coord.first, coord.second);
		V += buf;
		V += " $";

		_prompt += V;
		prompt_set.push_back(_prompt);

		for each (auto&& var in foci) { delete var.second; }
		foci.clear();
		
		isReadyPrompt = true;
		vertices.clear();
	}
}


Delegate::~Delegate()
{
}
