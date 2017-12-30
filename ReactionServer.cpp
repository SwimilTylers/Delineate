#include "ReactionServer.h"
#include "GeometricLine.h"
#include "GeometricCircle.h"
#include "GeometricEllipse.h"
#include "StraightLine.h"
#include "EllipseRim.h"
#include "CircleRim.h"
#include "Graphic.h"
#include "Polygon.h"
#include "Typedef.h"
#include <cassert>
#include <iostream>
#include <algorithm>

#define PROMPT_CMD(cmd) (prompt.substr(0, sizeof(cmd) + 1).find(cmd) != std::string::npos)

ReactionServer::ReactionServer()
{
}


ReactionServer::~ReactionServer()
{
}


void ReactionServer::operator()(std::string prompt) {
	// -n: Name
	if (prompt.empty())	return;
	char buf[640];
	std::string name;
	auto mark = prompt.find("-n ");
	if (mark != std::string::npos) {
		if (sscanf(prompt.substr(mark + 2).c_str(), " %s", buf) == 1) {
			name = buf;
		}
	}

	// -t: Type
	std::string type;
	mark = prompt.find("-t ");
	if (mark != std::string::npos) {
		if (sscanf(prompt.substr(mark + 2).c_str(), " %s", buf) == 1)
			type = buf;
	}

	// -v ... $: Vertices
	std::vector<std::pair<int, int>> vertices;
	int tensor[2];
	mark = prompt.find("-v ");
	if (mark != std::string::npos) {
		strcpy_s(buf, prompt.substr(mark + 3, prompt.find("$", mark)).c_str());
		auto needle = strtok(buf, " ");
		while (needle != nullptr) {
			if (sscanf(needle, "[%d,%d]", &tensor[0], &tensor[1]) != 2)
				break;
			vertices.push_back(std::pair<int, int>(tensor[0], tensor[1]));
			needle = strtok(NULL, " ");
		}
	}

	// -p ... $: Properties
	mark = prompt.find("-p ");
	std::string properties;
	if (mark != std::string::npos) {
		properties = prompt.substr(mark + 3, prompt.find("$", mark));
	}


	if (prompt.find("@clear-select") != std::string::npos) {
		selected.outline.ptr = nullptr;
		selected.graphic.ptr = nullptr;
	}

	if (prompt.find("@clear-ans") != std::string::npos) {
		if (ans.outline != nullptr)	delete ans.outline;
		if (ans.graphic != nullptr)	delete ans.graphic;
		if (ans.CutWindow != nullptr) delete ans.CutWindow;

		if (selected.graphic.isAns)	selected.graphic.ptr = nullptr;
		if (selected.outline.isAns)	selected.outline.ptr = nullptr;

		ans.outline = nullptr;
		ans.graphic = nullptr;
		ans.CutWindow = nullptr;
	}

	if (prompt.find("@release-points") != std::string::npos) {
		buffer_vertices.clear();
	}
	if (prompt.find("@release-cgs") != std::string::npos) {
		buffer_cgenerators.clear();
	}
	if (prompt.find("@release-all") != std::string::npos) {
		buffer_vertices.clear();
		buffer_cgenerators.clear();
	}


	try {
		// import: New a Instance
		if (PROMPT_CMD("import temp outline"))
			add_outlines(name, type, vertices, properties);
		else if (PROMPT_CMD("import temp graphic"))
			add_graphics(name, type, vertices, properties);

		// export: Drop a Instance
		else if (PROMPT_CMD("export now")) {
			isReady = true;
		}
		else if (PROMPT_CMD("export trash Explicit")) {
			Explicit.outlines.clear();
			Explicit.graphics.clear();

			if (!selected.graphic.isAns && !selected.graphic.isIdle)	selected.graphic.ptr = nullptr;
			if (!selected.outline.isAns && !selected.outline.isIdle) selected.outline.ptr = nullptr;
		}
		else if (PROMPT_CMD("export trash Idle")) {
			Idle.outlines.clear();
			Idle.graphics.clear();

			if (selected.graphic.isIdle)	selected.graphic.ptr = nullptr;
			if (selected.outline.isIdle) selected.outline.ptr = nullptr;
		}
		else if (PROMPT_CMD("export trash outline"))
			delete_outlines(name, properties);
		else if (PROMPT_CMD("export trash graphic"))
			delete_graphics(name, properties);

		// select: select a Instance
		else if (PROMPT_CMD("select outline"))
			select_outline(name);
		else if (PROMPT_CMD("select graphic"))
			select_graphic(name);

		// ease: unselect, or idle
		else if (PROMPT_CMD("ease outline"))
			selected.outline.ptr = nullptr;
		else if (PROMPT_CMD("ease graphic"))
			selected.graphic.ptr = nullptr;
		else if (PROMPT_CMD("at ease"));

		// record: set buffers
		else if (PROMPT_CMD("record points"))
			record_vertices(vertices);
		else if (PROMPT_CMD("record cgs"))
			record_cgenerator(type, vertices, properties);

		// go: rotate, rescale or move a graphic
		else if (PROMPT_CMD("let's go"))
			go(name, properties);

		// makechange
		else if (PROMPT_CMD("makechange outline"))
			makechange_outline(name, properties);
		else if (PROMPT_CMD("makechange graphic"))
			makechange_graphics(name, properties);

		// store: store ans
		else if (PROMPT_CMD("store outline"))
			store_outline(name, properties);
		else if (PROMPT_CMD("store graphic"))
			store_graphic(name, properties);

		// ILLEGAL COMMANDS
		else {
			std::cerr << "[!] Illegal Commands" << std::endl;
			std::cerr << "[!] @pre-option has already worked, while post-option# and cmd is denied" << std::endl;
			std::cerr << "[!] This feature is not safe, send prompt cmd \'at ease @pre-option-lock=1\' to ban pre-option excluding \'at ease\'" << std::endl;
			return;
		}
	}
	catch (std::string ex) {
		std::cerr << ex << std::endl;
	}

	if (prompt.find("immediate#") != std::string::npos)
		isReady = true;

	if (prompt.find("clear-select#") != std::string::npos) {
		selected.outline.ptr = nullptr;
		selected.graphic.ptr = nullptr;
	}

	if (prompt.find("clear-ans#") != std::string::npos) {
		if (ans.outline != nullptr)	delete ans.outline;
		if (ans.graphic != nullptr)	delete ans.graphic;
		if (ans.CutWindow != nullptr) delete ans.CutWindow;

		if (selected.graphic.isAns)	selected.graphic.ptr = nullptr;
		if (selected.outline.isAns)	selected.outline.ptr = nullptr;

		ans.outline = nullptr;
		ans.graphic = nullptr;
		ans.CutWindow = nullptr;
	}

	if (prompt.find("release-points#") != std::string::npos) {
		buffer_vertices.clear();
	}
	if (prompt.find("release-cgs#") != std::string::npos) {
		buffer_cgenerators.clear();
	}
	if (prompt.find("release-all#") != std::string::npos) {
		buffer_vertices.clear();
		buffer_cgenerators.clear();
	}
}

