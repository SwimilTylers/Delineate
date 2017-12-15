#include "Matrix.h"
#include <valarray>


Matrix::Matrix(const int row, const int col): row(row), col(col)
{
	values = new double*[row];
	for (int i = 0; i < row; ++i)
	{
		values[i] = new double[col];
	}
}

Matrix::Matrix(const std::pair<int, int>& a): row(3), col(1)
{
	values = new double*[3];
	for (int i = 0; i < 3; ++i)
	{
		values[i] = new double[1];
	}
	values[0][0] = a.first;
	values[1][0] = a.second;
	values[2][0] = 1;
}

Matrix::Matrix(const Matrix& a): row(a.row), col(a.col)
{
	values = new double*[a.row];
	for (int i = 0; i < a.row; ++i)
	{
		values[i] = new double[a.col];
		for (int j = 0; j < a.col; ++j)
		{
			values[i][j] = a.values[i][j];
		}
	}
}

Matrix::Matrix(const Matrix&& a) noexcept: row(a.row), col(a.col)
{
	values = new double*[a.row];
	for (int i = 0; i < a.row; ++i)
	{
		values[i] = new double[a.col];
		for (int j = 0; j < a.col; ++j)
		{
			values[i][j] = a.values[i][j];
		}
	}
}


Matrix::~Matrix()
{
	for (int i = 0; i < row; ++i)
	{
		delete values[i];
	}
}


std::pair<int, int> Matrix::coordinate() const
{
	if (row == 1)
	{
		if (col == 2)
		{
			std::pair<int, int> ret;
			ret.first = values[0][0];
			ret.second = values[0][1];
			return ret;
		}
		if (col == 3)
		{
			std::pair<int, int> ret;
			ret.first = values[0][0] * values[0][2];
			ret.second = values[0][1] * values[0][2];
			return ret;
		}
		else
			throw nullptr;
	}
	if (col == 1)
	{
		if (row == 2)
		{
			std::pair<int, int> ret;
			ret.first = values[0][0];
			ret.second = values[1][0];
			return ret;
		}
		if (row == 3)
		{
			std::pair<int, int> ret;
			ret.first = values[0][0] * values[2][0];
			ret.second = values[1][0] * values[2][0];
			return ret;
		}
		throw nullptr;
	}
	throw nullptr;
}

Matrix mtx::relocate(const std::pair<int, int> disp)
{
	Matrix ret(3, 3);

	ret.values[0][0] = 1;
	ret.values[0][1] = 0;
	ret.values[0][2] = disp.first;

	ret.values[1][0] = 0;
	ret.values[1][1] = 1;
	ret.values[1][2] = disp.second;

	ret.values[2][0] = 0;
	ret.values[2][1] = 0;
	ret.values[2][2] = 1;

	return ret;
}

Matrix mtx::scale(const std::pair<double, double> ratio)
{
	Matrix ret(3, 3);

	ret.values[0][0] = ratio.first;
	ret.values[0][1] = 0;
	ret.values[0][2] = 1;

	ret.values[1][0] = 0;
	ret.values[1][1] = ratio.second;
	ret.values[1][2] = 1;

	ret.values[2][0] = 0;
	ret.values[2][1] = 0;
	ret.values[2][2] = 1;

	return ret;
}

Matrix mtx::rotate(const double rad)
{
	Matrix ret(3, 3);

	ret.values[0][0] = cos(rad);
	ret.values[0][1] = -sin(rad);
	ret.values[0][2] = 0;

	ret.values[1][0] = sin(rad);
	ret.values[1][1] = cos(rad);
	ret.values[1][2] = 0;

	ret.values[2][0] = 0;
	ret.values[2][1] = 0;
	ret.values[2][2] = 1;

	return ret;
}

Matrix operator+(const Matrix& x, const Matrix& y)
{
	if (x.row == y.row && x.col == y.col)
	{
		Matrix ret(x.row, x.col);
		for (int i = 0; i < x.row; ++i)
		{
			for (int j = 0; j < x.col; ++j)
			{
				ret.values[i][j] = x.values[i][j] + y.values[i][j];
			}
		}
		return ret;
	}
	else
		throw nullptr;
}

Matrix operator-(const Matrix& x, const Matrix& y)
{
	if (x.row == y.row && x.col == y.col)
	{
		Matrix ret(x.row, x.col);
		for (int i = 0; i < x.row; ++i)
		{
			for (int j = 0; j < x.col; ++j)
			{
				ret.values[i][j] = x.values[i][j] - y.values[i][j];
			}
		}
		return ret;
	}
	else
		throw nullptr;
}

Matrix operator*(const Matrix& x, const Matrix& y)
{
	if (x.col == y.row)
	{
		Matrix ret(x.row, y.col);
		for (int i = 0; i < x.row; ++i)
		{
			for (int j = 0; j < y.col; ++j)
			{
				double buf = 0;
				for (int k = 0; k < x.col; ++k)
				{
					buf += x.values[i][k] * y.values[k][j];
				}
				ret.values[i][j] = buf;
			}
		}
		return ret;
	}
	else
		throw nullptr;
}
