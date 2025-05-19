#ifndef BRUSHTOOL_H
#define BRUSHTOOL_H

#include "IDrawingTool.h"
#include "Stroke.h"

class BrushTool : public IDrawingTool {
private:
    std::shared_ptr<Stroke> current_stroke;
    Color brush_color;
    float brush_thickness;

public:
    BrushTool(Color color, float thickness);
	~BrushTool();

	void beginStroke(const Point& start) override;
    void addPoint(const Point& point) override;
    void endStroke(const Point& end) override;
    
    std::shared_ptr<IStroke> getCurrentStroke() const;
    std::string getName() const { return "Brush"; }
};

#endif // BRUSHTOOL_H