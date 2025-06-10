#ifndef ERASER_TOOL_H
#define ERASER_TOOL_H

#include "IDrawingTool.h"
#include "IStrokeManager.h"
#include "ToolHistory.h"
#include "Stroke.h"

class EraserTool : public IDrawingTool
{
   public:
	EraserTool(std::shared_ptr<IStrokeManager> stroke_manager, float thickness);
	~EraserTool() override;

	EraserTool(const EraserTool&)			 = default;
	EraserTool& operator=(const EraserTool&) = default;
	EraserTool(EraserTool&&)				 = default;
	EraserTool& operator=(EraserTool&&)		 = default;

	void beginStroke(const Point& start) override;
	void addPoint(const Point& point) override;
	void endStroke(const Point& end) override;

	std::shared_ptr<IStroke> getCurrentStroke() override;
	std::string				 getName() override;
	void					 setColor(const Color& color) override;

	[[nodiscard]] bool isActive() const override;
	void			   setActive(bool value);

	[[nodiscard]] bool	isDrawing() const override;
	[[nodiscard]] Color getColor() const override;

	void				setThickness(float thickness) override;
	[[nodiscard]] float getThickness() const override;

	void		undoStroke() override;
	void		redoStroke() override;
	ToolHistory getHistory() const;

   private:
	std::shared_ptr<Stroke>			erase_path;
	std::shared_ptr<IStrokeManager> stroke_manager;
	float							eraser_thickness;
	bool							active		 = false;
	bool							drawing		 = false;
	Color							eraser_color = {.r = 1.0F, .g = 1.0F, .b = 1.0F, .a = 0.0F};
};

#endif	// ERASER_TOOL_H