#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <optional>

#include "CanvasRenderer.h"
#include "InputManager.h"
#include "StrokeManager.h"
#include "ToolManager.h"
#include "BrushTool.h"
#include "EraserTool.h"
#include "MenuBar.h"
#include "ButtonClass.h"
#include "TextManager.h"
#include "SubMenu.h"
#include "SliderButton.h"

const int		  defaultWindowWidth  = 800;
const int		  defaultWindowHeight = 600;
const char* const defaultWindowTitle  = "Drawing App";

const float defaultEraserSize = 10;

const float defaultThickness		= 2.0F;
const int	defaultMenuBarHeight	= 100;
const int	defaultToolButtonHeight = 60;
const float buttonWidth				= 40.0F;
const int	defaultFontSize			= 48;

const float grayColor	  = 0.5F;
const float darkGrayColor = 0.3F;

const int buffer = 20;

int main()
{
	if (glfwInit() == GLFW_FALSE)
	{
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	GLFWwindow* window = glfwCreateWindow(defaultWindowWidth, defaultWindowHeight,
										  defaultWindowTitle, nullptr, nullptr);
	if (window == nullptr)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	auto					   renderer		 = std::make_unique<CanvasRenderer>(window);
	auto					   strokeManager = std::make_shared<StrokeManager>();
	auto					   toolManager	 = std::make_shared<ToolManager>();
	auto					   inputManager	 = std::make_shared<InputManager>();
	auto					   menuBar		 = std::make_shared<MenuBar>();
	std::optional<std::string> pendingToolSwitch;
	auto					   textManager = std::make_shared<TextManager>();
	auto					   textMenu	   = std::make_shared<SubMenu>();

	inputManager->bindToWindow(window);
	inputManager->registerReceiver(toolManager);
	inputManager->setResizeCallback([&](int w, int h) { CanvasRenderer::resize(w, h); });
	inputManager->registerReceiver(textManager);

	toolManager->registerTool(
		"brush",
		std::make_shared<BrushTool>(
			strokeManager, Color{.r = 0.0F, .g = 0.0F, .b = 0.0F, .a = 1.0F}, defaultThickness));
	textManager->registerTextTool(std::make_shared<Text>(
		"",
		Bounds(defaultFontSize + defaultMenuBarHeight, defaultWindowHeight, 0, defaultWindowWidth),
		"Delius", defaultFontSize, Color{.r = 0.0F, .g = 0.0F, .b = 0.0F, .a = 1.0F}, true));
	toolManager->registerTool("eraser",
							  std::make_shared<EraserTool>(strokeManager, defaultEraserSize));

	menuBar->setBounds(Bounds(0, defaultMenuBarHeight, 0, static_cast<float>(INT_MAX)));

	float currentRight = 0.0F;

	menuBar->addButton(std::make_shared<ButtonClass>(
		"brush", Bounds(0, defaultMenuBarHeight, currentRight, currentRight + buttonWidth),
		bColor(0, grayColor, grayColor, 1)));
	currentRight += buttonWidth + 1;

	menuBar->addButton(std::make_shared<ButtonClass>(
		"eraser", Bounds(0, defaultMenuBarHeight, currentRight, currentRight + buttonWidth),
		bColor(1, grayColor, 0.0F, 1)));
	currentRight += buttonWidth + 1;

	menuBar->addButton(std::make_shared<ButtonClass>(
		"text", Bounds(0, defaultToolButtonHeight, currentRight, currentRight + buttonWidth),
		bColor(darkGrayColor, grayColor, 0, 1)));
	static bool wasPressedLastFrame = false;

	menuBar->addButton(
		std::make_shared<ButtonClass>("open text menu",
									  Bounds(defaultToolButtonHeight, defaultMenuBarHeight,
											 currentRight, currentRight + buttonWidth),
									  bColor(grayColor, grayColor, 0, 0.5F)));
	textMenu->setBounds(
		Bounds(defaultMenuBarHeight, 2 * defaultMenuBarHeight, 0, static_cast<float>(INT_MAX)));
	textMenu->setLabel("Text Options");
	textMenu->addButton(std::make_shared<SliderButton>(
		"text size", Bounds(defaultMenuBarHeight, 2 * defaultMenuBarHeight, 0, buttonWidth),
		bColor(grayColor, grayColor, 0, 1)));
	textMenu->addButton(
		std::make_shared<SliderButton>("text red",
									   Bounds(defaultMenuBarHeight, 2 * defaultMenuBarHeight,
											  buttonWidth + buffer, 2 * buttonWidth + buffer),
									   bColor(grayColor, grayColor, 0, 1)));
	textMenu->addButton(
		std::make_shared<SliderButton>("text green",
									   Bounds(defaultMenuBarHeight, 2 * defaultMenuBarHeight,
											  2 * buttonWidth + buffer, 3 * buttonWidth + buffer),
									   bColor(grayColor, grayColor, 0, 1)));
	textMenu->addButton(
		std::make_shared<SliderButton>("text blue",
									   Bounds(defaultMenuBarHeight, 2 * defaultMenuBarHeight,
											  3 * buttonWidth + buffer, 4 * buttonWidth + buffer),
									   bColor(grayColor, grayColor, 0, 1)));
	textMenu->addButton(
		std::make_shared<SliderButton>("text opacity",
									   Bounds(defaultMenuBarHeight, 2 * defaultMenuBarHeight,
											  4 * buttonWidth + buffer, 5 * buttonWidth + buffer),
									   bColor(grayColor, grayColor, 0, 1)));

	while (glfwWindowShouldClose(window) == 0)
	{
		inputManager->beginFrame();
		glfwPollEvents();

		double mouseX = 0;
		double mouseY = 0;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		bool isPressedNow = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

		if (isPressedNow && !wasPressedLastFrame)
		{
			for (const auto& button : menuBar->getButtons())
			{
				if (button->getBounds().contains(mouseX, mouseY))
				{
					pendingToolSwitch	= button->getLabel();
					wasPressedLastFrame = isPressedNow;
					goto render_frame;
				}
			}
			for (const auto& button : textMenu->getButtons())
			{
				if (button->getBounds().contains(mouseX, mouseY) && textMenu->isOpen())
				{
					pendingToolSwitch	= button->getLabel();
					wasPressedLastFrame = isPressedNow;
					goto render_frame;
				}
			}
		}

		wasPressedLastFrame = isPressedNow;

	render_frame:
		renderer->beginFrame();

		for (const auto& stroke : strokeManager->getStrokes())
		{
			renderer->drawStroke(*stroke);
		}

		if (pendingToolSwitch == "text")
		{
			if (textManager->isTextToolActive())
			{
				textManager->setTextToolInactive();
				pendingToolSwitch.reset();
			}
			else
			{
				textManager->setTextToolActive();
				pendingToolSwitch.reset();
			}
		}

		if (pendingToolSwitch == "open text menu")
		{
			if (textMenu->isOpen())
			{
				textMenu->close();
			}
			else
			{
				textMenu->open();
			}
			pendingToolSwitch.reset();
		}

		if (pendingToolSwitch == "text size")
		{
			auto sliderButton =
				std::dynamic_pointer_cast<SliderButton>(textMenu->getSelectedItem());
			if (sliderButton)
			{
				sliderButton->setMinValue(0.0F);
				sliderButton->setMaxValue(1.0F);
				float minValue	  = sliderButton->getMinValue();
				float maxValue	  = sliderButton->getMaxValue();
				auto  bounds	  = sliderButton->getBounds();
				float sliderStart = bounds.left;
				float sliderEnd	  = bounds.right;
				float t = (static_cast<float>(mouseX) - sliderStart) / (sliderEnd - sliderStart);
				t		= std::clamp(t, 0.0f, 1.0f);
				float value = minValue + t * (maxValue - minValue);
				sliderButton->setValue(value);

				// Map slider value to a reasonable font size range, e.g., 12 to 96
				int minFontSize = 12;
				int maxFontSize = 96;
				int newFontSize =
					static_cast<int>(minFontSize + value * (maxFontSize - minFontSize));

				for (const auto& text : textManager->getTexts())
				{
					text->setFontSize(newFontSize);
					auto  oldBounds = text->getBounds();
					float newBottom = oldBounds.top + newFontSize + 1.0F;
					text->setBounds(
						Bounds(oldBounds.top, newBottom, oldBounds.left, oldBounds.right));
				}
			}
			pendingToolSwitch.reset();
		}

		if (pendingToolSwitch == "text red")
		{
			auto sliderButton =
				std::dynamic_pointer_cast<SliderButton>(textMenu->getSelectedItem());
			if (sliderButton)
			{
				sliderButton->setMinValue(0.0F);
				sliderButton->setMaxValue(1.0F);
				float minValue	  = sliderButton->getMinValue();
				float maxValue	  = sliderButton->getMaxValue();
				auto  bounds	  = sliderButton->getBounds();
				float sliderStart = bounds.left;
				float sliderEnd	  = bounds.right;
				float t = (static_cast<float>(mouseX) - sliderStart) / (sliderEnd - sliderStart);
				t		= std::clamp(t, 0.0f, 1.0f);
				float value = minValue + t * (maxValue - minValue);
				sliderButton->setValue(value);

				for (const auto& text : textManager->getTexts())
				{
					text->setColor(Color{.r = value,
										 .g = text->getColor().g,
										 .b = text->getColor().b,
										 .a = text->getColor().a});
				}
			}
			pendingToolSwitch.reset();
		}

		if (pendingToolSwitch == "text blue")
		{
			auto sliderButton =
				std::dynamic_pointer_cast<SliderButton>(textMenu->getSelectedItem());
			if (sliderButton)
			{
				sliderButton->setMinValue(0.0F);
				sliderButton->setMaxValue(1.0F);
				float minValue	  = sliderButton->getMinValue();
				float maxValue	  = sliderButton->getMaxValue();
				auto  bounds	  = sliderButton->getBounds();
				float sliderStart = bounds.left;
				float sliderEnd	  = bounds.right;
				float t = (static_cast<float>(mouseX) - sliderStart) / (sliderEnd - sliderStart);
				t		= std::clamp(t, 0.0f, 1.0f);
				float value = minValue + t * (maxValue - minValue);
				sliderButton->setValue(value);

				for (const auto& text : textManager->getTexts())
				{
					text->setColor(Color{.r = text->getColor().r,
										 .g = text->getColor().g,
										 .b = value,
										 .a = text->getColor().a});
				}
			}
			pendingToolSwitch.reset();
		}

		if (pendingToolSwitch == "text green")
		{
			auto sliderButton =
				std::dynamic_pointer_cast<SliderButton>(textMenu->getSelectedItem());
			if (sliderButton)
			{
				sliderButton->setMinValue(0.0F);
				sliderButton->setMaxValue(1.0F);
				float minValue	  = sliderButton->getMinValue();
				float maxValue	  = sliderButton->getMaxValue();
				auto  bounds	  = sliderButton->getBounds();
				float sliderStart = bounds.left;
				float sliderEnd	  = bounds.right;
				float t = (static_cast<float>(mouseX) - sliderStart) / (sliderEnd - sliderStart);
				t		= std::clamp(t, 0.0f, 1.0f);
				float value = minValue + t * (maxValue - minValue);
				sliderButton->setValue(value);

				for (const auto& text : textManager->getTexts())
				{
					text->setColor(Color{.r = text->getColor().r,
										 .g = value,
										 .b = text->getColor().b,
										 .a = text->getColor().a});
				}
			}
			pendingToolSwitch.reset();
		}

		if (pendingToolSwitch == "text opacity")
		{
			auto sliderButton =
				std::dynamic_pointer_cast<SliderButton>(textMenu->getSelectedItem());
			if (sliderButton)
			{
				sliderButton->setMinValue(0.0F);
				sliderButton->setMaxValue(1.0F);
				float minValue	  = sliderButton->getMinValue();
				float maxValue	  = sliderButton->getMaxValue();
				auto  bounds	  = sliderButton->getBounds();
				float sliderStart = bounds.left;
				float sliderEnd	  = bounds.right;
				float t = (static_cast<float>(mouseX) - sliderStart) / (sliderEnd - sliderStart);
				t		= std::clamp(t, 0.0f, 1.0f);
				float value = minValue + t * (maxValue - minValue);
				sliderButton->setValue(value);

				for (const auto& text : textManager->getTexts())
				{
					text->setColor(Color{.r = text->getColor().r,
										 .g = text->getColor().g,
										 .b = text->getColor().b,
										 .a = value});
				}
			}
			pendingToolSwitch.reset();
		}

		if (pendingToolSwitch)
		{
			toolManager->selectTool(*pendingToolSwitch);
			pendingToolSwitch.reset();
		}

		for (const auto& text : textManager->getTexts())
		{
			CanvasRenderer::renderText(*text);
		}

		auto current_tool = toolManager->getActiveTool();

		if (isPressedNow && !wasPressedLastFrame)
		{
			current_tool->beginStroke({.x = mouseX, .y = mouseY});
		}
		else if (isPressedNow && wasPressedLastFrame)
		{
			current_tool->addPoint({.x = mouseX, .y = mouseY});
		}
		else if (!isPressedNow && wasPressedLastFrame)
		{
			current_tool->endStroke({.x = mouseX, .y = mouseY});
		}

		if (current_tool)
		{
			auto brush = std::dynamic_pointer_cast<BrushTool>(current_tool);
			if (brush)
			{
				auto live_stroke = brush->getCurrentStroke();
				if (live_stroke && live_stroke->getPoints().size() >= 2)
				{
					renderer->drawStroke(*live_stroke);
				}
			}
		}

		renderer->drawMenu(*menuBar);
		for (const auto& button : menuBar->getButtons())
		{
			renderer->drawButton(*button);
		}
		if (textMenu->isOpen())
		{
			renderer->drawMenu(*textMenu);
			for (const auto& button : textMenu->getButtons())
			{
				renderer->drawSliderButton(*button, button->getValue());
			}
		}

		renderer->endFrame();
		inputManager->endFrame();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}