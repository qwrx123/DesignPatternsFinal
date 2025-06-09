#ifndef LAYER_MANAGER_H
#define LAYER_MANAGER_H

#include "Layer.h"
#include <memory>
#include <vector>
#include <string>

class LayerManager
{
   public:
	LayerManager();
	~LayerManager() = default;

	LayerManager(const LayerManager& other)				   = default;
	LayerManager& operator=(const LayerManager& other)	   = delete;
	LayerManager(LayerManager&& other) noexcept			   = default;
	LayerManager& operator=(LayerManager&& other) noexcept = delete;

	// Attempts to add a new layer, returns true if successful
	bool addLayer();

	// Sets active layer by index (0-based), returns false if invalid index
	bool setActiveLayer(size_t index);

	// Returns currently active layer
	[[nodiscard]] std::shared_ptr<Layer> getActiveLayer() const;

	// Returns all layers (for rendering or UI display)
	[[nodiscard]] const std::vector<std::shared_ptr<Layer>>& getAllLayers() const;

	// Returns the index of the currently active layer
	[[nodiscard]] size_t getActiveLayerIndex() const;

	// Returns max allowed layers
	static size_t maxLayers()
	{
		return maxNumOfLayers;
	}

   private:
	std::vector<std::shared_ptr<Layer>> layers;
	size_t								active_layer_index = 0;
	static constexpr size_t				maxNumOfLayers	   = 5;
};

#endif	// LAYER_MANAGER_H