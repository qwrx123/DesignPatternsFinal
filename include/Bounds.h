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
};

#endif	// BOUNDS_H