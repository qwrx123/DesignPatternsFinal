#ifndef BOUNDS_H
#define BOUNDS_H

struct Bounds
{
	double top;
	double bottom;
	double left;
	double right;

	Bounds() : top(0), bottom(0), left(0), right(0) {}

	Bounds(double top, double bottom, double left, double right)
		: top(top), bottom(bottom), left(left), right(right)
	{
	}
};

#endif	// BOUNDS_H