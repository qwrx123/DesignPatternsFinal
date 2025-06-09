#include "TextHistory.h"

void TextHistory::push(std::shared_ptr<IText> text)
{
	history.push_back(text);
}

std::shared_ptr<IText> TextHistory::pop()
{
	if (history.empty())
	{
		return nullptr;
	}
	undoneHistory.push_back(history.back());
	history.pop_back();
	return history.back();
}

std::shared_ptr<IText> TextHistory::peek()
{
	if (history.empty())
	{
		return nullptr;
	}
	return history.back();
}

std::vector<std::shared_ptr<IText>> TextHistory::getHistory()
{
	return history;
}

bool TextHistory::isEmpty() const
{
	return history.empty();
}

size_t TextHistory::size() const
{
	return history.size();
}

std::shared_ptr<IText> TextHistory::redo()
{
	if (!undoneHistory.empty())
	{
		push(undoneHistory.back());
		undoneHistory.pop_back();
		return peek();
	}
	return nullptr;
}

std::shared_ptr<IText> TextHistory::undo()
{
	if (!history.empty())
	{
		return pop();
	}
	return nullptr;
}

std::shared_ptr<IText> TextHistory::peekLastUndone() const
{
	if (undoneHistory.empty())
	{
		return nullptr;
	}
	return undoneHistory.back();
}

bool TextHistory::isLastUndoneEmpty() const
{
	return undoneHistory.empty();
}

size_t TextHistory::undoneSize() const
{
	return undoneHistory.size();
}

std::vector<std::shared_ptr<IText>> TextHistory::getUndoneHistory() const
{
	return undoneHistory;
}
