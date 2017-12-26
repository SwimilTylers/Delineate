#pragma once
#include <string>
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

	struct {
		Outline* outline = nullptr;
		Graphic* graphic = nullptr;
		RectangleWindowRim* CutWindow = nullptr;
	} ans;

	struct {
		Outline* outline = nullptr;
		Graphic* graphic = nullptr;
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
};

