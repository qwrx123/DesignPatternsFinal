#ifndef ISTROKEGENERATINGTOOL_H
#define ISTROKEGENERATINGTOOL_H

#include "IDrawingTool.h"
#include "IStroke.h"
#include <memory>

class IStrokeGeneratingTool : public IDrawingTool {
public:
    virtual ~IStrokeGeneratingTool() = default;

    virtual std::shared_ptr<IStroke> getResultingStroke() const = 0;
};

#endif // ISTROKEGENERATINGTOOL_H