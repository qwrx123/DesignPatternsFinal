#include "MenuBar.h"
#include "Bounds.h"
#include "ButtonClass.h"
#include "SliderButton.h"
#include <iostream>
#include <cmath>
#include <cassert>
#include <string>
#include <GLFW/glfw3.h>

const int defaultButtonWidth = 50;
const int defaultSliderWidth = 100;
const int sliderMargin = 7;
const int exportButtonMargin = 100;

const Color black	 = {.r = 0.0F, .g = 0.0F, .b = 0.0F, .a = 1.0F};
const Color brown = {.r = 0.45F, .g = 0.24F, .b = 0.06F, .a = 1.0F};
const Color red	 = {.r = 1.0F, .g = 0.0F, .b = 0.0F, .a = 1.0F};
const Color orange = {.r = 1.0F, .g = 0.5F, .b = 0.1F, .a = 1.0F};
const Color yellow = {.r = 0.9F, .g = 0.9F, .b = 0.0F, .a = 1.0F};
const Color green	 = {.r = 0.0F, .g = 0.7F, .b = 0.1F, .a = 1.0F};
const Color teal = {.r = 0.0F, .g = 0.51F, .b = 0.51F, .a = 1.0F};
const Color blue	 = {.r = 0.0F, .g = 0.2F, .b = 0.9F, .a = 1.0F};
const Color purple = {.r = 0.6F, .g = 0.0F, .b = 0.6F, .a = 1.0F};
const Color pink = {.r = 1.0F, .g = 0.36F, .b = 0.61F, .a = 1.0F};
const Color white	 = {.r = 1.0F, .g = 1.0F, .b = 1.0F, .a = 1.0F};
const Color gray = {.r = 0.5F, .g = 0.5F, .b = 0.5F, .a = 1.0F};

const int minFontSize = 12;
const int maxFontSize = 96;
const float thicknessConversionFactor = 40.0F;

MenuBar::MenuBar() : label("Menu Bar"), bounds{.top = 0,.bottom = 0,.left = 0,.right = 0}, tool(nullptr)
{
	buttons.push_back(
		std::make_shared<ButtonClass>("emptyEdge", Bounds{.top = 0,.bottom = 0,.left = 0,.right = 0}, Color{.r = 0,.g = 0,.b = 0,.a = 0}));
}

MenuBar::~MenuBar()
{
	if (!buttons.empty())
	{
		buttons.clear();
	}
}

MenuBar::MenuBar(const MenuBar& other)
	: label(other.label),
	  bounds(other.bounds),
	  selectedIndex(other.selectedIndex),
	  buttons(std::move(other.cloneButtons())), halfHeight(other.halfHeight), quarterHeight(other.quarterHeight)
{
}

MenuBar& MenuBar::operator=(const MenuBar& other)
{
	if (this != &other)
	{
		label		  = other.label;
		bounds		  = other.bounds;
		selectedIndex = other.selectedIndex;
		buttons.clear();

		buttons = std::move(other.cloneButtons());
	}
	return *this;
}

MenuBar::MenuBar(MenuBar&& other) noexcept
	: label(std::move(other.label)),
	  bounds(other.bounds),
	  selectedIndex(other.selectedIndex),
	  buttons(std::move(other.buttons)),
	  halfHeight(other.halfHeight),
	  quarterHeight(other.quarterHeight)
{
}

MenuBar& MenuBar::operator=(MenuBar&& other) noexcept
{
	if (this != &other)
	{
		label		  = std::move(other.label);
		bounds		  = other.bounds;
		selectedIndex = other.selectedIndex;
		buttons		  = std::move(other.buttons);

		other.selectedIndex = 0;  // Reset moved-from state
	}
	return *this;
}

std::string MenuBar::getLabel() const
{
	return label;
}

void MenuBar::setLabel(const std::string& label)
{
	this->label = label;
}

Bounds MenuBar::getBounds() const
{
	return bounds;
}

void MenuBar::setBounds(const Bounds& bounds)
{
	this->bounds = bounds;
	halfHeight = (bounds.bottom / 2) - bounds.top;
	quarterHeight = (bounds.bottom / 4) - bounds.top;
}

bool MenuBar::isOpen() const
{
	return true;
}

void MenuBar::open() {}

