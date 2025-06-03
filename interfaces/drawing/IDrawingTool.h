#ifndef IDRAWINGTOOL_H
#define IDRAWINGTOOL_H

#include <memory>
#include <string>
#include "IStroke.h"
#include "ITool.h"

class IDrawingTool : public ITool
{
   public:
	IDrawingTool()								 = default;
	~IDrawingTool() override					 = default;
	IDrawingTool(const IDrawingTool&)			 = default;
	IDrawingTool& operator=(const IDrawingTool&) = default;
	IDrawingTool(IDrawingTool&&)				 = default;
	IDrawingTool& operator=(IDrawingTool&&)		 = default;

	virtual void beginStroke(const Point& start) = 0;
	virtual void addPoint(const Point& point)	 = 0;
	virtual void endStroke(const Point& end)	 = 0;

	virtual std::shared_ptr<IStroke> getCurrentStroke()			   = 0;
	virtual std::string				 getName()					   = 0;
	virtual void					 setColor(const Color& color)  = 0;
	[[nodiscard]] virtual Color		 getColor() const			   = 0;
	[[nodiscard]] virtual bool		 isDrawing() const			   = 0;
	virtual void					 setThickness(float thickness) = 0;
	[[nodiscard]] virtual float		 getThickness() const		   = 0;
};

#endif	// IDRAWINGTOOL_H