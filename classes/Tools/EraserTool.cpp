#include "EraserTool.h"
#include <cmath>
#include <algorithm>

// Helper: Distance from a point to a line segment
static float pointToSegmentDistance(const Point& p, const Point& a, const Point& b)
{
	Point ab			 = {b.x - a.x, b.y - a.y};
	Point ap			 = {p.x - a.x, p.y - a.y};
	float ab_len_squared = ab.x * ab.x + ab.y * ab.y;

	if (ab_len_squared == 0.0f)
	{
		float dx = p.x - a.x;
		float dy = p.y - a.y;
		return std::sqrt(dx * dx + dy * dy);
	}

	float projection = (ap.x * ab.x + ap.y * ab.y) / ab_len_squared;
	float t			 = std::max(0.0f, std::min(1.0f, projection));
	Point closest	 = {a.x + ab.x * t, a.y + ab.y * t};

	float dx = p.x - closest.x;
	float dy = p.y - closest.y;
	return std::sqrt(dx * dx + dy * dy);
}

EraserTool::EraserTool(std::shared_ptr<IStrokeManager> stroke_manager, float thickness)
	: stroke_manager(stroke_manager), eraser_thickness(thickness), active(false), drawing(false)
{
}

EraserTool::~EraserTool() = default;

void EraserTool::beginStroke(const Point& start)
{
	drawing	   = true;
	erase_path = std::make_shared<Stroke>(Color{1.0f, 1.0f, 1.0f, 0.0f}, eraser_thickness);
	erase_path->addPoint(start);
}

void EraserTool::addPoint(const Point& point)
{
	if (!erase_path) return;

	// Add point to visual eraser path
	erase_path->addPoint(point);

	const auto& points = erase_path->getPoints();
	if (points.size() < 2) return;

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

		if (intersects) break;
	}

	// If intersection is likely, send mini path to stroke manager
	if (intersects)
	{
		auto segment_path =
			std::make_shared<Stroke>(Color{1.0f, 1.0f, 1.0f, 0.0f}, eraser_thickness);
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