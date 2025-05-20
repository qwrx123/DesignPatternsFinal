#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

#include "CanvasRenderer.h"
#include "InputManager.h"
#include "StrokeManager.h"
#include "ToolManager.h"

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
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Drawing App", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD\n";
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
		renderer->endFrame();

		inputManager->endFrame();
	}

	// --- Shutdown ---
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}