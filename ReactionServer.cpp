#include "ReactionServer.h"
#include "GeometricLine.h"
#include "GeometricCircle.h"
#include "GeometricEllipse.h"
#include "StraightLine.h"
#include "EllipseRim.h"
#include "Graphic.h"
#include "Polygon.h"
#include "Typedef.h"
#include <cassert>
#include <iostream>


#define PROMPT_CMD(cmd) (prompt.substr(0, sizeof(cmd) + 1).find(cmd) != std::string::npos)

ReactionServer::ReactionServer()
{
}


ReactionServer::~ReactionServer()
{
}


void ReactionServer::operator()(std::string prompt) {
	// export: Output instances
	if (prompt.substr(0, sizeof("export --now ")).find("export --now") != std::string::npos) {
		isReady = true;
		return;
	}
	if (prompt.find("--immediate") != std::string::npos)
		isReady = true;
	else
		isReady = false;


	// -n: Name
	char buf[100];
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

	try {
		// import: New a Instance
		if (prompt.substr(0, sizeof("import --temp outline ")).find("import --temp outline") != std::string::npos)
			add_outlines(name, type, vertices, properties);
		else if (prompt.substr(0, sizeof("import --temp graphic ")).find("import --temp graphic") != std::string::npos)
			add_graphics(name, type, vertices, properties);

		// export: Drop a Instance
		else if (prompt.substr(0, sizeof("export --trash outline ")).find("import --trash outline") != std::string::npos)
			delete_graphics(name, properties);
		else if (prompt.substr(0, sizeof("export --trash graphic ")).find("import --trash graphic") != std::string::npos)
			delete_graphics(name, properties);
	}
	catch (std::string ex) {
		std::cerr << ex << std::endl;
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
		buffer_vertices.clear();
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
		if (properties.find("--UTTERMOST") != std::string::npos) {
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
		else if(properties.find("--SET-SEMIAXIS") != std::string::npos){
			if (points.size() != 1)	return false;
			auto stt = properties.find("--SET-SEMIAXIS");
			if (stt == std::string::npos)
				return false;
			buf.integer[0] = 1;
			buf.integer[1] = 1;
			buf.integer[2] = sscanf(properties.substr(stt).c_str(), "--SET-SEMIAXIS %d %d", &buf.integer[0], &buf.integer[1]);
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
	if (properties.find("--SET-COLOR") != std::string::npos) {
		if (sscanf(properties.substr(properties.find("--SET-COLOR")).c_str(), "--SET-COLOR [%f,%f,%f]", &color[0], &color[1], &color[2]) == 3)
			outline->setColor(color);
	}

	if (name.size() == 0)
		ans.outline = outline;
	else if (properties.find("--IDLE") != std::string::npos)
		Idle.outlines.insert(std::pair<std::string, Outline*>(name, outline));
	else
		Explicit.outlines.insert(std::pair<std::string, Outline*>(name, outline));
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
	if (properties.find("--HARD") != std::string::npos) {	delete ans.outline;	}
	return true;
}

bool ReactionServer::add_graphics(std::string name, std::string type, std::vector<std::pair<int, int>> points, std::string properties) {
	if (Explicit.outlines.find(name) != Explicit.outlines.end() || Idle.outlines.find(name) != Idle.outlines.end())
		throw std::string("Name already exists");
	Graphic* graphic = nullptr;
	
	cgeneratorlist_t cgeneratorlist;
	if (properties.find("--PAINT") != std::string::npos) {
		cgeneratorlist = buffer_cgenerators;
		buffer_cgenerators.clear();
	}

	auto color = graphic->getEdgeColor();
	if (properties.find("--SET-COLOR") != std::string::npos) {
		if (sscanf(properties.substr(properties.find("--SET-COLOR")).c_str(), "--SET-COLOR [%f,%f,%f]", &color[0], &color[1], &color[2]) == 3)
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
	if (properties.find("--DROP-EDGE") != std::string::npos)
		isEdgeVisible = false;

	if (isEdgeVisible)
		graphic->TurnOnEdgeVision();
	else
		graphic->TurnOffEdgeVision();

	if (name.size() == 0)
		ans.graphic = graphic;
	else if (properties.find("--IDLE") != std::string::npos)
		Idle.graphics.insert(std::pair<std::string, Graphic*>(name, graphic));
	else
		Explicit.graphics.insert(std::pair<std::string, Graphic*>(name, graphic));
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
	if (properties.find("--HARD") != std::string::npos) { delete ans.graphic; }
	return true;
}
