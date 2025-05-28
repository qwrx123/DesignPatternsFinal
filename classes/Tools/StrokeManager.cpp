#include "StrokeManager.h"

StrokeManager::StrokeManager() = default;

StrokeManager::~StrokeManager() = default;

void StrokeManager::addStroke(std::shared_ptr<IStroke> stroke) {
    strokes_.push_back(std::move(stroke));
}

const std::vector<std::shared_ptr<IStroke>>& StrokeManager::getStrokes() const {
    return strokes_;
}

void StrokeManager::clear() {
    strokes_.clear();
}

void StrokeManager::replaceStrokes(std::vector<std::shared_ptr<IStroke>> new_strokes) {
    strokes_ = std::move(new_strokes);
}

void StrokeManager::splitEraseWithPath(const std::shared_ptr<IStroke>& eraser_path, float eraser_radius)
{
    std::vector<std::shared_ptr<IStroke>> updated_strokes;

    for (const auto& stroke : strokes_)
    {
        std::vector<Point> current_segment;
        const auto& stroke_pts = stroke->getPoints();

        for (const auto& pt : stroke_pts)
        {
            bool is_erased = false;
            for (const auto& ept : eraser_path->getPoints())
            {
                double dx = pt.x - ept.x;
                double dy = pt.y - ept.y;
                if ((dx * dx + dy * dy) <= (eraser_radius * eraser_radius))
                {
                    is_erased = true;
                    break;
                }
            }

            if (is_erased)
            {
                if (!current_segment.empty())
                {
                    auto new_stroke = std::make_shared<Stroke>(
    stroke->getColor(), stroke->getThickness());

                    for (const auto& p : current_segment)
                        new_stroke->addPoint(p);

                    updated_strokes.push_back(new_stroke);
                    current_segment.clear();
                }
            }
            else
            {
                current_segment.push_back(pt);
            }
        }

        if (!current_segment.empty())
        {
            auto new_stroke = std::make_shared<Stroke>(
    stroke->getColor(), stroke->getThickness());
            for (const auto& p : current_segment)
                new_stroke->addPoint(p);

            updated_strokes.push_back(new_stroke);
        }
    }

    replaceStrokes(std::move(updated_strokes));
}