bool ReactionServer::add_outlines(std::string name, std::string type, std::vector<std::pair<int,int>> points, std::string properties) {
	if (Explicit.outlines.find(name) != Explicit.outlines.end() || Idle.outlines.find(name) != Idle.outlines.end())
		throw std::string("Name already exists");
	Outline* outline = nullptr;
	union {
		GeometricLine* line;
		GeometricCircle* circle;
		GeometricEllipse* ellipse;
		int integer[16];
	}buf;

	if (points.size() == 0) {
		points = buffer_vertices;
	}

	if (type.size() == 0)
		type = "Polygon";

	switch (type[0])
	{
	case 'L':
		if (points.size() != 2)	return false;
		buf.line = new GeometricLine(points[0], points[1]);
		outline = new StraightLine(*buf.line);
		delete buf.line;
		break;
	case 'E':
		if (properties.find("--uttermost") != std::string::npos) {
			if (points.size() != 2)	return false;
			if (abs(points[0].first - points[1].first) == abs(points[0].second - points[1].second)) {
				buf.circle = new GeometricCircle(std::pair<int, int>((points[0].first + points[1].first) / 2, (points[0].second + points[1].second) / 2),
					abs(points[0].first - points[1].first) / 2);
				outline = new CircleRim(*buf.circle);
				delete buf.circle;
			}
			else {
				buf.ellipse = new GeometricEllipse(std::pair<int, int>((points[0].first + points[1].first) / 2, (points[0].second + points[1].second) / 2),
					abs(points[0].first - points[1].first) / 2,
					abs(points[0].second - points[1].second) / 2);
				outline = new EllipseRim(*buf.ellipse);
				delete buf.ellipse;
			}
		}
		else if(properties.find("--set-semiaxis") != std::string::npos){
			if (points.size() != 1)	return false;
			auto stt = properties.find("--set-semiaxis");
			if (stt == std::string::npos)
				return false;
			buf.integer[0] = 1;
			buf.integer[1] = 1;
			buf.integer[2] = sscanf(properties.substr(stt).c_str(), "--set-semiaxis %d %d", &buf.integer[0], &buf.integer[1]);
			assert(buf.integer[2] == 2);
			if (buf.integer[0] != buf.integer[1]) {
				buf.ellipse = new GeometricEllipse(points[0], buf.integer[0], buf.integer[1]);
				outline = new EllipseRim(*buf.ellipse);
				delete buf.ellipse;
			}
			else {
				buf.circle = new GeometricCircle(points[0], buf.integer[0]);
				outline = new CircleRim(*buf.circle);
				delete buf.circle;
			}
		}
		else throw std::string("Lack parameter for Ellipse");
		break;
	case 'P':
		if (points.size() < 2)	return false;
		if (points.size() == 2) {
			buf.integer[0] = points[0].first < points[1].first ? points[0].first : points[1].first;
			buf.integer[1] = points[0].second < points[1].second ? points[0].second : points[1].second;

			buf.integer[2] = points[0].first > points[1].first ? points[0].first : points[1].first;
			buf.integer[3] = points[0].second > points[1].second ? points[0].second : points[1].second;

			outline = new RectangleRim(std::pair<int, int>(buf.integer[0], buf.integer[1]), std::pair<int, int>(buf.integer[2], buf.integer[3]));
		}
		else
			outline = new PolygonRim(PolygonRims().getNewRim(points));
		break;
	default:
		throw std::string("Improper type assignment. For outlines: -t [L(ine)/E(llipse)/P(olygon)]");
	}

	auto color = outline->getColor();
	if (properties.find("--set-color") != std::string::npos) {
		if (sscanf(properties.substr(properties.find("--set-color")).c_str(), "--set-color [%f,%f,%f]", &color[0], &color[1], &color[2]) == 3)
			outline->setColor(color);
	}


	if (properties.find("--duplicated-graphic") != std::string::npos && type[0] == 'P') {
		cgeneratorlist_t cgs;
		Polygon* graphic = new Polygon(*static_cast<PolygonRim*>(outline), color, cgs);
		if (ans.graphic != nullptr)	delete ans.graphic;
		ans.graphic = graphic;
		selected.graphic.ptr = graphic;
		selected.graphic.isAns = true;
		selected.graphic.isIdle = false;
	}


	if (name.size() == 0) {
		if (properties.find("--focus") != std::string::npos) {
			selected.outline.ptr = outline;
			selected.outline.isAns = true;
			selected.outline.isIdle = false;
			selected.outline.name = std::string();
		}
		ans.outline = outline;
	}
	else if (properties.find("--idle") != std::string::npos) {
		Idle.outlines.insert(std::pair<std::string, Outline*>(name, outline));
		if (properties.find("--focus") != std::string::npos) {
			selected.outline.ptr = outline;
			selected.outline.isAns = false;
			selected.outline.isIdle = true;
			selected.outline.name = name;
		}
	}
	else {
		Explicit.outlines.insert(std::pair<std::string, Outline*>(name, outline));
		if (properties.find("--focus") != std::string::npos) {
			selected.outline.ptr = outline;
			selected.outline.isAns = false;
			selected.outline.isIdle = false;
			selected.outline.name = name;
		}
	}


	return true;
}

