#include "Stroke.h"
#include <cmath>
#include <iostream>

Stroke::Stroke(Color color, float thickness) : stroke_color(color), stroke_thickness(thickness) {}

Stroke::Stroke() : stroke_color{.r = 0.0F, .g = 0.0F, .b = 0.0F, .a = 1.0F}, stroke_thickness(1.0F)
{
}

Stroke::~Stroke() = default;

void Stroke::addPoint(const Point& point)
{
	points.push_back(point);
}

const std::vector<Point>& Stroke::getPoints() const
{
	return points;
}

Color Stroke::getColor() const
{
	return stroke_color;
}

float Stroke::getThickness() const
{
	return stroke_thickness;
}

double Stroke::getLength() const
{
	if (points.size() < 2)
	{
		return 0.0;
	}

	double length = 0.0;
	for (size_t i = 1; i < points.size(); ++i)
	{
		double dx = points[i].x - points[i - 1].x;
		double dy = points[i].y - points[i - 1].y;
		length += std::sqrt((dx * dx) + (dy * dy));
	}
	return length;
}

void Stroke::setThickness(float thickness)
{
	stroke_thickness = thickness;
}

void Stroke::setColor(const Color& color)
{
	stroke_color = color;
}