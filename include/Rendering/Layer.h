#ifndef LAYER_H
#define LAYER_H

#include "IStroke.h"
#include <vector>
#include <memory>

class Layer
{
   public:
	Layer();
	~Layer() = default;

	Layer(const Layer& other)				 = default;
	Layer& operator=(const Layer& other)	 = default;
	Layer(Layer&& other) noexcept			 = default;
	Layer& operator=(Layer&& other) noexcept = default;

	void addStroke(std::shared_ptr<IStroke> stroke);
	void clear();
	[[nodiscard]] const std::vector<std::shared_ptr<IStroke>>& getStrokes() const;

   private:
	std::vector<std::shared_ptr<IStroke>> strokes;
};

#endif	// LAYER_H