bool ReactionServer::delete_outlines(std::string name, std::string properties) {
	auto&& iter = Explicit.outlines.find(name);
	if (iter == Explicit.outlines.end()) {
		iter = Idle.outlines.find(name);
		if (iter == Idle.outlines.end())
			return false;
		delete iter->second;
		Idle.outlines.erase(iter);
		return true;
	}
	if (ans.outline != nullptr)
		delete ans.outline;
	ans.outline =  iter->second;
	Explicit.outlines.erase(iter);
	if (properties.find("--hard") != std::string::npos) { delete ans.outline;	ans.outline = nullptr; }
	if (selected.outline.name == name)	selected.outline.ptr = nullptr;
	return true;
}

bool ReactionServer::add_graphics(std::string name, std::string type, std::vector<std::pair<int, int>> points, std::string properties) {
	if (Explicit.outlines.find(name) != Explicit.outlines.end() || Idle.outlines.find(name) != Idle.outlines.end())
		throw std::string("Name already exists");
	Graphic* graphic = nullptr;
	
	cgeneratorlist_t cgeneratorlist;
	if (properties.find("--paint") != std::string::npos) {
		cgeneratorlist.insert(cgeneratorlist.end(), buffer_cgenerators.begin(), buffer_cgenerators.end());
	}

	pencolor_t color(3, 0);
	if (properties.find("--set-color") != std::string::npos) {
		if (sscanf(properties.substr(properties.find("--set-color")).c_str(), "--set-color [%f,%f,%f]", &color[0], &color[1], &color[2]) == 3)
			graphic->setEdgeColor(color);
	}

	if (type.size() == 0)
		type = "Polygon";

	switch (type[0])
	{
	case 'P':	graphic = new Polygon(Polygons().getNewPolygon(color, cgeneratorlist, points)); break;
	default:
		throw std::string("Improper type assignment. For graphics: -t [P(olygon)]");
			break;
	}


	bool isEdgeVisible = true;
	if (properties.find("--drop-edge") != std::string::npos)
		isEdgeVisible = false;

	if (isEdgeVisible)
		graphic->TurnOnEdgeVision();
	else
		graphic->TurnOffEdgeVision();

	if (name.size() == 0) {
		if (properties.find("--focus") != std::string::npos) {
			selected.graphic.ptr = graphic;
			selected.graphic.isAns = true;
			selected.graphic.isIdle = false;
			selected.graphic.name = std::string();
		}
		ans.graphic = graphic;
	}
	else if (properties.find("--idle") != std::string::npos) {
		Idle.graphics.insert(std::pair<std::string, Graphic*>(name, graphic));
		if (properties.find("--focus") != std::string::npos) {
			selected.graphic.ptr = graphic;
			selected.graphic.isAns = false;
			selected.graphic.isIdle = true;
			selected.graphic.name = name;
		}
	}
	else {
		Explicit.graphics.insert(std::pair<std::string, Graphic*>(name, graphic));
		if (properties.find("--focus") != std::string::npos) {
			selected.graphic.ptr = graphic;
			selected.graphic.isAns = false;
			selected.graphic.isIdle = false;
			selected.graphic.name = name;
		}
	}
	return true;
}

