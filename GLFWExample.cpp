#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

#include "CanvasRenderer.h"
#include "InputManager.h"
#include "StrokeManager.h"
#include "ToolManager.h"
#include "BrushTool.h"
#include "EraserTool.h"
#include "MenuBar.h"
#include "ButtonClass.h"

// --- Main Entry ---
int main()
{
	if (!glfwInit())
	{
		std::cerr << "GLFW failed to initialize\n";
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Drawing App", nullptr, nullptr);
	if (!window)
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
	inputManager->setResizeCallback([&](int w, int h) { renderer->resize(w, h); });

	toolManager->registerTool(
		"brush", std::make_shared<BrushTool>(strokeManager, Color{0.0f, 0.0f, 0.0f, 1.0f},	// Black
											 2.0f  // Thickness
											 ));
	toolManager->registerTool("eraser", std::make_shared<EraserTool>(strokeManager, 10.0f));

	menuBar->setBounds(Bounds(0, 100, 0, INT_MAX));
	menuBar->addButton(std::make_shared<ButtonClass>(
		"brush",
		Bounds(menuBar->getBounds().top, 50,
			   menuBar->getButtons().at(menuBar->getButtons().size() - 1)->getBounds().right + 1,
			   menuBar->getButtons().at(menuBar->getButtons().size() - 1)->getBounds().right + 50),
		bColor(0, .5, .5, 1)));
	menuBar->addButton(std::make_shared<ButtonClass>(
		"eraser",  // This is the unique ID used for tool switching
		Bounds(50, menuBar->getBounds().bottom, 0, 50), bColor(1, 0.5, 0, 1)  // Orange button
		));

	// --- Main Loop ---
	while (!glfwWindowShouldClose(window))
	{
		inputManager->beginFrame();
		glfwPollEvents();

		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			for (const auto& button : menuBar->getButtons())
			{
				if (button->getBounds().contains(mouseX, mouseY))
				{
					std::string buttonLabel = button->getLabel();

					if (buttonLabel == "eraser")
					{
						toolManager->selectTool("eraser");
					}
					else if (buttonLabel == "brush")
					{
						toolManager->selectTool("brush");
					}
				}
			}
		}

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