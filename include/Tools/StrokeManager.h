#ifndef STROKEMANAGER_H
#define STROKEMANAGER_H

#include "IStrokeManager.h"
#include "Stroke.h"
#include "History.h"

class StrokeManager : public IStrokeManager
{
   public:
	StrokeManager();
	~StrokeManager() override;

	StrokeManager(const StrokeManager& other);
	StrokeManager& operator=(const StrokeManager& other);
	StrokeManager(StrokeManager&& other) noexcept;
	StrokeManager& operator=(StrokeManager&& other) noexcept;

	void addStroke(std::shared_ptr<IStroke> stroke) override;
	[[nodiscard]] const std::vector<std::shared_ptr<IStroke>>& getStrokes() const override;
	void													   clear() override;
	void replaceStrokes(std::vector<std::shared_ptr<IStroke>> new_strokes);
	void splitEraseWithPath(const std::shared_ptr<IStroke>& eraser_path,
							float							eraser_radius) override;
	void removeLastStroke() override;
	void undoStroke() override;
	void redoStroke() override;
	void undoErase() override;
	void redoErase() override;
	History<std::shared_ptr<IStroke>>			   getBrushHistory();
	History<std::vector<std::shared_ptr<IStroke>>> getEraserHistory();

   private:
	[[nodiscard]] std::vector<std::shared_ptr<IStroke>> cloneStrokes() const;

	std::vector<std::shared_ptr<IStroke>> strokes_;

	void							  isErased(const auto& stroke_pts, size_t i, bool& is_erased,
											   std::vector<std::shared_ptr<IStroke>>& updated_strokes,
											   std::vector<Point>& current_segment, const std::shared_ptr<IStroke>& eraser_path,
											   float eraser_radius, const std::shared_ptr<IStroke>& stroke);
	History<std::shared_ptr<IStroke>> brushHistory;
	History<std::vector<std::shared_ptr<IStroke>>> eraserHistory;
	void										   reAddStroke(std::shared_ptr<IStroke> stroke);
};

#endif	// STROKEMANAGER_H