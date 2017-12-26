#include "CircleRim.h"
#include "GeometricCircle.h"


CircleRim::CircleRim(GeometricCircle& description)
{
	orignal = new GeometricCircle(description);
}


CircleRim::CircleRim(GeometricCircle* description)
{
	orignal = description;
}


CircleRim::~CircleRim()
{
}

GeometricCircle CircleRim::getCircle() const
{
	return *orignal;
}

void CircleRim::setCircle(const std::pair<int, int> centroid, const int radius)
{
	isComplete = false;
	orignal->setRadius(radius);
	orignal->setCentroid(centroid);
}

std::vector<std::pair<int, int>> CircleRim::Vertices(Window& window_now)
{
	if (orignal->out_range(window_now))
		return std::vector<std::pair<int, int>>();
	if(!isComplete)
	{
		internal_FirstQuadrant_Upper();
		toQuadrant();
		toEntireArc();
		Relocation(orignal->getCentroid());
	}
	if(orignal->complete_image(window_now))
		return Trajectory;
	else
	{
		std::vector<std::pair<int, int>> ret;
		std::for_each(Trajectory.begin(), Trajectory.end(), [&ret](std::pair<int,int> &point)
		{
			ret.push_back(point);
		});
		return ret;
	}
}

void CircleRim::internal_FirstQuadrant_Upper()
{
	Trajectory.clear();
	double p = 1.25 - orignal->getRadius();
	std::pair<int, int> point(0, int(orignal->getRadius() + 0.5));
	Trajectory.push_back(point);
	while (point.second >= point.first) {
		if (p >= 0)
		{
			point.second--;
			p = p + 2 * point.first + 3 - 2 * point.second - 2;
		}
		else
		{
			p = p + 2 * point.first + 3;
		}
		point.first++;
		Trajectory.push_back(point);
	}
	isComplete = true;
}
