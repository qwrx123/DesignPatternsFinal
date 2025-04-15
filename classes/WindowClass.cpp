#include "WindowClass.h"
#include <GLFW/glfw3.h>
#include <iostream>

WindowClass::WindowClass() : width(0), height(0), title(nullptr), window(nullptr) {}

WindowClass::~WindowClass()
{
	if (window)
	{
		glfwDestroyWindow(window);
	}
	glfwTerminate();
}

bool WindowClass::CreateWindow(int width, int height, const char* title)
{
	this->width	 = width;
	this->height = height;
	this->title	 = title;

	if (!glfwInit())
	{
		return false;
	}

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	if (!window)
	{
		std::cerr << "Failed to create window" << std::endl;
		return false;
	}

	glfwSetWindowUserPointer(window, this);

	glfwMakeContextCurrent(window);

	return true;
}

bool WindowClass::shouldClose() const
{
	return glfwWindowShouldClose(window);
}

void WindowClass::defaultEvent()
{
	glfwPollEvents();
}

bool WindowClass::initCallbacks()
{
	glfwSetWindowSizeCallback(window, (GLFWwindowsizefun) (&windowSizeCallback));
	glfwSetCursorPosCallback(window, &cursorPositionCallback);
	glfwSetMouseButtonCallback(window, &mouseButtonCallback);
	return true;
}

void WindowClass::windowSizeCallback(GLFWwindow* window, int width, int height)
{
	WindowClass* myWindow = static_cast<WindowClass*>(glfwGetWindowUserPointer(window));

	if (myWindow)
	{
		myWindow->handleWindowSize(width, height);
	}

	return;
}

void WindowClass::handleWindowSize(int width, int height)
{
	return;
}

void WindowClass::render()
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glClear(GL_COLOR_BUFFER_BIT);

	// Draw stroke
	glLineWidth(5.0f);	// Medium thickness
	for (const auto& stroke : strokes)
	{
		glBegin(GL_LINE_STRIP);
		for (const auto& pt : stroke)
		{
			float normX = (pt.first / width) * 2.0f - 1.0f;
			float normY = 1.0f - (pt.second / height) * 2.0f;
			glVertex2f(normX, normY);
		}
		glEnd();
	}

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void WindowClass::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	WindowClass* myWindow = static_cast<WindowClass*>(glfwGetWindowUserPointer(window));

	if (myWindow)
	{
		myWindow->handleMouseMove(xpos, ypos);
	}
}

void WindowClass::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	WindowClass* myWindow = static_cast<WindowClass*>(glfwGetWindowUserPointer(window));

	if (myWindow)
	{
		myWindow->handleMouseButton(button, action, mods);
	}
}

void WindowClass::handleMouseMove(double xpos, double ypos)
{
	if (isDrawing && currentStroke)
	{
		currentStroke->emplace_back(xpos, ypos);
	}
}

void WindowClass::handleMouseButton(int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS)
		{
			isDrawing = true;
			strokes.emplace_back();
			currentStroke = &strokes.back();
		}
		else if (action == GLFW_RELEASE)
		{
			isDrawing	  = false;
			currentStroke = nullptr;
		}
	}
}
