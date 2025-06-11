#ifndef BRUSHTOOL_H
#define BRUSHTOOL_H

#include "IDrawingTool.h"
#include "IStrokeManager.h"
#include "History.h"
#include "Stroke.h"

class BrushTool : public IDrawingTool
{
   private:
	std::shared_ptr<IStrokeManager> stroke_manager;
	std::shared_ptr<Stroke>			current_stroke;
	Color							brush_color;
	float							brush_thickness;
	bool							active;
	bool							drawing = false;

   public:
	BrushTool(std::shared_ptr<IStrokeManager> stroke_manager, Color color, float thickness);
	BrushTool(Color color, float thickness);
	~BrushTool() override;

	BrushTool(const BrushTool& other);
	BrushTool& operator=(const BrushTool& other);
	BrushTool(BrushTool&& other) noexcept;
	BrushTool& operator=(BrushTool&& other) noexcept;

	void beginStroke(const Point& start) override;
	void addPoint(const Point& point) override;
	void endStroke(const Point& end) override;

	std::shared_ptr<IStroke> getCurrentStroke() override;
	std::string				 getName() override
	{
		return "Brush";
	}
	void setColor(const Color& color) override;

	[[nodiscard]] bool isActive() const override;
	void			   setActive(bool value);

	[[nodiscard]] bool	isDrawing() const override;
	[[nodiscard]] Color getColor() const override;

	void				setThickness(float thickness) override;
	[[nodiscard]] float getThickness() const override;

	void							  undoStroke() override;
	void							  redoStroke() override;
	History<std::shared_ptr<IStroke>> getHistory() const;
};

#endif	// BRUSHTOOL_H