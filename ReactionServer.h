#pragma once
#include <string>
#include <algorithm>
#include <map>
#include "Outline.h"
#include "Graphic.h"
#include "ServiceRoutine.h"
#include "RectangleWindowRim.h"
#include "Typedef.h"

class ReactionServer
{
public:
	ReactionServer();
	~ReactionServer();
	
	void operator()(std::string prompt);
	std::vector<Outline*> serializeOutline() {
		std::vector<Outline*> ret;
		std::for_each(Explicit.outlines.begin(), Explicit.outlines.end(), 
			[&ret](std::pair<std::string, Outline*> x) {ret.push_back(x.second); });
		return ret;
	}
	std::vector<Graphic*> serializeGraphic() {
		std::vector<Graphic*> ret;
		std::for_each(Explicit.graphics.begin(), Explicit.graphics.end(),
			[&ret](std::pair<std::string, Graphic*> x) {ret.push_back(x.second); });
		return ret;
	}
	bool isReadyToExport() const {
		return isReady;
	}
	void DisableIsReady() {
		isReady = false;
	}

private:
	std::map<std::string, ServiceRoutine*> service_routines;
	bool isReady = false;

	std::vector<std::pair<int, int>> buffer_vertices;
	cgeneratorlist_t buffer_cgenerators;

	LineCutAlgorithm* line_cut_server;
	PolygonCutAlgorithm* polygon_rim_cut_server;

	struct {
		Outline* outline = nullptr;
		Graphic* graphic = nullptr;
		RectangleWindowRim* CutWindow = nullptr;
	} ans;

	struct
	{
		struct {
			Outline* ptr = nullptr;
			bool isAns, isIdle;
			std::string name;
		} outline;
		struct {
			Graphic* ptr = nullptr;
			bool isAns, isIdle;
			std::string name;
		} graphic;
	} selected;

	struct {
		std::map<std::string, Outline*> outlines;
		std::map<std::string, Graphic*> graphics;
	} Explicit;

	struct {
		std::map<std::string, Outline*> outlines;
		std::map<std::string, Graphic*> graphics;
	} Idle;

	bool add_outlines(std::string name, std::string type, std::vector<std::pair<int, int>> points, std::string properties);
	bool delete_outlines(std::string name, std::string properties);

	bool add_graphics(std::string name, std::string type, std::vector<std::pair<int, int>> points, std::string properties);
	bool delete_graphics(std::string name, std::string properties);

	bool select_outline(std::string name);
	bool select_graphic(std::string name);

	bool record_vertices(std::vector<std::pair<int, int>> vertices) {
		buffer_vertices.insert(buffer_vertices.end(), vertices.begin(), vertices.end());
		return true;
	}
	bool record_cgenerator(std::string type, std::vector<std::pair<int, int>> vertices, std::string properties);

	bool go(std::string name, std::string properties);
	bool rid(std::vector<std::pair<int, int>> vertices);

	bool makechange_outline(std::string name, std::string properties);
	bool makechange_graphics(std::string name, std::string properties);

	bool store_outline(std::string name, std::string properties);
	bool store_graphic(std::string name, std::string properties);
};