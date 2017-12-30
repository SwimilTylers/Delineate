#pragma once
#include <utility>
#include "Window.h"
#include <vector>
#include "CGeneratorBarrier.h"

class GeometricLine
{
public:
	GeometricLine(std::pair<int, int> point_1, std::pair<int, int> point_2);
	~GeometricLine();

	double getGradient() const;
	std::pair<int, int> get_deltas() const;
	std::pair<std::pair<int, int>, std::pair<int, int>> get_vertices() const;
	GeometricLine *compatibility(Window& window);
	std::pair<bool, std::pair<int, int>> onLine_x(const int x) const
	{
		std::pair<int, int> ret;
		bool isOn = false;
		if (x <= right && x >= left)
		{
			isOn = true;
			ret.first = x;
			ret.second = gradient * (x - start.first) + start.second;
		}
		return std::pair<bool, std::pair<int, int>>(isOn, ret);
	}
	std::pair<bool, std::pair<int, int>> onLine_y(const int y) const
	{
		std::pair<int, int> ret;
		bool isOn = false;
		if (y <= up && y >= down)
		{
			isOn = true;
			ret.second = y;
			ret.first = (y - start.second) / gradient + start.first;
		}
		return std::pair<bool, std::pair<int, int>>(isOn, ret);
	}

	class ScanBucket : public CGeneratorBarrier
	{
	public:
		ScanBucket(const double x, const int max_y, const double gradient)
			: max_y(max_y),
			  gradient(gradient)
		{
			this->x = x;
		}

		ScanBucket* updata(const int current_y) const;

		int get_max_y() const
		{
			return max_y;
		}

	private:
		int max_y;
		double gradient;
		bool isOutofDate(const int cmp_y) const
		{
			if(cmp_y >= max_y)
				return true;
			else
				return false;
		}

	public:
		CGeneratorBarrier* getNextBarrier(const int now_y) const override;
	};

	ScanBucket scan_bucket() const
	{
		const auto yleast = start.second < end.second ? start : end;
		const auto ymost = start.second > end.second ? start : end;
		return ScanBucket(yleast.first, ymost.second, gradient);
	}
	int scan_bucket_start_y() const
	{
		return start.second < end.second ? start.second : end.second;
	}

private:
	std::pair<int, int> deltas;
	std::pair<int, int> start, end;
	int left, right, up, down;
	double gradient;
};

