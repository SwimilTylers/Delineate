#pragma once
#include "Outline.h"
#include "StraightLine.h"

class PolygonRim :
	public Outline
{
public:
	explicit PolygonRim(std::vector<std::pair<std::pair<int,int>,std::pair<int,int>>> vertex_pairs);
	virtual ~PolygonRim();
	std::vector<std::pair<int, int>> Vertices(Window& window_now) override;
	std::vector<StraightLine> getEdge() const;

	
	std::vector<std::pair<int,int>> getApexes() const
	{
		return vertices;
	}


	class OELServer
	{
	public:
		OELServer(const std::vector<double>& gradients, 
			const std::vector<std::pair<int, GeometricLine::ScanBucket>>& scanbackets);
		~OELServer();
		std::vector<std::vector<GeometricLine::ScanBucket>>& get_ordered_edge_list();
		std::pair<int, int>& getRangeY()
		{
			return RangeY;
		}

	private:
		std::pair<int, int> RangeY;
		std::vector<std::vector<GeometricLine::ScanBucket>> ordered_edge_list;
	};


	OELServer& DeployOEL() const
	{
		return *(new OELServer(OELBackups.CorrespondingGradients, OELBackups.ScanBacketStack));
	}


protected:
	std::vector<StraightLine> edges;
	std::vector<std::pair<int, int>> vertices;
	std::vector<StraightLine>& compatibility(Window& window);
	bool not_collide(Window& window);

	bool isComplete = false;
	std::vector<std::pair<int, int>> Trajectory;
	

	struct
	{
		std::vector<std::pair<int, GeometricLine::ScanBucket>> ScanBacketStack;
		std::vector<double> CorrespondingGradients;
	}OELBackups;
	
};