bool ReactionServer::delete_graphics(std::string name, std::string properties) {
	auto&& iter = Explicit.graphics.find(name);
	if (iter == Explicit.graphics.end()) {
		iter = Idle.graphics.find(name);
		if (iter == Idle.graphics.end())
			return false;
		delete iter->second;
		Idle.graphics.erase(iter);
		return true;
	}
	if (ans.graphic != nullptr)
		delete ans.graphic;
 	ans.graphic = iter->second;
	Explicit.graphics.erase(iter);
	if (properties.find("--hard") != std::string::npos) { delete ans.graphic; ans.graphic = nullptr; }
	if (selected.graphic.name == name)	selected.graphic.ptr = nullptr;
	return true;
}


bool ReactionServer::select_outline(std::string name) {
	if (Explicit.outlines.find(name) != Explicit.outlines.end()) {
		selected.outline.ptr = Explicit.outlines.find(name)->second;
		selected.outline.name = name;
		selected.outline.isAns = false;
		selected.outline.isIdle = false;
		return true;
	}
	else if (Idle.outlines.find(name) != Idle.outlines.end()) {
		selected.outline.ptr = Idle.outlines.find(name)->second;
		selected.outline.name = name;
		selected.outline.isAns = false;
		selected.outline.isIdle = true;
		return true;
	}
	throw std::string("Name not exists");
}

