#include "BrushTool.h"
#include "Stroke.h"

BrushTool::BrushTool(Color color, float thickness)
	: brush_color(color), brush_thickness(thickness), active(false)
{
}

BrushTool::BrushTool(std::shared_ptr<IStrokeManager> stroke_manager, Color color, float thickness)
	: stroke_manager(std::move(stroke_manager)),
	  brush_color(color),
	  brush_thickness(thickness),
	  active(false)
{
}

BrushTool::~BrushTool() = default;

void BrushTool::beginStroke(const Point& start)
{
	drawing		   = true;
	current_stroke = std::make_shared<Stroke>(brush_color, brush_thickness);
	current_stroke->addPoint(start);
}

void BrushTool::addPoint(const Point& point)
{
	if (current_stroke)
	{
		current_stroke->addPoint(point);
	}
}

void BrushTool::endStroke(const Point& end)
{
	drawing = false;
	if (current_stroke)
	{
		current_stroke->addPoint(end);
		stroke_manager->addStroke(current_stroke);
		current_stroke.reset();
	}
}

std::shared_ptr<IStroke> BrushTool::getCurrentStroke()
{
	return current_stroke;
}

bool BrushTool::isActive() const
{
	return active;
}

void BrushTool::setActive(bool value)
{
	active = value;
}

bool BrushTool::isDrawing() const
{
	return drawing;
}