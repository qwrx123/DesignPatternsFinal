#include "Layer.h"

Layer::Layer() : layerName("Layer 1") {}

void Layer::setName(const std::string& name)
{
    layerName = name;
}

std::string Layer::getName() const
{
    return layerName;
}

void Layer::addStroke(std::shared_ptr<IStroke> stroke)
{
    strokes.push_back(std::move(stroke));
}

void Layer::setStrokes(std::vector<std::shared_ptr<IStroke>> new_strokes)
{
    strokes = std::move(new_strokes);
}

void Layer::clear()
{
    strokes.clear();
}

const std::vector<std::shared_ptr<IStroke>>& Layer::getStrokes() const
{
    return strokes;
}

void Layer::updateEraserHistory()
{
    if (eraserHistory.isEmpty())
    {
        eraserHistory.push(strokes);
    }

    eraserHistory.push(strokes);
    eraserHistory.clearUndone();
}


void Layer::undoErase()
{
    if (!eraserHistory.isEmpty())
    {
        eraserHistory.undo();
        if (!eraserHistory.isEmpty())
        {
            strokes = eraserHistory.peek();
        }
    }
}

void Layer::redoErase()
{
    if (!eraserHistory.isLastUndoneEmpty())
    {
        eraserHistory.redo();
        strokes = eraserHistory.peek();
    }
}

History<std::vector<std::shared_ptr<IStroke>>> Layer::getEraserHistory() const
{
    return eraserHistory;
}