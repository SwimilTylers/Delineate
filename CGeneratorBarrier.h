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

	virtual CGeneratorBarrier* getNextBarrier(const int now_y) const = 0;

protected:
	int x;
};

