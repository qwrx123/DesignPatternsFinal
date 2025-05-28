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

BrushTool::BrushTool(const BrushTool& other)
	: stroke_manager(other.stroke_manager),
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
		stroke_manager	= other.stroke_manager;
		brush_color		= other.brush_color;
		brush_thickness = other.brush_thickness;
		active			= other.active;
		current_stroke	= nullptr;	// Reset current stroke
		drawing			= false;	// Reset drawing state
	}
	return *this;
}

BrushTool::BrushTool(BrushTool&& other) noexcept
	: stroke_manager(std::move(other.stroke_manager)),
	  brush_color(other.brush_color),
	  brush_thickness(other.brush_thickness),
	  active(other.active),
	  current_stroke(std::move(other.current_stroke)),
	  drawing(other.drawing)
{
	// Reset the moved-from object
	other.active  = false;
	other.drawing = false;
	other.current_stroke.reset();
}

BrushTool& BrushTool::operator=(BrushTool&& other) noexcept
{
	if (this != &other)
	{
		stroke_manager	= std::move(other.stroke_manager);
		brush_color		= other.brush_color;
		brush_thickness = other.brush_thickness;
		active			= other.active;
		current_stroke	= std::move(other.current_stroke);
		drawing			= other.drawing;

		// Reset the moved-from object
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