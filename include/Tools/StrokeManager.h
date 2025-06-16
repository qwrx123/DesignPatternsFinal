#ifndef STROKEMANAGER_H
#define STROKEMANAGER_H

#include "IStrokeManager.h"
#include "Stroke.h"
#include "History.h"
#include "LayerManager.h"

class StrokeManager : public IStrokeManager
{
   public:
	StrokeManager(std::shared_ptr<LayerManager> layer_manager);
	~StrokeManager() override;

	StrokeManager(const StrokeManager& other)				 = delete;
	StrokeManager& operator=(const StrokeManager& other)	 = delete;
	StrokeManager(StrokeManager&& other) noexcept			 = delete;
	StrokeManager& operator=(StrokeManager&& other) noexcept = delete;

	void addStroke(std::shared_ptr<IStroke> stroke) override;
	[[nodiscard]] const std::vector<std::shared_ptr<IStroke>>& getStrokes() const override;
	void													   clear() override;
	void replaceStrokes(std::vector<std::shared_ptr<IStroke>> new_strokes) override;
	void removeLastStroke() override;
	void undoStroke() override;
	void redoStroke() override;
	History<std::shared_ptr<IStroke>> getBrushHistory() override;
	void							  undoAll() override;

   private:
	std::shared_ptr<LayerManager>	  layer_manager;
	History<std::shared_ptr<IStroke>> brushHistory;
};

#endif	// STROKEMANAGER_H