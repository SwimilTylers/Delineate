#pragma once
class CGeneratorBarrier
{
public:
	CGeneratorBarrier();
	virtual ~CGeneratorBarrier();

	int get_x() const
	{
		return x;
	}

	virtual CGeneratorBarrier* Update(const int now_y) = 0;

protected:
	int x;
};