void MenuBar::close() {}

void MenuBar::setDefaultButtons()
{
	float firstDiv = bounds.top + quarterHeight;
	float midDiv = bounds.top + halfHeight;
	float thirdDiv = bounds.top + halfHeight + quarterHeight;
	selectedIndex = 1;

	//Half size tool buttons
	addButton(std::make_shared<ButtonClass>(
		"Brush",
		Bounds{.top	   = bounds.top,
			   .bottom = midDiv,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().right + 1,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right + defaultButtonWidth},
		white));
	addButton(std::make_shared<ButtonClass>(
		"Eraser",
		Bounds{.top	   = midDiv,
			   .bottom = bounds.bottom,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		white));

	addButton(std::make_shared<ButtonClass>(
		"Text",
		Bounds{.top	   = bounds.top,
			   .bottom = midDiv,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().right + 1,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right + defaultButtonWidth},
		white));

	// Size slider
	addButton(std::make_shared<SliderButton>(
		"size",
		Bounds{.top	   = bounds.top,
			   .bottom = firstDiv,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().right + sliderMargin,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right + defaultSliderWidth},
		gray));

	//Quarter size color buttons
	addButton(std::make_shared<ButtonClass>(
		"color",
		Bounds{.top	   = bounds.top,
			   .bottom = firstDiv,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().right + sliderMargin,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right + sliderMargin + quarterHeight},
		black));
	addButton(std::make_shared<ButtonClass>(
		"color",
		Bounds{.top	   = firstDiv,
			   .bottom = midDiv,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		brown));
	addButton(std::make_shared<ButtonClass>(
		"color",
		Bounds{.top	   = midDiv,
			   .bottom = thirdDiv,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		red));
	addButton(std::make_shared<ButtonClass>(
		"color",
		Bounds{.top	   = thirdDiv,
			   .bottom = bounds.bottom,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		orange));

	addButton(std::make_shared<ButtonClass>(
		"color",
		Bounds{.top	   = bounds.top,
			   .bottom = firstDiv,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().right + 1,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right + quarterHeight},
		yellow));
	addButton(std::make_shared<ButtonClass>(
		"color",
		Bounds{.top	   = firstDiv,
			   .bottom = midDiv,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		green));
	addButton(std::make_shared<ButtonClass>(
		"color",
		Bounds{.top	   = midDiv,
			   .bottom = thirdDiv,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		teal));
	addButton(std::make_shared<ButtonClass>(
		"color",
		Bounds{.top	   = thirdDiv,
			   .bottom = bounds.bottom,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		blue));

	addButton(std::make_shared<ButtonClass>(
		"color",
		Bounds{.top	   = bounds.top,
			   .bottom = firstDiv,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().right + 1,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right + quarterHeight},
		purple));
	addButton(std::make_shared<ButtonClass>(
		"color",
		Bounds{.top	   = firstDiv,
			   .bottom = midDiv,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		pink));
	addButton(std::make_shared<ButtonClass>(
		"color",
		Bounds{.top	   = midDiv,
			   .bottom = thirdDiv,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		white));
	addButton(std::make_shared<ButtonClass>(
		"color",
		Bounds{.top	   = thirdDiv,
			   .bottom = bounds.bottom,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		gray));
	
	// Color sliders
	addButton(std::make_shared<SliderButton>(
		"red",
		Bounds{.top	   = bounds.top,
			   .bottom = firstDiv,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().right + sliderMargin,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right + defaultSliderWidth},
		red));
	addButton(std::make_shared<SliderButton>(
		"green",
		Bounds{.top	   = firstDiv,
			   .bottom = midDiv,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		green));
	addButton(std::make_shared<SliderButton>(
		"blue",
		Bounds{.top	   = midDiv,
			   .bottom = thirdDiv,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		blue));
	addButton(std::make_shared<SliderButton>(
		"opacity",
		Bounds{.top	   = thirdDiv,
			   .bottom = bounds.bottom,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		black));
	
	setSliderButtonValues();

	addButton(std::make_shared<ButtonClass>(
		"export",
		Bounds{.top	   = midDiv,
			   .bottom = bounds.bottom,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().right + 1,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right + defaultButtonWidth},
		gray));
	// Undo and Redo
	addButton(std::make_shared<ButtonClass>(
		"Undo Text",
		Bounds{.top	   = bounds.top,
			   .bottom = firstDiv,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().right + 1,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right + defaultSliderWidth},
		white));
	addButton(std::make_shared<ButtonClass>(
		"Redo Text",
		Bounds{.top	   = firstDiv,
			   .bottom = midDiv,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		white));
	addButton(std::make_shared<ButtonClass>(
		"Undo Strokes",
		Bounds{.top	   = midDiv,
			   .bottom = thirdDiv,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		white));
	addButton(std::make_shared<ButtonClass>(
		"Redo Strokes",
		Bounds{.top	   = thirdDiv,
			   .bottom = bounds.bottom,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		white));
	addButton(std::make_shared<ButtonClass>(
		"Clear Text",
		Bounds{.top	   = bounds.top,
			   .bottom = midDiv,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().right + 1,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right + defaultSliderWidth},
		red));
	addButton(std::make_shared<ButtonClass>(
		"Clear Strokes",
		Bounds{.top	   = midDiv,
			   .bottom = bounds.bottom,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		red));

	// Add Layer button
	addButton(std::make_shared<ButtonClass>(
    	"Add Layer",
    	Bounds{
     		.top = bounds.top,
        	.bottom = midDiv,
        	.left = buttons.at(buttons.size() - 1)->getBounds().right + 1,
        	.right = buttons.at(buttons.size() - 1)->getBounds().right + defaultSliderWidth},
    	white));

	// Rename Layer button
	addButton(std::make_shared<ButtonClass>(
    	"Rename Layer",
    	Bounds{
        	.top = midDiv,
        	.bottom = bounds.bottom,
        	.left = buttons.at(buttons.size() - 1)->getBounds().left,
			.right  = buttons.at(buttons.size() - 1)->getBounds().right},
    	white));

	// Layer dropdown menu
	addButton(std::make_shared<ButtonClass>(
    	"Select Layer",
    	Bounds{
        	.top = bounds.top,
        	.bottom = midDiv,
        	.left = buttons.at(buttons.size() - 1)->getBounds().right + 1,
        	.right = buttons.at(buttons.size() - 1)->getBounds().right + defaultSliderWidth},
    	white));
}

void MenuBar::addButton(std::shared_ptr<IButton> button)
{
	buttons.push_back(button);
}

void MenuBar::clearButtons()
{
	buttons.clear();
}

const std::vector<std::shared_ptr<IButton>>& MenuBar::getButtons() const
{
	return buttons;
}

int MenuBar::getSelectedIndex() const
{
	return selectedIndex;
}

void MenuBar::setSelectedIndex(int index)
{
	selectedIndex = index;
}

std::shared_ptr<IButton> MenuBar::getSelectedItem() const
{
	return buttons.at(selectedIndex);
}

bool MenuBar::showSelectedLabelWhenClosed() const
{
	return false;
}

void MenuBar::setShowSelectedLabelWhenClosed(bool show) {}

void MenuBar::onMouseMove(double x, double y)
{
	for (auto& button : buttons) {
		auto slider = std::dynamic_pointer_cast<SliderButton>(button);
		if (slider && slider->isPressed()) {
			std::string label = slider->getLabel();
			sliderLogic(slider, label, x, y);
			setSliderButtonValues();
		}
	}
}

void MenuBar::onMouseButton(MouseButton click, KeyAction action, double x, double y)
{
    int itCount = 0;
    bool clickedInsideDropdown = false;

    for (auto& button : buttons)
    {
        if (button->getBounds().contains(x, y))
        {
            std::string label = button->getLabel();

            if (action == KeyAction::Press)
            {
                handleButtonPress(button, label, x, y, itCount);
            }

            if (button->isPressed() && label == "color" && buttons.at(selectedIndex)->getLabel() != "Eraser" &&
                action == KeyAction::Release)
            {
                buttons.at(selectedIndex)->setColor(button->getColor());
                setSliderButtonValues();
            }

            if (action == KeyAction::Release)
            {
                handleButtonRelease(button, label);
            }

            if (isDropdownButton(label))
            {
                clickedInsideDropdown = true;
            }
        }
        itCount++;
    }

    handleDropdownButtons(action, x, y, clickedInsideDropdown);

    if (dropdownOpen && !clickedInsideDropdown && action == KeyAction::Press)
    {
        dropdownOpen = false;
        layerDropdownButtons.clear();
        layerDeleteButtons.clear();
    }
}

void MenuBar::handleButtonPress(const std::shared_ptr<IButton>& button, const std::string& label, double x, double y, int itCount)
{
    button->setPressed(true);

    if (label == "Add Layer" || label == "Select Layer" || label == "Brush" || 
        label == "Undo Text" || label == "Redo Text" || label == "Undo Strokes" || label == "Redo Strokes")
    {
        button->setColor(gray);
    }

    onButton(button, label, x, y, itCount);
}

void MenuBar::handleButtonRelease(const std::shared_ptr<IButton>& button, const std::string& label)
{
    button->setPressed(false);

    if (label == "Add Layer" || label == "Select Layer" || label == "Undo Text" || label == "Redo Text" 
        || label == "Undo Strokes" || label == "Redo Strokes")
    {
        button->setColor(white);
    }

    if (label == "Brush")
    {
        Color brushColor = tool->getActiveTool()->getColor();
        button->setColor(brushColor);
    }
}

bool MenuBar::isDropdownButton(const std::string& label)
{
    return (label == "Select Layer" || label == "Add Layer" || label == "Rename Layer");
}

void MenuBar::handleDropdownButtons(KeyAction action, double x, double y, bool& clickedInsideDropdown)
{
	if (!dropdownOpen) 
	{
		return;
	}

    // Handle layer delete clicks
    for (size_t i = 0; i < layerDeleteButtons.size(); ++i)
    {
        auto& delBtn = layerDeleteButtons[i];
        if (delBtn->getBounds().contains(x, y) && action == KeyAction::Press && layerDeleteButtons.size() > 1)
        {
            layerManager->removeLayer((int)i);
            clickedInsideDropdown = true;
            return;
        }
    }

    // Handle layer selection clicks
    for (size_t i = 0; i < layerDropdownButtons.size(); ++i)
    {
        auto& btn = layerDropdownButtons[i];
        if (btn->getBounds().contains(x, y) && action == KeyAction::Press)
        {
            layerManager->setActiveLayer(static_cast<int>(i));
            clickedInsideDropdown = true;
        }
    }
}

void MenuBar::onKey(int key, KeyAction action)
{
    if (!renamingLayer) 
	{
		return;
	}

    if (key == GLFW_KEY_BACKSPACE && action == KeyAction::Press)
    {
        if (!renameBuffer.empty())
		{
            renameBuffer.pop_back();
		}
    }
    else if (key == GLFW_KEY_ENTER && action == KeyAction::Press)
    {
        // Apply the name change
        layerManager->getAllLayers()[layerBeingRenamed]->setName(renameBuffer);
        renamingLayer = false;
        layerBeingRenamed = -1;

		for (auto& btn : buttons)
    	{
        	if (btn->getLabel() == "Rename Layer")
        	{
            	btn->setColor(white);
        	}
    	}
    }
}

void MenuBar::onChar(unsigned int codepoint) {
	if (renamingLayer)
    {
        renameBuffer += static_cast<char>(codepoint);
    }
}

void MenuBar::onResize(int width, int height)
{
	setBounds(Bounds{.top = bounds.top, .bottom = bounds.bottom, .left = bounds.left, .right = (float)width});
}

void MenuBar::setToolPointer(const std::shared_ptr<IToolManager>& ptr)
{
	tool = ptr;
}

void MenuBar::setTextPointer(const std::shared_ptr<ITextManager>& ptr)
{
	text = ptr;
}

void MenuBar::setLayerPointer(std::shared_ptr<LayerManager> ptr) {
	layerManager = std::move(ptr);
}

std::vector<std::shared_ptr<IButton>> MenuBar::cloneButtons() const
{
	std::vector<std::shared_ptr<IButton>> clonedButtons;

	for (const auto& btn : buttons)
	{
		auto btnPtr = std::dynamic_pointer_cast<ButtonClass>(btn);	// C++ be like that
		if (btnPtr)
		{
			clonedButtons.push_back(std::make_shared<ButtonClass>(*btnPtr));
		}
		else
		{
			assert(false);	// Welp, fix this
		}
	}

	return clonedButtons;
}

void MenuBar::setSliderButtonValues()
{
	for (auto& slider : buttons)
	{
		if (slider->getLabel() == "size") {
			slider->setValue(tool->getActiveTool()->getThickness() / thicknessConversionFactor);
		}
		else if (slider->getLabel() == "red")
		{
			slider->setValue(tool->getActiveTool()->getColor().r);
		}
		else if (slider->getLabel() == "green")
		{
			slider->setValue(tool->getActiveTool()->getColor().g);
		}
		else if (slider->getLabel() == "blue")
		{
			slider->setValue(tool->getActiveTool()->getColor().b);
		}
		else if (slider->getLabel() == "opacity")
		{
			slider->setValue(tool->getActiveTool()->getColor().a);
		}
	}

}

float MenuBar::sliderValueCalc(const std::shared_ptr<SliderButton>& slider, double x)
{
	float minValue = slider->getMinValue();
	float maxValue = slider->getMaxValue();
	Bounds  bounds   = slider->getBounds();
	float sliderStart = bounds.left;
	float sliderEnd   = bounds.right;
	float t = (static_cast<float>(x) - sliderStart) / (sliderEnd - sliderStart);
	if (t < 0.0F) 
	{
		t = 0.0F;
	}
	else if (t > 1.0F) 
	{
		t = 1.0F;
	}
	float value = minValue + (t * (maxValue - minValue));
	return value;
}

void MenuBar::onButton(const std::shared_ptr<IButton>& button, const std::string& label, double x,
					 double y, int itCount)
{
	onToolButton(button, label, x, y, itCount);
	onColorButton(button, label, x, y, itCount);
	onHistoryButton(button, label, x, y, itCount);

	if (label == "Add Layer")
	{
    	if (layerManager && layerManager->getAllLayers().size() < layerManager->maxLayers()) {
        	layerManager->addLayer();
    	}
	}
	else if (label == "Select Layer")
	{
		dropdownOpen = !dropdownOpen;

    	if (!dropdownOpen)
    	{
        	layerDropdownButtons.clear();
        	layerDeleteButtons.clear();
    	}
	}
	else if (label == "Rename Layer")
	{
    	if (layerManager && !layerManager->getAllLayers().empty())
    	{
        	renamingLayer = true;
        	layerBeingRenamed = (int)layerManager->getActiveLayerIndex();
			renameBuffer.clear();
    	}
		button->setColor(gray);
	}
	else
	{
		tool->selectTool(label);
		selectedIndex = itCount; // These lines may or may not need to be removed

		// Visual feedback for Eraser button state
    	for (auto& btn : buttons)
    	{
        	if (btn->getLabel() == "Eraser")
        	{
            	if (label == "Eraser")
            	{
                	btn->setColor(gray);
            	}
            	else if (label == "Brush")
            	{
                	btn->setColor(white);
            	}
        	}
    	}
	}
}

void MenuBar::sliderLogic(const std::shared_ptr<SliderButton>& slider, const std::string& label, double x, double y)
{
	float value = sliderValueCalc(slider, x);

	if (label == "size")
	{
		tool->getActiveTool()->setThickness(value * thicknessConversionFactor);

		if (text->isTextToolActive())
		{
			int newFontSize =
						static_cast<int>(minFontSize + (value * (maxFontSize - minFontSize)));
			text->getTexts().at(text->getTexts().size() - 1)->setFontSize(newFontSize);
			text->getTexts().at(text->getTexts().size() - 1)->setBounds(
				Bounds{.top	   = text->getTexts().at(text->getTexts().size() - 1)->getBounds().top,
					   .bottom = text->getTexts().at(text->getTexts().size() - 1)->getBounds().bottom,
					   .left   = text->getTexts().at(text->getTexts().size() - 1)->getBounds().left,
					   .right  = text->getTexts().at(text->getTexts().size() - 1)->getBounds().right});
		}	
	}
	else if (label == "red")
	{
		Color newToolColor = {.r = value,
						   .g = tool->getActiveTool()->getColor().g,
						   .b = tool->getActiveTool()->getColor().b,
						   .a = tool->getActiveTool()->getColor().a};
		tool->getActiveTool()->setColor(newToolColor);
		updateBrushButtonColor(newToolColor);

		if (buttons.at(selectedIndex)->getLabel() != "Eraser") {
			buttons.at(selectedIndex)->setColor(newToolColor);
		}

		if (text->isTextToolActive())
		{
			text->getTexts().at(text->getTexts().size() - 1)->setColor(Color{.r = value,
													 .g = text->getTexts().at(text->getTexts().size() - 1)->getColor().g,
													 .b = text->getTexts().at(text->getTexts().size() - 1)->getColor().b,
													 .a = text->getTexts().at(text->getTexts().size() - 1)->getColor().a});			
		}
	}
	else if (label == "green")
	{
		Color newToolColor = {.r = tool->getActiveTool()->getColor().r,
						   .g = value,
						   .b = tool->getActiveTool()->getColor().b,
						   .a = tool->getActiveTool()->getColor().a};
		tool->getActiveTool()->setColor(newToolColor);
		updateBrushButtonColor(newToolColor);

		if (buttons.at(selectedIndex)->getLabel() != "Eraser") {
			buttons.at(selectedIndex)->setColor(newToolColor);
		}

		if (text->isTextToolActive())
		{
			text->getTexts().at(text->getTexts().size() - 1)->setColor(Color{.r = text->getTexts().at(text->getTexts().size() - 1)->getColor().r,
												 .g = value,
												 .b = text->getTexts().at(text->getTexts().size() - 1)->getColor().b,
												 .a = text->getTexts().at(text->getTexts().size() - 1)->getColor().a});			
		}
	}
	else if (label == "blue")
	{
		Color newToolColor = {.r = tool->getActiveTool()->getColor().r,
						   .g = tool->getActiveTool()->getColor().g,
						   .b = value,
						   .a = tool->getActiveTool()->getColor().a};
		tool->getActiveTool()->setColor(newToolColor);
		updateBrushButtonColor(newToolColor);

		if (buttons.at(selectedIndex)->getLabel() != "Eraser") {
			buttons.at(selectedIndex)->setColor(newToolColor);
		}
		
		if (text->isTextToolActive())
		{
			text->getTexts().at(text->getTexts().size() - 1)->setColor(Color{.r = text->getTexts().at(text->getTexts().size() - 1)->getColor().r,
													 .g = text->getTexts().at(text->getTexts().size() - 1)->getColor().g,
													 .b = value,
													 .a = text->getTexts().at(text->getTexts().size() - 1)->getColor().a});
			}
		}
	else if (label == "opacity")
	{
		Color newToolColor = {.r = tool->getActiveTool()->getColor().r,
						   .g = tool->getActiveTool()->getColor().g,
						   .b = tool->getActiveTool()->getColor().b,
						   .a = value};
		tool->getActiveTool()->setColor(newToolColor);
		updateBrushButtonColor(newToolColor);

		if (buttons.at(selectedIndex)->getLabel() != "Eraser") {
			buttons.at(selectedIndex)->setColor(newToolColor);
		}
		

		if (text->isTextToolActive())
		{
			text->getTexts().at(text->getTexts().size() - 1)->setColor(Color{.r = text->getTexts().at(text->getTexts().size() - 1)->getColor().r,
													 .g = text->getTexts().at(text->getTexts().size() - 1)->getColor().g,
													 .b = text->getTexts().at(text->getTexts().size() - 1)->getColor().b,
													 .a = value});
		}
	}

	setSliderButtonValues();
}

void MenuBar::onToolButton(const std::shared_ptr<IButton>& button, const std::string& label, double x,
				  double y, int itCount)
{
	if (label == "Text")
	{
		if (text->isTextToolActive())
		{
			text->setTextToolInactive();
			button->setColor(white);
		}
		else
		{
			text->setTextToolActive();
			button->setColor(green);
		}
	}
	else if (label == "Eraser" || label == "Brush")
	{
		tool->selectTool(label);
		selectedIndex = itCount;
	}
}

void MenuBar::onColorButton(const std::shared_ptr<IButton>& button, const std::string& label, double x,
				  double y, int itCount)
{
	if (label == "color")
	{
		tool->getActiveTool()->setColor(button->getColor());
		if (text->isTextToolActive())
		{
			text->getTexts().at(text->getTexts().size() - 1)->setColor(button->getColor());
		}
		else
		{
			updateBrushButtonColor(button->getColor());
		}
	}
	else if (label == "size" || label == "red" || label == "green" || label == "blue" || label == "opacity")
	{
		auto sliderButton = std::dynamic_pointer_cast<SliderButton>(button);
		if (sliderButton)
		{
			sliderLogic(sliderButton, label, x, y);
		}
	}
}

void MenuBar::onHistoryButton(const std::shared_ptr<IButton>& button, const std::string& label, double x,
				  double y, int itCount)
{
	if (label == "Undo Text")
	{
		if (text->isTextToolActive())
		{
			text->undoText();
		}
	}
	else if (label == "Redo Text")
	{
		if (text->isTextToolActive())
		{
			text->redoText();
		}
	}
	else if (label == "Undo Strokes")
	{
		if (tool->getActiveTool())
		{
			tool->undoStroke();
		}
	}
	else if (label == "Redo Strokes")
	{
		if (tool->getActiveTool())
		{
			tool->redoStroke();
		}
	}
	else if (label == "Clear Text")
	{
		if (text->isTextToolActive())
		{
			text->clearAll();
		}
	}
	else if (label == "Clear Strokes")
	{
		if (tool->getActiveTool())
		{
			tool->clearStrokes();
		}
	}
}

void MenuBar::rebuildLayerDropdownButtons()
{
    if (!dropdownOpen || !layerManager) 
	{
		return;
	}

    layerDropdownButtons.clear();
    layerDeleteButtons.clear();

    const auto& layers = layerManager->getAllLayers();
    const float buttonHeight = 25.0F;
	const float top			 = bounds.bottom - 50.0F;

    // Locate dropdown button to position this list
    auto dropdownBtn = std::ranges::find_if(buttons.begin(), buttons.end(), [](const auto& b) {
        return b->getLabel() == "Select Layer";
    });

    if (dropdownBtn == buttons.end()) 
	{
		return;
	}

    float left = (*dropdownBtn)->getBounds().left;
    float right = (*dropdownBtn)->getBounds().right;

    for (size_t i = 0; i < layers.size(); ++i)
    {
        std::string layerName = layers[i]->getName();
        
        // Main selection button (full width minus delete button space)
		Color layerColor = (layers[i] == layerManager->getActiveLayer()) ? gray : white;
		auto layerBtn = std::make_shared<ButtonClass>(
			layerName,
			Bounds {
				.top	= top + ((float) i * buttonHeight),
				.bottom = top + (((float) i + 1) * buttonHeight), 
				.left = left,
				.right = right - buttonHeight,
			},
			layerColor);
		layerDropdownButtons.push_back(layerBtn);

        // Delete button ("X") aligned right
		Color deleteColor = (layers.size() > 1) ? red : gray;
        auto deleteBtn = std::make_shared<ButtonClass>(
            "X",
            Bounds{
                .top = top + ((float)i * buttonHeight),
                .bottom = top + (((float)i + 1) * buttonHeight),
                .left = right - buttonHeight,
                .right = right
            },
            deleteColor);
        layerDeleteButtons.push_back(deleteBtn);
    }
}

const std::vector<std::shared_ptr<IButton>>& MenuBar::getLayerDropdownButtons() const {
	return layerDropdownButtons;
}

const std::vector<std::shared_ptr<IButton>>& MenuBar::getLayerDeleteButtons() const {
	return layerDeleteButtons;
}

void MenuBar::update()
{
    if (dropdownOpen)
    {
        rebuildLayerDropdownButtons();
    }
}

void MenuBar::beginRenameLayer(int layerIndex)
{
    renamingLayer = true;
    layerBeingRenamed = layerIndex;
    renameBuffer = layerManager->getAllLayers()[layerIndex]->getName();
}

bool MenuBar::isRenaming() const 
{ 
	return renamingLayer; 

}
std::string MenuBar::getRenameBuffer() const 
{ 
	return renameBuffer; 
}

int MenuBar::getLayerBeingRenamed() const 
{ 
	return layerBeingRenamed; 
}

void MenuBar::updateBrushButtonColor(Color newColor)
{
    for (auto& button : buttons)
    {
        if (button->getLabel() == "Brush")
        {
            button->setColor(newColor);
            break;
        }
    }
}
