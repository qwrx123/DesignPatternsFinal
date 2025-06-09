#include "Layer.h"

Layer::Layer() = default;

void Layer::addStroke(std::shared_ptr<IStroke> stroke) {
    strokes.push_back(std::move(stroke));
}

void Layer::clear() {
    strokes.clear();
}

const std::vector<std::shared_ptr<IStroke>>& Layer::getStrokes() const {
    return strokes;
}