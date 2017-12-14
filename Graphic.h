#pragma once
#include "Window.h"
#include <vector>
#include "Outline.h"
#include "StraightLine.h"
#include "RectangleRim.h"

class Graphic
{
public:
	Graphic(RectangleRim& uttermost, Outline* Rim, std::vector<float>& RimColor, std::vector<std::pair<std::pair<int,int>, std::vector<float>>>& CGenerators);
	virtual ~Graphic();
	virtual std::vector<std::pair<int,int>> EdgeVertices(Window& window)
	{
		if (visible_edge)
			return Rim.profile->Vertices(window);
		else
			return std::vector<std::pair<int, int>>();
	}
	std::vector<float> getEdgeColor() const;
	
	std::vector<std::pair<std::pair<int, int>, std::vector<float>>>& getCGenerators()
	{
		return CGenerators;
	}
	std::vector<std::vector<CGeneratorBarrier*>>& getCGProfile()
	{
		if(CGeneratorProfile.empty()) generateCGProfile();
		return CGeneratorProfile;
	}
	RectangleRim& getUttermost()
	{
		return uttermost;
	}

	virtual std::pair<int, int>& getRangeY() = 0;

	void TurnOnEdgeVision() { visible_edge = true; }
	void TurnOffEdgeVision() { visible_edge = false; }

protected:
	
	bool visible_edge = true;
	RectangleRim uttermost;
	
	struct
	{
		Outline* profile;
		std::vector<float> color;
	}Rim;

	std::vector<std::pair<std::pair<int, int>, std::vector<float>>> CGenerators;
	std::vector<std::vector<CGeneratorBarrier*>> CGeneratorProfile;
	virtual void generateCGProfile() = 0;
};

