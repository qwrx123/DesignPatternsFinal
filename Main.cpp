#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <optional>

#include "CanvasRenderer.h"
#include "InputManager.h"
#include "ToolManager.h"
#include "BrushTool.h"
#include "EraserTool.h"
#include "MenuBar.h"
#include "ButtonClass.h"
#include "TextManager.h"
#include "LayerManager.h"

const int		  defaultWindowWidth  = 800;
const int		  defaultWindowHeight = 600;
const char* const defaultWindowTitle  = "Drawing App";

const float defaultEraserSize = 10;

const float defaultThickness	 = 2.0F;
const int	defaultMenuBarHeight = 100;
const int	defaultFontSize		 = 48;

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

	auto renderer	  = std::make_unique<CanvasRenderer>(window);
	auto layerManager = std::make_shared<LayerManager>();
	auto toolManager  = std::make_shared<ToolManager>();
	auto inputManager = std::make_shared<InputManager>();
	auto menuBar	  = std::make_shared<MenuBar>();
	auto textManager  = std::make_shared<TextManager>();

	inputManager->bindToWindow(window);
	inputManager->registerReceiver(toolManager);
	inputManager->registerReceiver(menuBar);
	inputManager->registerReceiver(textManager);
	inputManager->setResizeCallback([&](int w, int h) { CanvasRenderer::resize(w, h); });

	toolManager->setBounds(Bounds{.top	  = defaultMenuBarHeight,
								  .bottom = defaultWindowHeight,
								  .left	  = 0,
								  .right  = defaultWindowWidth});
	toolManager->registerTool(
		"brush",
		std::make_shared<BrushTool>(layerManager, Color{.r = 0.0F, .g = 0.0F, .b = 0.0F, .a = 1.0F},
									defaultThickness));
	toolManager->registerTool("eraser",
							  std::make_shared<EraserTool>(layerManager, defaultEraserSize));

	textManager->registerTextTool(std::make_shared<Text>(
		"",
		Bounds(defaultFontSize + defaultMenuBarHeight, defaultWindowHeight, 0, defaultWindowWidth),
		"Delius", defaultFontSize, Color{.r = 0.0F, .g = 0.0F, .b = 0.0F, .a = 1.0F}, true));

	menuBar->setBounds(
		Bounds{.top = 0, .bottom = defaultMenuBarHeight, .left = 0, .right = defaultWindowWidth});
	menuBar->setToolPointer(toolManager);
	menuBar->setTextPointer(textManager);
	menuBar->setLayerPointer(layerManager);
	menuBar->setDefaultButtons();

	while (glfwWindowShouldClose(window) == 0)
	{
		inputManager->beginFrame();
		glfwPollEvents();

		// begin rendering
		renderer->beginFrame();

		for (const auto& layer : layerManager->getAllLayers())
		{
			for (const auto& stroke : layer->getStrokes())
			{
				renderer->drawStroke(*stroke);
			}
		}

		for (const auto& text : textManager->getTexts())
		{
			CanvasRenderer::renderText(*text);
		}

		auto current_tool = toolManager->getActiveTool();
		if (toolManager->getActiveToolName() == "brush")
		{
			auto brush		 = std::dynamic_pointer_cast<BrushTool>(current_tool);
			auto live_stroke = brush->getCurrentStroke();
			if (live_stroke && live_stroke->getPoints().size() >= 2)
			{
				renderer->drawStroke(*live_stroke);
			}
		}

		renderer->drawMenu(*menuBar);
		for (const auto& button : menuBar->getButtons())
		{
			if (button->getLabel() == "size" || button->getLabel() == "red" ||
				button->getLabel() == "green" || button->getLabel() == "blue" ||
				button->getLabel() == "opacity")
			{
				CanvasRenderer::drawSliderButton(*button, button->getValue());
			}
			else
			{
				renderer->drawButton(*button);
			}
		}

		for (const auto& dropdown : menuBar->layerDropdownButtons)
		{
			renderer->drawButton(*dropdown);
		}

		renderer->endFrame();
		inputManager->endFrame();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}