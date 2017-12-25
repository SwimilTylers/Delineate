#include "RectangleWindowRim.h"
#include <string>
#include "PolygonCutAlgorithm.h"


RectangleWindowRim::RectangleWindowRim(std::pair<int, int>& leftdown, std::pair<int, int>& rightup, 
	LineCutAlgorithm* line_cut_server, PolygonCutAlgorithm* polygon_cut_server):
	RectangleRim(leftdown, rightup)
{
#ifdef NULLPTRCHK
	if (line_cut_server == nullptr || polygon_cut_server == nullptr)
		throw std::string("cut server must be non-nullptr");
#endif
	this->line_cut_server = line_cut_server;
	this->polygon_cut_server = polygon_cut_server;
}


RectangleWindowRim::~RectangleWindowRim()
{
}

std::pair<std::pair<int, int>, std::pair<int, int>> RectangleWindowRim::CutLine(const GeometricLine& line) const
{
	return line_cut_server->LineCutKernel(line, *this);
}

std::vector<PolygonRim> RectangleWindowRim::PolygonCut(const PolygonRim& Cut) const
{
	return polygon_cut_server->PolygonCutKernel(Cut, *this);
}