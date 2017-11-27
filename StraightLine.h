#pragma once
#include "Outline.h"
#include <algorithm>
#include "GeometricLine.h"
#include <functional>

class StraightLine :
	public Outline
{
public:
	StraightLine(GeometricLine& description);
	~StraightLine();
	std::vector<std::pair<int, int>> Vertices(Window& window_now) override;
	std::pair<int, GeometricLine::ScanBucket> getScanBucket() const
	{
		return std::pair<int, GeometricLine::ScanBucket>(orignal.scan_bucket_start_y(), orignal.scan_bucket());
	}

	double getGradient() const
	{
		return orignal.getGradient();
	}

private:
	GeometricLine orignal;

	// Pre
	static void inline Exchange_Tensor(std::pair<int, int>& needle)
	{
		const int temp = needle.first;
		needle.first = needle.second;
		needle.second = temp;
	}
	static void inline Exchange_Vector(std::pair<int, int>& A, std::pair<int, int>& B)
	{
		std::pair<int, int> temp;
		temp.swap(A);
		A.swap(B);
		B.swap(temp);
	}


	// During
	static std::vector<std::pair<int, int>> internal_xinc_l2r_asc(
		std::pair<int, int> &leftdown, std::pair<int, int> &deltas, int xincs);
	static std::vector<std::pair<int,int>> internal_link_str8(std::pair<std::pair<int,int>,std::pair<int,int>>&& vtx)
	{
		std::vector<std::pair<int, int>> ret;
		if(vtx.first.first == vtx.second.first)
		{
			int common_x = vtx.first.first;
			const int y_1 = vtx.first.second;
			const int y_2 = vtx.second.second;
			for (int i = (y_1 > y_2 ? y_2 : y_1); i <= (y_1 > y_2 ? y_1 : y_2); ++i)
			{
				ret.push_back(std::pair<int, int>(common_x, i));
			}
		}
		else
		{
			int common_y = vtx.first.second;
			const int x_1 = vtx.first.first;
			const int x_2 = vtx.second.first;
			for (int i = (x_1 > x_2 ? x_2 : x_1); i <= (x_1 > x_2 ? x_1 : x_2); ++i)
			{
				ret.push_back(std::pair<int, int>(i, common_y));
			}
		}
		return ret;
	}
	
	// Post
	static inline void ExhangeTensorForAll(std::vector<std::pair<int, int>>& before)
	{
		std::for_each(before.begin(), before.end(), [](std::pair<int, int>& element)
		{
			int temp = element.first;
			element.first = element.second;
			element.second = temp;
		});
	}
	static inline void RecalibrateGradient(std::vector<std::pair<int, int>>& before)
	{
		int cover = 2 * before.begin()->second;
		std::for_each(before.begin(), before.end(), [cover](std::pair<int, int>& element)
		{
			element.second = cover - element.second;
		});
	}
	static std::vector<std::pair<int, int>>& Wrapping
	(std::vector<std::pair<int, int>>&& Before, const bool isTensorExchange, const bool isGradientNegative)
	{
		if (isGradientNegative)
			RecalibrateGradient(Before);
		if (isTensorExchange)
			ExhangeTensorForAll(Before);
		return Before;
	}
};

