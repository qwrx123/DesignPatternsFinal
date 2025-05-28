#ifndef BOUNDS_H
#define BOUNDS_H

struct Bounds
{
	double top;
	double bottom;
	double left;
	double right;

	Bounds() {}

	Bounds(double top, double bottom, double left, double right)
	{
		this->top	 = top;
		this->bottom = bottom;
		this->left	 = left;
		this->right	 = right;
	}

	bool contains(double x, double y) const
	{
		return x >= left && x <= right && y >= top && y <= bottom;
	}
};

#endif	// BOUNDS_H