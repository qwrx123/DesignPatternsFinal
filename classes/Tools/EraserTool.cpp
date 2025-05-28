#include "EraserTool.h"

EraserTool::EraserTool(std::shared_ptr<IStrokeManager> stroke_manager, float thickness)
    : stroke_manager(stroke_manager), eraser_thickness(thickness), active(false) {}

EraserTool::~EraserTool() = default;

void EraserTool::beginStroke(const Point& start) {
    // Eraser stroke is white with 0 alpha for now (can change this logic later)
    drawing = true;
    erase_path = std::make_shared<Stroke>(Color{1.0f, 1.0f, 1.0f, 0.0f}, eraser_thickness);
    erase_path->addPoint(start);
}

void EraserTool::addPoint(const Point& point) {
    if (!erase_path) return;

    erase_path->addPoint(point);

    // Create a mini path just for this point
    auto point_path = std::make_shared<Stroke>(
        Color{1.0f, 1.0f, 1.0f, 0.0f}, eraser_thickness);
    point_path->addPoint(point);

    stroke_manager->splitEraseWithPath(point_path, eraser_thickness);
}

void EraserTool::endStroke(const Point& end) {
    drawing = false;

    if (erase_path) {
        erase_path->addPoint(end);

        // Tell the stroke manager to erase intersecting segments
        stroke_manager->splitEraseWithPath(erase_path, eraser_thickness);

        erase_path = nullptr;
    }
}

std::shared_ptr<IStroke> EraserTool::getCurrentStroke() {
    return nullptr;
}

std::string EraserTool::getName() {
    return "Eraser";
}

bool EraserTool::isActive() const {
    return active;
}

void EraserTool::setActive(bool value) {
    active = value;
}

bool EraserTool::isDrawing() const {
    return drawing;
}