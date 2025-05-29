#include "TextManager.h"
#include <algorithm>
#include <ranges>
#include <cassert>
#include <iostream>
#include <GLFW/glfw3.h>

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

void TextManager::registerTextTool(std::shared_ptr<IText> text)
{
	addText(text);
	bounds	 = text->getBounds();
	fontName = text->getFontName();
	fontSize = text->getFontSize();
	color	 = text->getColor();
}

bool TextManager::isTextToolActive() const
{
	return active;
}

void TextManager::setTextToolActive()
{
	active = true;
}

void TextManager::setTextToolInactive()
{
	active = false;
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

void TextManager::onMouseMove(double x, double y) {}
void TextManager::onMouseButton(MouseButton button, KeyAction action, double x, double y) {}
void TextManager::onKey(int key, KeyAction action)
{
	if (active && action == KeyAction::Press)
	{
		if (key == GLFW_KEY_ESCAPE)
		{
			active = false;
			std::cout << "Text tool deactivated.\n";
		}
		else if (key == GLFW_KEY_BACKSPACE)
		{
			for (auto& text : std::ranges::reverse_view(texts))
			{
				if (text->isEditable())
				{
					std::string content = text->getContent();
					if (!content.empty())
					{
						content.pop_back();
						text->setContent(content);
					}
					else if (texts.size() > 1)
					{
						removeText(text);
					}
					break;
				}
			}
		}
		else if (key == GLFW_KEY_ENTER)
		{
			Bounds prevBounds;
			if (!texts.empty())
			{
				prevBounds = texts.back()->getBounds();
			}
			else
			{
				prevBounds = bounds;
			}
			addText(std::make_shared<Text>("",
										   Bounds((static_cast<float>(fontSize) + prevBounds.top),
												  bounds.bottom, bounds.left, bounds.right),
										   fontName, fontSize, color, true));
		}
		else if (key == GLFW_KEY_TAB)
		{
			for (auto& text : std::ranges::reverse_view(texts))
			{
				if (text->isEditable())
				{
					std::string content = text->getContent();
					content += '\t';
					text->setContent(content);
					break;
				}
			}
		}
	}
}
void TextManager::onChar(unsigned int codepoint)
{
	if (active)
	{
		for (auto& text : std::ranges::reverse_view(texts))
		{
			if (text->isEditable())
			{
				std::string content = text->getContent();
				content += static_cast<char>(codepoint);
				text->setContent(content);
				break;
			}
		}
	}
}