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

	inputManager->bindToWindow(window);
	inputManager->registerReceiver(toolManager);
	inputManager->registerReceiver(menuBar);
	inputManager->registerReceiver(textManager);
	inputManager->setResizeCallback([&](int w, int h) { CanvasRenderer::resize(w, h); });

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
	menuBar->setToolPointer(toolManager);
	menuBar->setTextPointer(textManager);
	menuBar->setDefaultButtons();

	while (glfwWindowShouldClose(window) == 0)
	{
		inputManager->beginFrame();
		glfwPollEvents();

		// begin rendering
		renderer->beginFrame();

		for (const auto& stroke : strokeManager->getStrokes())
		{
			renderer->drawStroke(*stroke);
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
			if (button->getLabel() == "size" || button->getLabel() == "red" ||
				button->getLabel() == "green" || button->getLabel() == "blue" ||
				button->getLabel() == "opacity")
			{
				renderer->drawSliderButton(*button, button->getValue());
			}
			else
			{
				renderer->drawButton(*button);
			}
		}
		renderer->endFrame();
		inputManager->endFrame();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}