#include "TextManager.h"
#include <algorithm>
#include <cassert>
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
}

bool TextManager::isTextToolActive()
{
	return active;
}

void TextManager::setTextToolActive()
{
	active = true;
}

void TextManager::addText(std::shared_ptr<IText> text)
{
	texts.push_back(text);
}

void TextManager::removeText(std::shared_ptr<IText> text)
{
	auto it = std::remove(texts.begin(), texts.end(), text);
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
	// Handle key input
	if (active && action == KeyAction::Press)
	{
		if (key == GLFW_KEY_ESCAPE)	 // Example: deactivate text tool on Escape key
		{
			active = false;
		}
		else if (key == GLFW_KEY_BACKSPACE)	 // Example: handle backspace
		{
			for (const auto& text : texts)
			{
				if (text->isEditable())
				{
					std::string content = text->getContent();
					if (!content.empty())
					{
						content.pop_back();	 // Remove last character
						text->setContent(content);
					}
					break;	// Only modify the first editable text
				}
			}
		}
	}
	else if (active && action == KeyAction::Release)
	{
		// Handle other key releases if needed
	}
}
void TextManager::onChar(unsigned int codepoint)
{
	// Handle character input
	if (active)
	{
		for (const auto& text : texts)
		{
			if (text->isEditable())
			{
				std::string content = text->getContent();
				content += static_cast<char>(codepoint);
				text->setContent(content);
				break;	// Only modify the first editable text
			}
		}
	}
}