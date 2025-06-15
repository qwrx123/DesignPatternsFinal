#include "Layer.h"

Layer::Layer() : layerName("Layer 1") {}


void Layer::setName(const std::string& name) 
{ 
    layerName = name; 
}

std::string Layer::getName() const 
{ 
    return layerName; 
}

void Layer::addStroke(std::shared_ptr<IStroke> stroke) {
    strokes.push_back(std::move(stroke));
}

void Layer::setStrokes(std::vector<std::shared_ptr<IStroke>> new_strokes) {
	strokes = std::move(new_strokes);
}

void Layer::clear() {
    strokes.clear();
}

const std::vector<std::shared_ptr<IStroke>>& Layer::getStrokes() const {
    return strokes;
}