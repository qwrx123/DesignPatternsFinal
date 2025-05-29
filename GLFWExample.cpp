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

const int		  defaultWindowWidth  = 800;
const int		  defaultWindowHeight = 600;
const char* const defaultWindowTitle  = "Drawing App";

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
	inputManager->setResizeCallback([&](int w, int h) { renderer->resize(w, h); });

	toolManager->registerTool(
		"brush", std::make_shared<BrushTool>(strokeManager, Color{0.0F, 0.0F, 0.0F, 1.0F},
											 defaultThickness));
	textManager->registerTextTool(std::make_shared<Text>(
		"",
		Bounds(defaultFontSize + defaultMenuBarHeight, defaultWindowHeight, 0, defaultWindowWidth),
		"Delius", defaultFontSize, Color{.r = 0.0F, .g = 0.0F, .b = 0.0F, .a = 1.0F}, true));
	// textManager->setTextToolActive();
	toolManager->registerTool("eraser", std::make_shared<EraserTool>(strokeManager, 10.0F));

	menuBar->setBounds(Bounds(0, defaultMenuBarHeight, 0, static_cast<float>(INT_MAX)));
	menuBar->setToolPointer(toolManager);
	menuBar->setDefaultButtons();

	float currentRight = 0.0F;

	menuBar->addButton(std::make_shared<ButtonClass>(
		"brush", Bounds(0, defaultMenuBarHeight, currentRight, currentRight + buttonWidth),
		bColor(0, grayColor, grayColor, 1)));
	currentRight += buttonWidth + 1;

	menuBar->addButton(std::make_shared<ButtonClass>(
		"eraser", Bounds(0, defaultMenuBarHeight, currentRight, currentRight + buttonWidth),
		bColor(1, 0.5F, 0.0F, 1)));
	currentRight += buttonWidth + 1;

	menuBar->addButton(std::make_shared<ButtonClass>(
		"text", Bounds(0, defaultMenuBarHeight, currentRight, currentRight + buttonWidth),
		bColor(0.3F, 0.5F, 0, 1)));
	static bool wasPressedLastFrame = false;

	while (!glfwWindowShouldClose(window))
	{
		inputManager->beginFrame();
		glfwPollEvents();

		double mouseX, mouseY;
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

		if (pendingToolSwitch)
		{
			toolManager->selectTool(*pendingToolSwitch);
			pendingToolSwitch.reset();
		}

		for (const auto& text : textManager->getTexts())
		{
			renderer->renderText(*text);
		}

		auto current_tool = toolManager->getActiveTool();

		if (isPressedNow && !wasPressedLastFrame)
		{
			current_tool->beginStroke({mouseX, mouseY});
		}
		else if (isPressedNow && wasPressedLastFrame)
		{
			current_tool->addPoint({mouseX, mouseY});
		}
		else if (!isPressedNow && wasPressedLastFrame)
		{
			current_tool->endStroke({mouseX, mouseY});
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

		renderer->endFrame();
		inputManager->endFrame();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}