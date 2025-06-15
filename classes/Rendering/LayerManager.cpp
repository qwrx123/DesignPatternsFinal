#include "LayerManager.h"
#include <cassert>

LayerManager::LayerManager()
{
    // Start with a default base layer
    layers.push_back(std::make_shared<Layer>());
}

bool LayerManager::addLayer() {
    if (layers.size() >= maxLayers()) {
        return false;
    }
    layers.push_back(std::make_shared<Layer>());
    return true;
}

bool LayerManager::setActiveLayer(size_t index) {
    if (index >= layers.size()) {
        return false;
    }
    active_layer_index = index;
    return true;
}

std::shared_ptr<Layer> LayerManager::getActiveLayer() const {
    assert(!layers.empty());
    return layers[active_layer_index];
}

const std::vector<std::shared_ptr<Layer>>& LayerManager::getAllLayers() const {
    return layers;
}

size_t LayerManager::getActiveLayerIndex() const {
    return active_layer_index;
}

void LayerManager::removeLayer(int index)
{
    if (index >= 0 && index < static_cast<int>(layers.size()))
    {
        layers.erase(layers.begin() + index);

        // Adjust active layer if necessary
        if (getActiveLayerIndex() >= static_cast<int>(layers.size()))
            active_layer_index = static_cast<int>(layers.size()) - 1;

        if (getActiveLayerIndex() < 0 && !layers.empty())
            active_layer_index = 0;
    }
}