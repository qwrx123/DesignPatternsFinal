#include "StrokeManager.h"
#include "Stroke.h"	 //womp womp
#include <cassert>

StrokeManager::StrokeManager() = default;

StrokeManager::~StrokeManager() = default;

StrokeManager::StrokeManager(const StrokeManager& other) : strokes_(std::move(other.cloneStrokes()))
{
}

StrokeManager& StrokeManager::operator=(const StrokeManager& other)
{
	if (this == &other)
	{
		return *this;
	}

	strokes_ = std::move(other.cloneStrokes());

	return *this;
}

StrokeManager::StrokeManager(StrokeManager&& other) noexcept : strokes_(std::move(other.strokes_))
{
}

StrokeManager& StrokeManager::operator=(StrokeManager&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	strokes_ = std::move(other.strokes_);

	return *this;
}

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

std::vector<std::shared_ptr<IStroke>> StrokeManager::cloneStrokes() const
{
	std::vector<std::shared_ptr<IStroke>> clonedStrokes;

	for (const auto& btn : strokes_)
	{
		auto strkPtr = std::dynamic_pointer_cast<Stroke>(btn);	// C++ be like that
		if (strkPtr)
		{
			clonedStrokes.push_back(std::make_shared<Stroke>(*strkPtr));
		}
		else
		{
			assert(false);	// Welp, fix this
		}
	}

	return clonedStrokes;
}
