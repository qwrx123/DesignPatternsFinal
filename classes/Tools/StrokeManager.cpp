#include "StrokeManager.h"

StrokeManager::StrokeManager() = default;

StrokeManager::~StrokeManager() = default;

void StrokeManager::addStroke(std::shared_ptr<IStroke> stroke)
{
	strokes_.push_back(std::move(stroke));
}

const std::vector<std::shared_ptr<IStroke>>& StrokeManager::getStrokes() const
{
	return strokes_;
}

void StrokeManager::clear()
{
	strokes_.clear();
}