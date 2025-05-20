#ifndef STROKE_H
#define STROKE_H

#include "IStroke.h"
#include "Point.h"

class Stroke : public IStroke 
{
public:
    Stroke(Color color, float thickness);
	Stroke();
	~Stroke() override;

    void setThickness(float thickness) override;
    void setColor(const Color& color) override;
    void addPoint(const Point& point) override;

    const std::vector<Point>& getPoints() const override;
    Color getColor() const override;
	float getThickness() const override;
    double getLength() const override;

private:
    std::vector<Point> points;
    Color stroke_color;
    float stroke_thickness;
};

#endif	// STROKE_H