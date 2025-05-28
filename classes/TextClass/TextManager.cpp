#include "TextManager.h"
#include <algorithm>
#include <cassert>

TextManager::TextManager() = default;

TextManager::~TextManager() = default;

TextManager::TextManager(const TextManager& other) : texts(std::move(other.copyTexts())) {}

TextManager& TextManager::operator=(const TextManager& other)
{
	if (this != &other)
	{
		texts = other.copyTexts();
	}
	return *this;
}

TextManager::TextManager(TextManager&& other) noexcept : texts(std::move(other.texts)) {}

TextManager& TextManager::operator=(TextManager&& other) noexcept
{
	if (this != &other)
	{
		texts = std::move(other.texts);
	}
	return *this;
}

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

std::vector<std::shared_ptr<IText>> TextManager::copyTexts() const
{
	std::vector<std::shared_ptr<IText>> clonedTexts;

	for (const auto& txt : texts)
	{
		auto txtPtr = std::dynamic_pointer_cast<Text>(txt);	 // C++ be like that
		if (txtPtr)
		{
			clonedTexts.push_back(std::make_shared<Text>(*txtPtr));
		}
		else
		{
			assert(false);	// Welp, fix this
		}
	}

	return clonedTexts;
}