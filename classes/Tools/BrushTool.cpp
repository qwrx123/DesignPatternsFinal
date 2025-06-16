#include "BrushTool.h"
#include "Stroke.h"
#include <cmath>

BrushTool::BrushTool(std::shared_ptr<LayerManager>	 layer_manager,
					 std::shared_ptr<IStrokeManager> stroke_manager, Color color, float thickness)
	: layer_manager(std::move(layer_manager)),
	  stroke_manager(std::move(stroke_manager)),
	  brush_color(color),
	  brush_thickness(thickness)
{
}

BrushTool::~BrushTool() = default;

BrushTool::BrushTool(const BrushTool& other)
	: layer_manager(other.layer_manager),
	  brush_color(other.brush_color),
	  brush_thickness(other.brush_thickness),
	  active(other.active),
	  current_stroke(nullptr)
{
}

BrushTool& BrushTool::operator=(const BrushTool& other)
{
	if (this != &other)
	{
		layer_manager	= other.layer_manager;
		brush_color		= other.brush_color;
		brush_thickness = other.brush_thickness;
		active			= other.active;
		drawing			= false;
		current_stroke	= nullptr;
	}
	return *this;
}

BrushTool::BrushTool(BrushTool&& other) noexcept
	: layer_manager(std::move(other.layer_manager)),
	  brush_color(other.brush_color),
	  brush_thickness(other.brush_thickness),
	  active(other.active),
	  drawing(other.drawing),
	  current_stroke(std::move(other.current_stroke))
{
	other.active  = false;
	other.drawing = false;
	other.current_stroke.reset();
}

BrushTool& BrushTool::operator=(BrushTool&& other) noexcept
{
	if (this != &other)
	{
		layer_manager	= std::move(other.layer_manager);
		brush_color		= other.brush_color;
		brush_thickness = other.brush_thickness;
		active			= other.active;
		drawing			= other.drawing;
		current_stroke	= std::move(other.current_stroke);

		other.active  = false;
		other.drawing = false;
		other.current_stroke.reset();
	}
	return *this;
}

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

void BrushTool::setColor(const Color& color)
{
	brush_color = color;
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

Color BrushTool::getColor() const
{
	return brush_color;
}

void BrushTool::setThickness(float thickness)
{
	brush_thickness = thickness;
	if (current_stroke)
	{
		current_stroke->setThickness(thickness);
	}
}

float BrushTool::getThickness() const
{
	return brush_thickness;
}

void BrushTool::undoStroke()
{
	stroke_manager->undoStroke();
}

void BrushTool::redoStroke()
{
	stroke_manager->redoStroke();
}

History<std::shared_ptr<IStroke>> BrushTool::getHistory() const
{
	return stroke_manager->getBrushHistory();
}

void BrushTool::clearStrokes()
{
	stroke_manager->clear();
}