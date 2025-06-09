#include "TextManager.h"
#include <algorithm>
#include <ranges>
#include <cassert>
#include <GLFW/glfw3.h>

TextManager::TextManager() : bounds({.top = 0, .bottom = 0, .left = 0, .right = 0}) {};

TextManager::~TextManager() = default;

TextManager::TextManager(const TextManager& other)
	: texts(std::move(other.copyTexts())), bounds(other.bounds)
{
}

TextManager& TextManager::operator=(const TextManager& other)
{
	if (this != &other)
	{
		texts = other.copyTexts();
	}
	return *this;
}

TextManager::TextManager(TextManager&& other) noexcept
	: texts(std::move(other.texts)), bounds(other.bounds)
{
}

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
	textHistory.undo();
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
	if (active && (action == KeyAction::Press || action == KeyAction::Repeat))
	{
		if (key == GLFW_KEY_ESCAPE)
		{
			active = false;
		}
		else if (key == GLFW_KEY_BACKSPACE)
		{
			handleBackspace();
		}
		else if (key == GLFW_KEY_ENTER)
		{
			handleEnter();
		}
		else if (key == GLFW_KEY_TAB)
		{
			insertTab();
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
				textHistory.push(std::make_shared<Text>(text->getContent(), text->getBounds(),
														text->getFontName(), text->getFontSize(),
														text->getColor(), text->isEditable()));
				break;
			}
		}
	}
}

void TextManager::insertTab()
{
	for (auto& text : std::ranges::reverse_view(texts))
	{
		if (text->isEditable())
		{
			std::string content = text->getContent();
			content += '\t';
			text->setContent(content);
			textHistory.push(std::make_shared<Text>(text->getContent(), text->getBounds(),
													text->getFontName(), text->getFontSize(),
													text->getColor(), text->isEditable()));
		}
		break;
	}
}

void TextManager::handleBackspace()
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
				textHistory.push(std::make_shared<Text>(text->getContent(), text->getBounds(),
														text->getFontName(), text->getFontSize(),
														text->getColor(), text->isEditable()));
			}
			else if (texts.size() > 1)
			{
				removeText(text);
			}
			break;
		}
	}
}

void TextManager::handleEnter()
{
	Bounds prevBounds	= {};
	int	   prevFontSize = fontSize;
	Color  prevColor	= color;
	if (!texts.empty())
	{
		prevBounds	 = texts.back()->getBounds();
		prevFontSize = texts.back()->getFontSize();
		prevColor	 = texts.back()->getColor();
	}
	else
	{
		prevBounds = bounds;
	}
	addText(std::make_shared<Text>("",
								   Bounds((static_cast<float>(prevFontSize) + prevBounds.top),
										  bounds.bottom, bounds.left, bounds.right),
								   fontName, prevFontSize, prevColor, true));
	textHistory.push(std::make_shared<Text>(
		texts.back()->getContent(), texts.back()->getBounds(), texts.back()->getFontName(),
		texts.back()->getFontSize(), texts.back()->getColor(), texts.back()->isEditable()));
}
void TextManager::setFontSize(int size)
{
	fontSize = size;
	for (auto& text : texts)
	{
		text->setFontSize(size);
	}
}

void TextManager::undoText()
{
	if (!textHistory.isEmpty())
	{
		textHistory.undo();
		texts.back() = textHistory.peek();
	}
}

void TextManager::redoText()
{
	if (!textHistory.isLastUndoneEmpty())
	{
		textHistory.redo();
		texts.back() = textHistory.peek();
	}
}

TextHistory TextManager::getHistory()
{
	return textHistory;
}