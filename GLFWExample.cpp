#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

#include "CanvasRenderer.h"
#include "InputManager.h"
#include "StrokeManager.h"
#include "ToolManager.h"
#include "BrushTool.h"
#include "MenuBar.h"
#include "ButtonClass.h"

const int		  defaultWindowWidth  = 800;
const int		  defaultWindowHeight = 600;
const char* const defaultWindowTitle  = "Drawing App";

const float defaultThickness	 = 2.0F;
const int	defaultMenuBarHeight = 39;

const float grayColor = 0.5F;

// --- Main Entry ---
int main()
{
	if (glfwInit() == GLFW_FALSE)
	{
		std::cerr << "GLFW failed to initialize\n";
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	GLFWwindow* window = glfwCreateWindow(defaultWindowWidth, defaultWindowHeight,
										  defaultWindowTitle, nullptr, nullptr);
	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW\n";
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	// --- Core Systems ---
	auto renderer	   = std::make_unique<CanvasRenderer>(window);
	auto strokeManager = std::make_shared<StrokeManager>();
	auto toolManager   = std::make_shared<ToolManager>();
	auto inputManager  = std::make_shared<InputManager>();
	auto menuBar	   = std::make_shared<MenuBar>();

	inputManager->bindToWindow(window);
	inputManager->registerReceiver(toolManager);

	toolManager->registerTool(
		"brush", std::make_shared<BrushTool>(
					 strokeManager, Color{.r = 0.0F, .g = 0.0F, .b = 0.0F, .a = 1.0F},	// Black
					 defaultThickness													// Thickness
					 ));

	inputManager->setResizeCallback([&](int w, int h) { renderer->resize(w, h); });

	menuBar->setBounds(Bounds(0, defaultMenuBarHeight, 0, static_cast<float>(INT_MAX)));
	menuBar->addButton(std::make_shared<ButtonClass>(
		"button",
		Bounds(0, menuBar->getBounds().bottom,
			   menuBar->getButtons().at(menuBar->getButtons().size() - 1)->getBounds().right + 1,
			   menuBar->getButtons().at(menuBar->getButtons().size() - 1)->getBounds().right + 1 +
				   defaultMenuBarHeight),
		bColor(0, grayColor, grayColor, 1)));

	// --- Main Loop ---
	while (glfwWindowShouldClose(window) == 0)
	{
		inputManager->beginFrame();
		glfwPollEvents();

		renderer->beginFrame();
		for (const auto& stroke : strokeManager->getStrokes())
		{
			renderer->drawStroke(*stroke);
		}

		auto current_tool = toolManager->getActiveTool();
		if (current_tool)
		{
			auto live_stroke = current_tool->getCurrentStroke();
			if (live_stroke)
			{
				renderer->drawStroke(*live_stroke);
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

	// --- Shutdown ---
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}