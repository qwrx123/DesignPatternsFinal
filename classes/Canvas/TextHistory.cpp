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
	auto text = history.back();
	history.pop_back();
	undoneHistory.push_back(text);
	return text;
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

void TextHistory::redo()
{
	if (!undoneHistory.empty())
	{
		auto text = undoneHistory.back();
		push(text);
		undoneHistory.pop_back();
	}
}

void TextHistory::undo()
{
	pop();
}