bool ReactionServer::select_graphic(std::string name) {
	if (Explicit.graphics.find(name) != Explicit.graphics.end()) {
		selected.graphic.ptr = Explicit.graphics.find(name)->second;
		selected.graphic.name = name;
		selected.graphic.isAns = false;
		selected.graphic.isIdle = false;
		return true;
	}
	else if (Idle.graphics.find(name) != Idle.graphics.end()) {
		selected.graphic.ptr = Idle.graphics.find(name)->second;
		selected.graphic.name = name;
		selected.graphic.isAns = false;
		selected.graphic.isIdle = true;
		return true;
	}
	throw std::string("Name not exists");
}

bool ReactionServer::record_cgenerator(std::string type, std::vector<std::pair<int, int>> vertices, std::string properties) {
	if (vertices.size() == 0 || type.find("together") != std::string::npos)
		vertices.insert(vertices.end(), buffer_vertices.begin(), buffer_vertices.end());

	pencolor_t color;
	color.resize(3, 0);
	if (properties.find("--set-color") != std::string::npos) {
		if (sscanf(properties.substr(properties.find("--set-color")).c_str(), "--set-color [%f,%f,%f]", &color[0], &color[1], &color[2]) != 3)
			color.resize(3, 0);
	}

	
	auto& cg = buffer_cgenerators;
	
	std::for_each(vertices.begin(), vertices.end(), [&cg, &color](std::pair<int, int>& x) {
		cg.push_back(std::pair<std::pair<int, int>, pencolor_t>(x, color)); 
	});
	

	return true;
}

