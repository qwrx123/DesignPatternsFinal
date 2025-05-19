#ifndef ERASERTOOL_H
#define ERASERTOOL_H

#include "IDrawingTool.h"
#include "Stroke.h"

class EraserTool : public IDrawingTool 
{
private:
    std::shared_ptr<Stroke> erase_path;
    float eraser_thickness;

public:
    EraserTool(float thickness);

    void beginStroke(const Point& start) override;
    void addPoint(const Point& point) override;
    void endStroke(const Point& end) override;
    std::shared_ptr<IStroke> getCurrentStroke() const;

    std::string getName() const { return "Eraser"; }
};

#endif // ERASERTOOL_H