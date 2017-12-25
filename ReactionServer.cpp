#include "ReactionServer.h"
#include "GeometricLine.h"
#include "GeometricCircle.h"
#include "GeometricEllipse.h"
#include "StraightLine.h"
#include "EllipseRim.h"
#include <cassert>
#include <iostream>


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
	int chk = sscanf(prompt.substr(prompt.find("-n ") + 2).c_str(), " %s", buf);
	assert(chk == 1);
	std::string name(buf);

	// -t: Type
	//auto strchk = prompt.substr(prompt.find("-t ") + 2);
	chk = sscanf(prompt.substr(prompt.find("-t ") + 2).c_str(), " %s", buf);
	assert(chk == 1);
	std::string type(buf);

	// -v ... $: Vertices
	std::vector<std::pair<int, int>> vertices;
	int tensor[2];
	auto mark = prompt.find("-v ");
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


	// import: New a Instance
	if (prompt.substr(0, sizeof("import --temp outline ")).find("import --temp outline") != std::string::npos)
		if (!add_outlines(name, type, vertices, properties))
			std::cerr << "...FAILED!" << std::endl;
		else
			std::clog << "...DONE!" << std::endl;
}

bool ReactionServer::add_outlines(std::string name, std::string type, std::vector<std::pair<int,int>> points, std::string properties) {
	if (Explicit.outlines.find(name) != Explicit.outlines.end() || Idle.outlines.find(name) != Idle.outlines.end())
		return false;
	Outline* outline = nullptr;
	union {
		GeometricLine* line;
		GeometricCircle* circle;
		GeometricEllipse* ellipse;
		int integer[16];
	}buf;

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
			buf.ellipse = new GeometricEllipse(std::pair<int, int>((points[0].first + points[1].first) / 2, (points[0].second + points[1].second) / 2),
				abs(points[0].first - points[1].first) / 2,
				abs(points[0].second - points[1].second) / 2);
		}
		else {
			if (points.size() != 1)	return false;
			auto stt = properties.find("--SET-SEMIAXIS");
			if (stt == std::string::npos)
				return false;
			buf.integer[0] = 0;
			buf.integer[1] = 1;
			buf.integer[2] = sscanf(properties.substr(stt).c_str(), "--SET-SEMIAXIS %d %d", &buf.integer[0], &buf.integer[1]);
			assert(buf.integer[2] == 2);
			buf.ellipse = new GeometricEllipse(points[0], buf.integer[0], buf.integer[1]);
		}
		outline = new EllipseRim(*buf.ellipse);
		delete buf.ellipse;
		break;
	case 'P':
		if (points.size() < 3)	return false;
		outline = new PolygonRim(PolygonRims().getNewRim(points));
	default:
		return false;
	}
	if (properties.find("--IDLE ") != std::string::npos || properties.find("-i ") != std::string::npos)
		Idle.outlines.insert(std::pair<std::string, Outline*>(name, outline));
	else
		Explicit.outlines.insert(std::pair<std::string, Outline*>(name, outline));
	return true;
}

bool ReactionServer::delete_outlines(std::string name) {
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
	return true;
}

bool ReactionServer::add_graphics(std::string name, std::string type, std::vector<std::pair<int, int>> points, std::string properties) {
	bool isEdgeVisible = true;
	if (properties.find("--INVISIBLE-EDGE") != std::string::npos || properties.find("-I ") != std::string::npos)
		isEdgeVisible = false;
	return false;
}

bool ReactionServer::delete_graphics(std::string name) {
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
	return true;
}
