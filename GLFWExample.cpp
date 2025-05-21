#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

#include "CanvasRenderer.h"
#include "InputManager.h"
#include "StrokeManager.h"
#include "ToolManager.h"
#include "BrushTool.h"

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

	inputManager->bindToWindow(window);
	inputManager->registerReceiver(toolManager);

	toolManager->registerTool(
		"brush", std::make_shared<BrushTool>(strokeManager, Color{0.0f, 0.0f, 0.0f, 1.0f},	// Black
											 2.0f  // Thickness
											 ));

	inputManager->setResizeCallback([&](int w, int h) { renderer->resize(w, h); });

	// --- Main Loop ---
	while (!glfwWindowShouldClose(window))
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

		renderer->endFrame();

		inputManager->endFrame();
	}

	// --- Shutdown ---
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}