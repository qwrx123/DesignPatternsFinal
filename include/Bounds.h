#ifndef BOUNDS_H
#define BOUNDS_H

struct Bounds
{
	float top;
	float bottom;
	float left;
	float right;

	[[nodiscard]] bool contains(double x, double y) const
	{
		return x >= left && x <= right && y >= top && y <= bottom;
	}
};

#endif	// BOUNDS_H