bool ReactionServer::go(std::string name, std::string properties) {
	if (name.size() != 0)
		select_graphic(name);

	if (selected.graphic.ptr == nullptr)	throw std::string("not selected");

	double rad = 0;
	auto mark = properties.find("--rotate");
	if (mark != std::string::npos) {
		sscanf(properties.substr(mark).c_str(), "--rotate %lf", &rad);
	}

	std::pair<double, double> scale(1, 1);
	double scalebuf[2];
	mark = properties.find("--scale");
	if (mark != std::string::npos) {
		if (sscanf(properties.substr(mark).c_str(), "--scale [%lf,%lf]", &scalebuf[0], &scalebuf[1]) == 2) {
			scale.first = scalebuf[0] > 0 ? scalebuf[0] : 1;
			scale.second = scalebuf[1] > 0 ? scalebuf[1] : 1;
		}
	}

	std::pair<int, int> disp(0, 0);
	mark = properties.find("--disp");
	if (mark != std::string::npos) {
		if (sscanf(properties.substr(mark).c_str(), "--disp [%d,%d]", &disp.first, &disp.second) != 2) {
			disp.first = 0;
			disp.second = 0;
		}
	}

	Graphic* graphic = new Polygon(Polygons().getManipulatedNewPolygon(*(static_cast<Polygon*>(selected.graphic.ptr)), disp, scale, rad));
	if (selected.graphic.ptr->EdgeVision())
		graphic->TurnOnEdgeVision();
	else graphic->TurnOffEdgeVision();

	char namebuf[32] = { 0 };
	mark = properties.find("--save-as");
	if (mark != std::string::npos) {
		sscanf(properties.substr(mark).c_str(), "--save-as %s", namebuf);
		name = namebuf;
		if (name.size() == 0) {
			if (ans.graphic != nullptr)	delete ans.graphic;
			ans.graphic = graphic;
			throw std::string("Cannot read save-as's name, save as \'ans\'");
		}
		if (Explicit.outlines.find(name) != Explicit.outlines.end() || Idle.outlines.find(name) != Idle.outlines.end()) {
			if (ans.graphic != nullptr)	delete ans.graphic;
			ans.graphic = graphic;
			throw std::string("Name already exists, save as \'ans\'");
		}
		if (properties.find("--idle") != std::string::npos)
			Idle.graphics.insert(std::pair<std::string, Graphic*>(name, graphic));
		else
			Explicit.graphics.insert(std::pair<std::string, Graphic*>(name, graphic));
		return true;
	}

	mark = properties.find("--temp");
	if (mark != std::string::npos) {
		if (ans.graphic != nullptr)	delete ans.graphic;
		ans.graphic = graphic;
		return true;
	}

	if (selected.graphic.isAns) {
		if (ans.graphic != nullptr)	delete ans.graphic;
		ans.graphic = graphic;
		return true;
	}
	else if (selected.graphic.isIdle) {
		auto iter = Idle.graphics.find(selected.graphic.name);
		if (iter == Idle.graphics.end())	throw std::string("consistancy leak");
		delete iter->second;
		iter->second = graphic;
		selected.graphic.ptr = graphic;
		return true;
	}
	else {
		auto iter = Explicit.graphics.find(selected.graphic.name);
		if (iter == Explicit.graphics.end())	throw std::string("consistancy leak");
		delete iter->second;
		iter->second = graphic;
		selected.graphic.ptr = graphic;
		return true;
	}
}

bool ReactionServer::makechange_outline(std::string name, std::string properties) {
	if (name.size() != 0)
		select_outline(name);

	if (selected.outline.ptr == nullptr)	throw std::string("not selected");

	pencolor_t color(3, 0);
	auto mark = properties.find("--set-color");
	if (mark != std::string::npos) {
		if (properties.find("--set-color default"), mark, sizeof("--set-color default")) {
			selected.outline.ptr->setColor(color);
		}
		if (sscanf(properties.substr(mark).c_str(), "--set-color [%f,%f,%f]", &color[0], &color[1], &color[2]) == 3)
			selected.outline.ptr->setColor(color);
	}

	if (properties.find("--explicit") != std::string::npos && (selected.outline.isIdle || selected.outline.isAns)) {
		selected.outline.isIdle = false;
		selected.outline.isAns = false;
		Explicit.outlines.insert(std::pair<std::string, Outline*>(selected.outline.name, selected.outline.ptr));
		if (selected.outline.isAns) {
			selected.outline.isAns = false;
			ans.outline = nullptr;
		}
		else {
			Idle.outlines.erase(selected.outline.name);
		}
	}
	else if (properties.find("--idle") != std::string::npos && !selected.outline.isIdle) {
		selected.outline.isIdle = true;
		Idle.outlines.insert(std::pair<std::string, Outline*>(selected.outline.name, selected.outline.ptr));
		if (selected.outline.isAns) {
			selected.outline.isAns = false;
			ans.outline = nullptr;
		}
		else {
			Explicit.outlines.erase(selected.outline.name);
		}
	}

	return true;
}

