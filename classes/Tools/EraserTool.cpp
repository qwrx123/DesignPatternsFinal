#include "EraserTool.h"
#include <cmath>
#include <algorithm>

// Helper: Distance from a point to a line segment
static float pointToSegmentDistance(const Point& p, const Point& a, const Point& b)
{
	Point ab			 = {.x = (b.x - a.x), .y = (b.y - a.y)};
	Point ap			 = {.x = (p.x - a.x), .y = (p.y - a.y)};
	auto  ab_len_squared = ((ab.x * ab.x) + (ab.y * ab.y));

	if (ab_len_squared == 0.0F)
	{
		auto dx = static_cast<float>(p.x - a.x);
		auto dy = static_cast<float>(p.y - a.y);
		return std::sqrt((dx * dx) + (dy * dy));
	}

	float projection =
		static_cast<float>(((ap.x * ab.x) + (ap.y * ab.y))) / static_cast<float>(ab_len_squared);
	float t		  = std::max(0.0F, std::min(1.0F, projection));
	Point closest = {.x = (a.x + (ab.x * t)), .y = (a.y + (ab.y * t))};

	auto dx = static_cast<float>(p.x - closest.x);
	auto dy = static_cast<float>(p.y - closest.y);
	return std::sqrt((dx * dx) + (dy * dy));
}

EraserTool::EraserTool(std::shared_ptr<IStrokeManager> stroke_manager, float thickness)
	: stroke_manager(std::move(stroke_manager)), eraser_thickness(thickness)
{
}

EraserTool::~EraserTool() = default;

void EraserTool::beginStroke(const Point& start)
{
	drawing	   = true;
	erase_path = std::make_shared<Stroke>(Color{.r = 1.0F, .g = 1.0F, .b = 1.0F, .a = 0.0F},
										  eraser_thickness);
	erase_path->addPoint(start);
}

void EraserTool::addPoint(const Point& point)
{
	if (!erase_path)
	{
		return;
	}

	// Add point to visual eraser path
	erase_path->addPoint(point);

	const auto& points = erase_path->getPoints();
	if (points.size() < 2)
	{
		return;
	}

	const Point& a = points[points.size() - 2];
	const Point& b = points[points.size() - 1];

	// Check if this segment meaningfully overlaps any stroke (fast test)
	// We'll construct a mini stroke only if it does
	bool intersects = false;

	for (const auto& stroke : stroke_manager->getStrokes())
	{
		const auto& stroke_points = stroke->getPoints();
		for (size_t i = 0; i + 1 < stroke_points.size(); ++i)
		{
			float dist = pointToSegmentDistance(a, stroke_points[i], stroke_points[i + 1]);
			if (dist < eraser_thickness)
			{
				intersects = true;
				break;
			}

			dist = pointToSegmentDistance(b, stroke_points[i], stroke_points[i + 1]);
			if (dist < eraser_thickness)
			{
				intersects = true;
				break;
			}
		}

		if (intersects)
		{
			break;
		}
	}

	// If intersection is likely, send mini path to stroke manager
	if (intersects)
	{
		auto segment_path = std::make_shared<Stroke>(
			Color{.r = 1.0F, .g = 1.0F, .b = 1.0F, .a = 0.0F}, eraser_thickness);
		segment_path->addPoint(a);
		segment_path->addPoint(b);
		stroke_manager->splitEraseWithPath(segment_path, eraser_thickness);
	}
}

void EraserTool::endStroke(const Point& end)
{
	drawing = false;

	if (erase_path)
	{
		erase_path->addPoint(end);
		stroke_manager->splitEraseWithPath(erase_path, eraser_thickness);
		erase_path = nullptr;
	}
}

std::shared_ptr<IStroke> EraserTool::getCurrentStroke()
{
	return nullptr;
}

std::string EraserTool::getName()
{
	return "Eraser";
}

void  EraserTool::setColor(const Color& color) {}
Color EraserTool::getColor() const
{
	return eraser_color;
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

void EraserTool::setThickness(float thickness)
{
	eraser_thickness = thickness;
	if (erase_path)
	{
		erase_path->setThickness(thickness);
	}
}

float EraserTool::getThickness() const
{
	return eraser_thickness;
}

void EraserTool::undoStroke()
{
	stroke_manager->undoStroke();
}

void EraserTool::redoStroke()
{
	stroke_manager->redoStroke();
}

History<std::vector<std::shared_ptr<IStroke>>> EraserTool::getHistory() const
{
	return stroke_manager->getEraserHistory();
}