#ifndef LAYER_H
#define LAYER_H

#include "IStroke.h"
#include "History.h"
#include <vector>
#include <memory>
#include <string>

class Layer
{
   public:
	Layer();
	~Layer() = default;

	Layer(const Layer& other)				 = default;
	Layer& operator=(const Layer& other)	 = default;
	Layer(Layer&& other) noexcept			 = default;
	Layer& operator=(Layer&& other) noexcept = default;

	void					  setName(const std::string& name);
	[[nodiscard]] std::string getName() const;

	void addStroke(std::shared_ptr<IStroke> stroke);
	void setStrokes(std::vector<std::shared_ptr<IStroke>> new_strokes);
	void clear();
	[[nodiscard]] const std::vector<std::shared_ptr<IStroke>>& getStrokes() const;

	void														 updateEraserHistory();
	void														 undoErase();
	void														 redoErase();
	[[nodiscard]] History<std::vector<std::shared_ptr<IStroke>>> getEraserHistory() const;

   private:
	std::vector<std::shared_ptr<IStroke>>		   strokes;
	History<std::vector<std::shared_ptr<IStroke>>> eraserHistory;
	std::string									   layerName;
};

#endif	// LAYER_H