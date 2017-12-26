#pragma once
#include "Outline.h"
#include <algorithm>
class GeometricCircle;

class CircleRim :
	public Outline
{
public:
	CircleRim(GeometricCircle& description);
	~CircleRim();

	GeometricCircle getCircle() const;
	void setCircle(std::pair<int, int> centroid, int radius);

	std::vector<std::pair<int, int>> Vertices(Window& window_now) override;

protected:
	GeometricCircle* orignal;
	bool isComplete = false;
	std::vector<std::pair<int, int>> Trajectory;

	CircleRim(GeometricCircle* p_description);

	// during
	virtual void internal_FirstQuadrant_Upper();

	// post
	virtual void toQuadrant()
	{
		const int initSize = Trajectory.size();
		for (int i = 0; i < initSize; ++i)
			Trajectory.push_back(std::pair<int, int>(Trajectory[i].second, Trajectory[i].first));
	}

	void toEntireArc()
	{
		const int initSize = Trajectory.size();
		for (int i = 0; i < initSize; ++i) {
			Trajectory.push_back(std::pair<int, int>(Trajectory[i].first, -Trajectory[i].second));
			Trajectory.push_back(std::pair<int, int>(-Trajectory[i].first, Trajectory[i].second));
			Trajectory.push_back(std::pair<int, int>(-Trajectory[i].first, -Trajectory[i].second));
		}
	}

	void Relocation(std::pair<int, int> RelocatedCentroid)
	{
		std::for_each(Trajectory.begin(), Trajectory.end(), [RelocatedCentroid](std::pair<int,int> &element)
	{
		element.first += RelocatedCentroid.first;
		element.second += RelocatedCentroid.second;
	});
	}
};

