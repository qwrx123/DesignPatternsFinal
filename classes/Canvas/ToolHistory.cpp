#include "ToolHistory.h"

void ToolHistory::push(std::shared_ptr<IStroke> tool)
{
	history.push_back(tool);
}
void ToolHistory::pop()
{
	if (history.empty())
	{
		undoneHistory.push_back(history.back());
		history.pop_back();
	}
}
std::shared_ptr<IStroke> ToolHistory::peek()
{
	if (history.empty())
	{
		return nullptr;
	}
	return history.back();
}
std::vector<std::shared_ptr<IStroke>> ToolHistory::getHistory()
{
	return history;
}
bool ToolHistory::isEmpty() const
{
	return history.empty();
}
size_t ToolHistory::size() const
{
	return history.size();
}
std::shared_ptr<IStroke> ToolHistory::redo()
{
	if (!undoneHistory.empty())
	{
		push(undoneHistory.back());
		undoneHistory.pop_back();
		return peek();
	}
	return nullptr;
}
void ToolHistory::undo()
{
	if (!history.empty())
	{
		pop();
	}
}
std::shared_ptr<IStroke> ToolHistory::peekLastUndone() const
{
	if (undoneHistory.empty())
	{
		return nullptr;
	}
	return undoneHistory.back();
}
bool ToolHistory::isLastUndoneEmpty() const
{
	return undoneHistory.empty();
}
size_t ToolHistory::undoneSize() const
{
	return undoneHistory.size();
}
std::vector<std::shared_ptr<IStroke>> ToolHistory::getUndoneHistory() const
{
	return undoneHistory;
}