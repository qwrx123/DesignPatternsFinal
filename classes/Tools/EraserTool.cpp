#include "EraserTool.h"

EraserTool::EraserTool(float thickness) : eraser_thickness(thickness) {}

EraserTool::~EraserTool() = default;

void EraserTool::beginStroke(const Point& start)
{
	// Eraser stroke is white with 0 alpha for now (can change this logic later)
	drawing	   = true;
	erase_path = std::make_shared<Stroke>(Color{.r = 1.0F, .g = 1.0F, .b = 1.0F, .a = 0.0F},
										  eraser_thickness);
	erase_path->addPoint(start);
}

void EraserTool::addPoint(const Point& point)
{
	if (erase_path)
	{
		erase_path->addPoint(point);
	}
}

void EraserTool::endStroke(const Point& end)
{
	drawing = false;
	if (erase_path)
	{
		erase_path->addPoint(end);
	}
}

std::shared_ptr<IStroke> EraserTool::getCurrentStroke()
{
	return erase_path;
}

std::string EraserTool::getName()
{
	return "Eraser";
}

void EraserTool::setColor(const Color& color)
{
	return;
}

bool EraserTool::isActive() const
{
	return active;
}

void EraserTool::setActive(bool value)
{
	active = value;
}

bool EraserTool::isDrawing() const
{
	return drawing;
}