#ifndef IDRAWINGTOOL_H
#define IDRAWINGTOOL_H

#include "ITool.h"

class IDrawingTool : ITool {
public:
    IDrawingTool()			= default;
    virtual ~IDrawingTool() = default;

    virtual void beginStroke(double x, double y) = 0;
    virtual void addPoint(double x, double y)	 = 0;
    virtual void endStroke()					 = 0;
};

#endif // IDRAWINGTOOL_H