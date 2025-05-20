#include "BrushTool.h"
#include "Stroke.h"

BrushTool::BrushTool(Color color, float thickness)
    : brush_color(color), brush_thickness(thickness), active(false) {}

BrushTool::~BrushTool() = default;

void BrushTool::beginStroke(const Point& start) {
    current_stroke = std::make_shared<Stroke>(brush_color, brush_thickness);
    current_stroke->addPoint(start);
}

void BrushTool::addPoint(const Point& point) {
    if (current_stroke) {
        current_stroke->addPoint(point);
    }
}

void BrushTool::endStroke(const Point& end) {
    if (current_stroke) {
        current_stroke->addPoint(end);
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