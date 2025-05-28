#include "BrushTool.h"
#include "Stroke.h"
#include <cmath>

BrushTool::BrushTool(Color color, float thickness)
    : brush_color(color), brush_thickness(thickness), active(false) {}

BrushTool::BrushTool(std::shared_ptr<IStrokeManager> stroke_manager, Color color, float thickness)
    : stroke_manager(stroke_manager), brush_color(color), brush_thickness(thickness),
      active(false), drawing(false) {}


BrushTool::~BrushTool() = default;

void BrushTool::beginStroke(const Point& start) {
	drawing = true;
	current_stroke = std::make_shared<Stroke>(brush_color, brush_thickness);
    current_stroke->addPoint(start);
}

void BrushTool::addPoint(const Point& point) {
    if (!current_stroke) return;

    const auto& pts = current_stroke->getPoints();
    if (!pts.empty()) {
        const Point& last = pts.back();

        double dx = point.x - last.x;
        double dy = point.y - last.y;
        double dist = std::sqrt(dx * dx + dy * dy);

        const double spacing = 1;  // tune this value for density

        if (dist > spacing) {
            int steps = static_cast<int>(dist / spacing);
            for (int i = 1; i <= steps; ++i) {
                double t = static_cast<double>(i) / steps;
                Point interp {
                    last.x + t * dx,
                    last.y + t * dy
                };
                current_stroke->addPoint(interp);
            }
        }
    }

    current_stroke->addPoint(point);
}


void BrushTool::endStroke(const Point& end) {
    drawing = false;
    if (current_stroke) {
        current_stroke->addPoint(end);
        stroke_manager->addStroke(current_stroke);
        current_stroke.reset();
    }
}

std::shared_ptr<IStroke> BrushTool::getCurrentStroke() {
    return current_stroke;
}

bool BrushTool::isActive() const {
    return active;
}

void BrushTool::setActive(bool value) {
    active = value;
}

bool BrushTool::isDrawing() const {
    return drawing;
}