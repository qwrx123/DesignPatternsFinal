#include "TextManager.h"
#include <algorithm>

TextManager::TextManager() = default;

TextManager::~TextManager() = default;

void TextManager::addText(std::shared_ptr<IText> text)
{
	texts.push_back(text);
}

void TextManager::removeText(std::shared_ptr<IText> text)
{
	auto it = std::ranges::remove(texts, text).begin();
	if (it != texts.end())
	{
		texts.erase(it, texts.end());
	}
}

const std::vector<std::shared_ptr<IText>>& TextManager::getTexts() const
{
	return texts;
}

std::shared_ptr<IText> TextManager::getTextAt(double x, double y) const
{
	for (const auto& text : texts)
	{
		Bounds bounds = text->getBounds();
		if (x >= bounds.left && x <= bounds.right && y >= bounds.top && y <= bounds.bottom)
		{
			return text;
		}
	}
	return nullptr;
}

void TextManager::clearAll()
{
	texts.clear();
}