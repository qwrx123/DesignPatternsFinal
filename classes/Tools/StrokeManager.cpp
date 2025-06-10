#include "StrokeManager.h"
#include "Stroke.h"
#include <cassert>
#include <cmath>

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

StrokeManager::StrokeManager() = default;

StrokeManager::~StrokeManager() = default;

StrokeManager::StrokeManager(const StrokeManager& other) : strokes_(std::move(other.cloneStrokes()))
{
}

StrokeManager& StrokeManager::operator=(const StrokeManager& other)
{
	if (this == &other)
	{
		return *this;
	}
	strokes_ = std::move(other.cloneStrokes());
	return *this;
}

StrokeManager::StrokeManager(StrokeManager&& other) noexcept : strokes_(std::move(other.strokes_))
{
}

StrokeManager& StrokeManager::operator=(StrokeManager&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}
	strokes_ = std::move(other.strokes_);
	return *this;
}

void StrokeManager::addStroke(std::shared_ptr<IStroke> stroke)
{
	strokes_.push_back(std::move(stroke));
}

const std::vector<std::shared_ptr<IStroke>>& StrokeManager::getStrokes() const
{
	return strokes_;
}

void StrokeManager::clear()
{
	strokes_.clear();
}

void StrokeManager::replaceStrokes(std::vector<std::shared_ptr<IStroke>> new_strokes)
{
	strokes_ = std::move(new_strokes);
}

void StrokeManager::splitEraseWithPath(const std::shared_ptr<IStroke>& eraser_path,
									   float						   eraser_radius)
{
	std::vector<std::shared_ptr<IStroke>> updated_strokes;

	// For each existing stroke
	for (const auto& stroke : strokes_)
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

std::vector<std::shared_ptr<IStroke>> StrokeManager::cloneStrokes() const
{
	std::vector<std::shared_ptr<IStroke>> clonedStrokes;

	for (const auto& btn : strokes_)
	{
		auto strkPtr = std::dynamic_pointer_cast<Stroke>(btn);
		if (strkPtr)
		{
			clonedStrokes.push_back(std::make_shared<Stroke>(*strkPtr));
		}
		else
		{
			assert(false);
		}
	}

	return clonedStrokes;
}

void StrokeManager::isErased(const auto& stroke_pts, size_t i, bool& is_erased,
							 std::vector<std::shared_ptr<IStroke>>& updated_strokes,
							 std::vector<Point>&					current_segment,
							 const std::shared_ptr<IStroke>& eraser_path, float eraser_radius,
							 const std::shared_ptr<IStroke>& stroke)
{
	// This function is a placeholder for any additional logic needed when a stroke is erased.
	// Currently, it does nothing but can be extended in the future if needed.
	if (i + 1 < stroke_pts.size())
	{
		Point a = stroke_pts[i];
		Point b = stroke_pts[i + 1];

		// Check each eraser segment against this stroke segment
		const auto& erase_pts = eraser_path->getPoints();
		for (size_t j = 0; j + 1 < erase_pts.size(); ++j)
		{
			Point e_center = erase_pts[j];

			// Erase if segment is within eraser radius
			if (pointToSegmentDistance(e_center, a, b) <= eraser_radius)
			{
				is_erased = true;
				break;
			}
		}
	}
	else
	{
		// Last point in stroke: do point-to-point erasing
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

void StrokeManager::removeLastStroke()
{
	if (!strokes_.empty())
	{
		strokes_.pop_back();
	}
}