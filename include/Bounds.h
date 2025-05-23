#ifndef BOUNDS_H
#define BOUNDS_H

struct Bounds
{
	float top;
	float bottom;
	float left;
	float right;

	Bounds() : top(0), bottom(0), left(0), right(0) {}

	Bounds(float top, float bottom, float left, float right)
		: top(top), bottom(bottom), left(left), right(right)
	{
	}
};

#endif	// BOUNDS_H