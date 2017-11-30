#include "GLPlayer.h"
#include <GL/glut.h>
#include <utility>
#include "Outline.h"
#include "Graphic.h"
#include <ppltasks.h>
#include <cassert>
#include <string>
#include <stack>
using namespace std;

#define FLOAT_PRINT true

inline void PinPoint(const pair<int, int>& pinned, Window WindowNow)
{
#if FLOAT_PRINT
	glVertex3f(float(pinned.first) / WindowNow.getWindowSize().first - 1,
		float(pinned.second) / WindowNow.getWindowSize().second - 1, 0.0);
#else
	glVertex3d(element.first, element.second, 0);
#endif
}

inline int QuickFind(vector<CGeneratorBarrier*>& this_line, pair<int,int>& CGenerator)
{
	int head(0), tail(this_line.size() - 1), mid;

	while (true)
	{
		mid = (head + tail) / 2;

		if (mid < 0 || mid >= this_line.size())	throw string("outside the graphic\n");
		if (head >= tail)	break;

		if (this_line[mid]->get_x() < CGenerator.first)	head = mid + 1;
		else if (this_line[mid]->get_x() > CGenerator.first)	tail = mid - 1;
		else	throw string("collided with the outline\n");
	}
	assert(mid >= 1 && mid <= this_line.size() - 2);
	assert(this_line[mid]->get_x() > CGenerator.first);

	return mid;
}


GLPlayer::GLPlayer(const Window InitWindow)
: WindowNow(InitWindow)
{
}

void GLPlayer::DrawOutline(Outline& outline)
{
	glBegin(GL_POINTS);
	for (const pair<int,int> element : outline.Vertices(WindowNow))
	{
		PinPoint(element, WindowNow);
	}
	glEnd();
}

void GLPlayer::FillGraphic(Graphic& graphic)
{
	// display the outline of the graphic
	{
		auto color = graphic.getEdgeColor();
		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_POINTS); 
		auto&& drawnpoints = graphic.EdgeVertices(WindowNow);
		auto& win = WindowNow;
		for_each(drawnpoints.begin(),drawnpoints.end(), [win](pair<int,int>& drawnpoint)
		{
			PinPoint(drawnpoint, win);
		});

		/*
		for (const pair<int, int> element : graphic.EdgeVertices(WindowNow))
		{
			PinPoint(element, WindowNow);
		}
		*/

		glEnd();
	}

	// fill the texture
	{
		for (auto CGenerator : graphic.getCGenerators())
		{
			glColor3f(CGenerator.second[0], CGenerator.second[1], CGenerator.second[2]);
			glBegin(GL_POINTS);
			auto&& buf = CGenerationKernel(CGenerator.first, graphic.getRangeY().first, 
				graphic.getCGProfile(), WindowNow);
			auto &win = WindowNow;
			for_each(buf.begin(), buf.end(), [&win](vector<pair<int, int>>& subline)
			{
				for_each(subline.begin(), subline.end(), [&win](pair<int,int>& drawnpoint)
				{
					PinPoint(drawnpoint, win);
				});
			});
			glEnd();
		}
	}
	
}

Window& GLPlayer::getWindow()
{
	return WindowNow;
}

void GLPlayer::setWindow(Window& Now)
{
	WindowNow = Now;
}


GLPlayer::~GLPlayer()
{
}

