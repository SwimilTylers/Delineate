#pragma once
#include <utility>
#include <string>
#include <sstream>

struct Matrix;
namespace mtx
{
	Matrix relocate(std::pair<int, int> disp);
	Matrix scale(std::pair<double, double> ratio);
	Matrix rotate(double rad);
}

struct Matrix
{
	Matrix(const int row, const int col);
	Matrix(const std::pair<int, int> &a);
	Matrix(const Matrix& a);
	Matrix(const Matrix&& a) noexcept;
	~Matrix();

	double** values;
	const int row, col;

	std::pair<int, int> coordinate() const;
	std::string toString() const
	{
		std::string ret;
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				char str[100];
				sprintf_s(str, "%lf", values[i][j]);
				ret += str;
				ret+= '\t';
			}
			ret += '\n';
		}
		return ret;
	}


	friend Matrix operator+(const Matrix& x, const Matrix& y);
	friend Matrix operator-(const Matrix& x, const Matrix& y);
	friend Matrix operator*(const Matrix& x, const Matrix& y);

	
	friend  Matrix mtx::relocate(std::pair<int, int> disp);
	friend Matrix mtx::scale(std::pair<double, double> ratio);
	friend  Matrix mtx::rotate(double rad);
};

