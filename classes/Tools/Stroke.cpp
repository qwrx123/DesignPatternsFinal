#include "Stroke.h"

Stroke::Stroke(Color color, float thickness)
    : stroke_color(color), stroke_thickness(thickness) {}

Stroke::~Stroke() = default;

void Stroke::addPoint(const Point& point) {
    points.push_back(point);
}

const std::vector<Point>& Stroke::getPoints() const {
    return points;
}

Color Stroke::getColor() const {
    return stroke_color;
}

float Stroke::getThickness() const {
    return stroke_thickness;
}

#include <cmath> // for std::sqrt, std::pow

double Stroke::getLength() const {
    if (points.size() < 2) return 0.0;

    double length = 0.0;
    for (size_t i = 1; i < points.size(); ++i) {
        double dx = points[i].x - points[i - 1].x;
        double dy = points[i].y - points[i - 1].y;
        length += std::sqrt(dx * dx + dy * dy);
    }
    return length;
}