vector<vector<pair<int, int>>> GLPlayer::CGenerationKernel(std::pair<int, int>& IgnitionCoordinate, const int baseY, vector<vector<CGeneratorBarrier*>>& CGeneratorList, Window& WindowNow)
{
	vector<vector<pair<int, int>>> ret;

	vector<pair<int, int>> sec_ret;

	stack<pair<int, int>> CGeneratorCoordinates;
	CGeneratorCoordinates.push(IgnitionCoordinate);

	// downs

	while (!CGeneratorCoordinates.empty())
	{
		// get new CGCoordinate and its corresponding CGProfile line

		auto thisCGCoordinate = CGeneratorCoordinates.top();
		CGeneratorCoordinates.pop();

		auto this_line = CGeneratorList[thisCGCoordinate.second - baseY];

		sec_ret.clear();

		
		auto below_line = thisCGCoordinate.second - baseY - 1 > 0
			? CGeneratorList[thisCGCoordinate.second - baseY - 1]
			: vector<CGeneratorBarrier*>();
/*
		auto above_line = thisCGCoordinate.second - baseY + 1 <= CGeneratorList.size()
			? CGeneratorList[thisCGCoordinate.second - baseY + 1]
			: vector<CGeneratorBarrier*>();

		*/


		// find out the appropriate section

		int stationary = 0;

		if (this_line.size() < 5)
		{
			for (int i = 0; i < this_line.size(); ++i)
			{
				if (this_line[i]->get_x() > thisCGCoordinate.first)
				{
					stationary = i;
					break;
				}
			}
			if (stationary == 0)
				return ret;
		}
		else {
			try {
				stationary = QuickFind(this_line, thisCGCoordinate);
			}
			catch (string) { return ret; }
		}

		pair<int, int> RangeX(this_line[stationary - 1]->get_x() + 1, this_line[stationary]->get_x() - 1);


		// fill out the drawnpoints

		pair<int, int> drawnpoint(RangeX.first, thisCGCoordinate.second);
		for (; drawnpoint.first <= RangeX.second; drawnpoint.first++)
		{
			sec_ret.push_back(drawnpoint);
		}

		ret.push_back(sec_ret);


		auto&& candidates = CGenerationRecursionStartPoint(below_line, RangeX, thisCGCoordinate.second - 1);
		for_each(candidates.begin(), candidates.end(), [&CGeneratorCoordinates](pair<int, int>& candidate) {CGeneratorCoordinates.push(candidate); });
	}
	
	CGeneratorCoordinates.push(IgnitionCoordinate);

	while (!CGeneratorCoordinates.empty())
	{
		// get new CGCoordinate and its corresponding CGProfile line

		auto thisCGCoordinate = CGeneratorCoordinates.top();
		CGeneratorCoordinates.pop();

		auto this_line = CGeneratorList[thisCGCoordinate.second - baseY];

		sec_ret.clear();

/*
		auto below_line = thisCGCoordinate.second - baseY - 1 > 0
			? CGeneratorList[thisCGCoordinate.second - baseY - 1]
			: vector<CGeneratorBarrier*>();
*/		
		auto above_line = thisCGCoordinate.second - baseY + 1 < CGeneratorList.size()
		? CGeneratorList[thisCGCoordinate.second - baseY + 1]
		: vector<CGeneratorBarrier*>();

		


		// find out the appropriate section

		int stationary = 0;

		if (this_line.size() < 5)
		{
			for (int i = 0; i < this_line.size(); ++i)
			{
				if (this_line[i]->get_x() > thisCGCoordinate.first)
				{
					stationary = i;
					break;
				}
			}
			if (stationary == 0)
				return ret;
		}
		else {
			try {
				stationary = QuickFind(this_line, thisCGCoordinate);
			}
			catch (string) { return ret; }
		}

		pair<int, int> RangeX(this_line[stationary - 1]->get_x() + 1, this_line[stationary]->get_x() - 1);


		// fill out the drawnpoints

		pair<int, int> drawnpoint(RangeX.first, thisCGCoordinate.second);
		for (; drawnpoint.first <= RangeX.second; drawnpoint.first++)
		{
			sec_ret.push_back(drawnpoint);
		}

		ret.push_back(sec_ret);


		auto&& candidates = CGenerationRecursionStartPoint(above_line, RangeX, thisCGCoordinate.second + 1);
		for_each(candidates.begin(), candidates.end(), [&CGeneratorCoordinates](pair<int, int>& candidate) {CGeneratorCoordinates.push(candidate); });
	}

	return ret;
}

std::vector<std::pair<int, int>> GLPlayer::CGenerationRecursionStartPoint(std::vector<CGeneratorBarrier*>& StartLine,
	std::pair<int, int>& ClosedRange, int CommonY)
{
	vector<pair<int, int>> ret;

	vector<int> xs;
	for_each(StartLine.begin(), StartLine.end(), [&xs](CGeneratorBarrier* element)
	{
		xs.push_back(element->get_x());
	});
	sort(xs.begin(), xs.end());

	for (int i = 0; i < xs.size(); ++i)
	{
		if (xs[i] >= ClosedRange.second)
		{
			ret.push_back(pair<int, int>(xs[i] - 1, CommonY));
			break;
		}
		if (xs[i] > ClosedRange.first)
		{
			ret.push_back(pair<int, int>(xs[i] - 1, CommonY));
		}
	}

	return ret;
}
