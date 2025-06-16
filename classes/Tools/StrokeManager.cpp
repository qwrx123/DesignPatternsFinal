#include "StrokeManager.h"
#include "Stroke.h"
#include <cassert>

StrokeManager::StrokeManager(std::shared_ptr<LayerManager> layer_manager)
	: layer_manager(std::move(layer_manager))
{
}

StrokeManager::~StrokeManager() = default;

void StrokeManager::addStroke(std::shared_ptr<IStroke> stroke)
{
	auto active_layer = layer_manager->getActiveLayer();
	auto strokes	  = active_layer->getStrokes();
	strokes.push_back(stroke);
	active_layer->setStrokes(strokes);

	auto cloned = std::make_shared<Stroke>(*std::dynamic_pointer_cast<Stroke>(stroke));
	brushHistory.clearUndone();
	brushHistory.push(cloned);
}

const std::vector<std::shared_ptr<IStroke>>& StrokeManager::getStrokes() const
{
	return layer_manager->getActiveLayer()->getStrokes();
}

void StrokeManager::clear()
{
	layer_manager->getActiveLayer()->setStrokes({});
}

void StrokeManager::replaceStrokes(std::vector<std::shared_ptr<IStroke>> new_strokes)
{
	layer_manager->getActiveLayer()->setStrokes(std::move(new_strokes));
}

void StrokeManager::removeLastStroke()
{
	auto active_layer = layer_manager->getActiveLayer();
	auto strokes	  = active_layer->getStrokes();

	if (!strokes.empty())
	{
		strokes.pop_back();
		active_layer->setStrokes(strokes);
	}
}

void StrokeManager::undoStroke()
{
	if (!brushHistory.isEmpty())
	{
		brushHistory.undo();

		auto active_layer = layer_manager->getActiveLayer();
		auto strokes	  = active_layer->getStrokes();

		if (!strokes.empty())
		{
			strokes.pop_back();
			active_layer->setStrokes(strokes);
		}
	}
}

void StrokeManager::redoStroke()
{
	if (!brushHistory.isLastUndoneEmpty())
	{
		brushHistory.redo();

		auto active_layer = layer_manager->getActiveLayer();
		auto strokes	  = active_layer->getStrokes();

		strokes.push_back(brushHistory.peek());
		active_layer->setStrokes(strokes);
	}
}

void StrokeManager::undoErase()
{
	if (!eraserHistory.isEmpty())
	{
		eraserHistory.undo();
		if (!eraserHistory.isEmpty())
		{
			layer_manager->getActiveLayer()->setStrokes(eraserHistory.peek());
		}
	}
}

void StrokeManager::redoErase()
{
	if (!eraserHistory.isLastUndoneEmpty())
	{
		eraserHistory.redo();
		layer_manager->getActiveLayer()->setStrokes(eraserHistory.peek());
	}
}

History<std::shared_ptr<IStroke>> StrokeManager::getBrushHistory()
{
	return brushHistory;
}

History<std::vector<std::shared_ptr<IStroke>>> StrokeManager::getEraserHistory()
{
	return eraserHistory;
}

void StrokeManager::updateEraserHistory()
{
	auto active_layer = layer_manager->getActiveLayer();
	auto strokes	  = active_layer->getStrokes();
	eraserHistory.push(strokes);
	eraserHistory.clearUndone();
}

void StrokeManager::undoAll()
{
	eraserHistory.clear();
	brushHistory.clear();
	layer_manager->getActiveLayer()->setStrokes({});
}