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

EraserTool::EraserTool(std::shared_ptr<LayerManager>   layer_manager,
					   std::shared_ptr<IStrokeManager> stroke_manager, float thickness)
	: layer_manager(std::move(layer_manager)),
	  stroke_manager(std::move(stroke_manager)),
	  eraser_thickness(thickness)
{
}

EraserTool::~EraserTool() = default;

void EraserTool::beginStroke(const Point& start)
{
	drawing	   = true;
	erase_path = std::make_shared<Stroke>(Color{.r = 1.0F, .g = 1.0F, .b = 1.0F, .a = 0.0F},
										  eraser_thickness);
	erase_path->addPoint(start);

	if (layer_manager->getActiveLayer()->getEraserHistory().isEmpty())
	{
		layer_manager->getActiveLayer()->updateEraserHistory();
	}
}

void EraserTool::addPoint(const Point& point)
{
	if (!erase_path)
	{
		return;
	}

	erase_path->addPoint(point);

	const auto& points = erase_path->getPoints();
	if (points.size() < 2)
	{
		return;
	}

	const Point& a = points[points.size() - 2];
	const Point& b = points[points.size() - 1];

	bool intersects = false;

	auto active_layer = layer_manager->getActiveLayer();
	for (const auto& stroke : active_layer->getStrokes())
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

	if (intersects)
	{
		auto segment_path = std::make_shared<Stroke>(
			Color{.r = 1.0F, .g = 1.0F, .b = 1.0F, .a = 0.0F}, eraser_thickness);
		segment_path->addPoint(a);
		segment_path->addPoint(b);
		splitEraseWithPath(segment_path, eraser_thickness);
	}
}

void EraserTool::endStroke(const Point& end)
{
	drawing = false;

	if (erase_path)
	{
		erase_path->addPoint(end);
		splitEraseWithPath(erase_path, eraser_thickness);
		layer_manager->getActiveLayer()->updateEraserHistory();
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

void EraserTool::setColor(const Color& color) {}

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
	layer_manager->getActiveLayer()->undoErase();
}

void EraserTool::redoStroke()
{
	layer_manager->getActiveLayer()->redoErase();
}

void EraserTool::clearStrokes()
{
	stroke_manager->clear();
}

void EraserTool::splitEraseWithPath(const std::shared_ptr<IStroke>& eraser_path,
									float							eraser_radius)
{
	std::vector<std::shared_ptr<IStroke>> updated_strokes;

	auto		layer	= layer_manager->getActiveLayer();
	const auto& strokes = layer->getStrokes();

	for (const auto& stroke : strokes)
	{
		std::vector<Point> current_segment;
		const auto&		   stroke_pts = stroke->getPoints();

		for (size_t i = 0; i < stroke_pts.size(); ++i)
		{
			bool is_erased = false;
			isErased(stroke_pts, i, is_erased, updated_strokes, current_segment, eraser_path,
					 eraser_radius, stroke);
		}

		if (!current_segment.empty())
		{
			auto new_stroke = std::make_shared<Stroke>(stroke->getColor(), stroke->getThickness());
			for (const auto& p : current_segment)
			{
				new_stroke->addPoint(p);
			}
			updated_strokes.push_back(new_stroke);
		}
	}

	replaceStrokes(std::move(updated_strokes));
}

void EraserTool::replaceStrokes(std::vector<std::shared_ptr<IStroke>> new_strokes)
{
	layer_manager->getActiveLayer()->setStrokes(std::move(new_strokes));
}

void EraserTool::isErased(const std::vector<Point>& stroke_pts, size_t i, bool& is_erased,
						  std::vector<std::shared_ptr<IStroke>>& updated_strokes,
						  std::vector<Point>&					 current_segment,
						  const std::shared_ptr<IStroke>& eraser_path, float eraser_radius,
						  const std::shared_ptr<IStroke>& stroke)
{
	if (i + 1 < stroke_pts.size())
	{
		Point a = stroke_pts[i];
		Point b = stroke_pts[i + 1];

		const auto& erase_pts = eraser_path->getPoints();
		for (size_t j = 0; j + 1 < erase_pts.size(); ++j)
		{
			Point e_center = erase_pts[j];

			if (pointToSegmentDistance(e_center, a, b) <= eraser_radius)
			{
				is_erased = true;
				break;
			}
		}
	}
	else
	{
		for (const auto& ep : eraser_path->getPoints())
		{
			auto dx = static_cast<float>(stroke_pts[i].x - ep.x);
			auto dy = static_cast<float>(stroke_pts[i].y - ep.y);
			if ((dx * dx + dy * dy) <= (eraser_radius * eraser_radius))
			{
				is_erased = true;
				break;
			}
		}
	}

	if (is_erased)
	{
		if (!current_segment.empty())
		{
			auto new_stroke = std::make_shared<Stroke>(stroke->getColor(), stroke->getThickness());
			for (const auto& p : current_segment)
			{
				new_stroke->addPoint(p);
			}
			updated_strokes.push_back(new_stroke);
			current_segment.clear();
		}
	}
	else
	{
		current_segment.push_back(stroke_pts[i]);
	}
}