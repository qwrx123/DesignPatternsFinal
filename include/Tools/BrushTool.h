#ifndef BRUSHTOOL_H
#define BRUSHTOOL_H

#include "IDrawingTool.h"
#include "IStrokeManager.h"
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

	[[nodiscard]] bool isDrawing() const override;
};

#endif	// BRUSHTOOL_H