bool ReactionServer::makechange_graphics(std::string name, std::string properties) {
	if (name.size() != 0)
		select_graphic(name);

	if (selected.graphic.ptr == nullptr)	throw std::string("not selected");

	auto mark = properties.find("--paint");
	if (mark != std::string::npos) {
		if (properties.find("--paint app") != std::string::npos) {
			auto cgeneratorlist = selected.graphic.ptr->getCGenerators();
			cgeneratorlist.insert(cgeneratorlist.end(), buffer_cgenerators.begin(), buffer_cgenerators.end());
			selected.graphic.ptr->setCGenerators(cgeneratorlist);
		}
		else if (properties.find("--paint default") != std::string::npos) {
			cgeneratorlist_t cgeneratorlist;
			selected.graphic.ptr->setCGenerators(cgeneratorlist);
		}
		else if (properties.find("--paint replace") != std::string::npos) {
			selected.graphic.ptr->setCGenerators(buffer_cgenerators);
		}
	}

	pencolor_t color(3, 0);
	mark = properties.find("--set-color");
	if (mark != std::string::npos) {
		if (properties.find("--set-color default") != std::string::npos) {
			selected.graphic.ptr->setEdgeColor(color);
		}
		else if (sscanf(properties.substr(mark).c_str(), "--set-color [%f,%f,%f]", &color[0], &color[1], &color[2]) == 3)
			selected.graphic.ptr->setEdgeColor(color);
	}

	if (properties.find("--set-edge") != std::string::npos)
		selected.graphic.ptr->TurnOnEdgeVision();
	else if (properties.find("--drop-edge") != std::string::npos)
		selected.graphic.ptr->TurnOffEdgeVision();

	if (properties.find("--explicit") != std::string::npos && (selected.graphic.isIdle || selected.graphic.isAns)) {
		selected.graphic.isIdle = false;
		selected.graphic.isAns = false;
		Explicit.graphics.insert(std::pair<std::string, Graphic*>(selected.graphic.name, selected.graphic.ptr));
		if (selected.graphic.isAns) {
			selected.graphic.isAns = false;
			ans.graphic = nullptr;
		}
		else {
			Idle.graphics.erase(selected.graphic.name);
		}
	}else if (properties.find("--idle") != std::string::npos && !selected.graphic.isIdle) {
		selected.graphic.isIdle = true;
		Idle.graphics.insert(std::pair<std::string, Graphic*>(selected.graphic.name, selected.graphic.ptr));
		if (selected.graphic.isAns) {
			selected.graphic.isAns = false;
			ans.graphic = nullptr;
		}
		else {
			Explicit.graphics.erase(selected.graphic.name);
		}
	}

	return true;
}

bool ReactionServer::store_outline(std::string name, std::string properties) {
	if (ans.outline == nullptr)	throw std::string("empty ans.outline");
	if (name.size() == 0)throw std::string("empty name");

	auto outline = ans.outline;

	if (properties.find("--idle") != std::string::npos) {
		Idle.outlines.insert(std::pair<std::string, Outline*>(name, outline));
		if (properties.find("--focus") != std::string::npos) {
			selected.outline.ptr = outline;
			selected.outline.isAns = false;
			selected.outline.isIdle = true;
			selected.outline.name = name;
		}
	}
	else {
		Explicit.outlines.insert(std::pair<std::string, Outline*>(name, outline));
		if (properties.find("--focus") != std::string::npos) {
			selected.outline.ptr = outline;
			selected.outline.isAns = false;
			selected.outline.isIdle = false;
			selected.outline.name = name;
		}
	}

	ans.outline = nullptr;
	return true;
}

bool ReactionServer::store_graphic(std::string name, std::string properties) {
	if (ans.graphic == nullptr)	throw std::string("empty ans.graphic");
	if (name.size() == 0)throw std::string("empty name");

	auto graphic = ans.graphic;

	if (properties.find("--idle") != std::string::npos) {
		Idle.graphics.insert(std::pair<std::string, Graphic*>(name, graphic));
		if (properties.find("--focus") != std::string::npos) {
			selected.graphic.ptr = graphic;
			selected.graphic.isAns = false;
			selected.graphic.isIdle = true;
			selected.graphic.name = name;
		}
	}
	else {
		Explicit.graphics.insert(std::pair<std::string, Graphic*>(name, graphic));
		if (properties.find("--focus") != std::string::npos) {
			selected.graphic.ptr = graphic;
			selected.graphic.isAns = false;
			selected.graphic.isIdle = false;
			selected.graphic.name = name;
		}
	}

	ans.graphic = nullptr;
	return true;
}
