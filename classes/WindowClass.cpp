#include "WindowClass.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "Bounds.h"
#include "ButtonClass.h"
#include "MenuBar.h"

WindowClass::WindowClass() : width(0), height(0), title(nullptr) {}

WindowClass::~WindowClass()
{
	if (window != nullptr)
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

	// adding some test buttons for pen and eraser toolBar
	/*toolBar.setBounds(Bounds(0, 39, 0, width));
	Bounds buttonBounds = Bounds(0, toolBar.getBounds().bottom, 0, 39);
	toolBar.addButton(std::make_shared<ButtonClass>(ButtonClass(buttonBounds, 1, 1, 1)));
	double edge	 = toolBar.getButtons().at(0)->getBounds().right;
	buttonBounds = Bounds(0, toolBar.getBounds().bottom, edge + 1, edge + 40);
	toolBar.addButton(std::make_shared<ButtonClass>(ButtonClass(buttonBounds, 0, 0, 0)));*/

	if (glfwInit() == GLFW_FALSE)
	{
		return false;
	}

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	if (window == nullptr)
	{
		std::cerr << "Failed to create window\n";
		return false;
	}

	glfwSetWindowUserPointer(window, this);

	glfwMakeContextCurrent(window);

	return true;
}

bool WindowClass::shouldClose() const
{
	return glfwWindowShouldClose(window) != 0;
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
	glfwSetCharCallback(window, characterCallback);
	return true;
}

void WindowClass::windowSizeCallback(GLFWwindow* window, int width, int height)
{
	auto* myWindow = static_cast<WindowClass*>(glfwGetWindowUserPointer(window));

	if (myWindow != nullptr)
	{
		myWindow->handleWindowSize(width, height);
	}
}

void WindowClass::handleWindowSize(int width, int height) {}

void WindowClass::render()
{
	// Preps the widnow for rendering
	// Sets the canvas of the window starting at the top left
	int width  = 0;
	int height = 0;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);

	// Sets up the coordinate system for canvas
	// Origin at the center
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);  // (left, right, bottom, top, near, far);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Brush tool
	static const float defaultThickness = 5.0F;
	static const float defaultNorm		= 2.0F;
	glLineWidth(defaultThickness);
	for (const auto& stroke : strokes)
	{
		glBegin(GL_LINE_STRIP);
		glColor3f(1.0F, 1.0F, 1.0F);  // White
		for (const auto& pt : stroke)
		{
			float normX =
				((static_cast<float>(pt.first) / static_cast<float>(width)) * defaultNorm) - 1.0F;
			float normY =
				1.0F - ((static_cast<float>(pt.second) / static_cast<float>(height)) * defaultNorm);
			glVertex2f(normX, normY);
		}
		glEnd();
	}

	// Sets up coordinate system for UI
	// Origin at top-left
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int right  = width;
	int bottom = height;
	glOrtho(0, right, bottom, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// render ToolBar
	/*toolBar.setBounds(Bounds(0, 39, 0, width));
	glBegin(GL_QUADS);
	glColor3f(.3, .3, .3);
	glVertex2f(toolBar.getBounds().left, toolBar.getBounds().top);
	glVertex2f(toolBar.getBounds().right, toolBar.getBounds().top);
	glVertex2f(toolBar.getBounds().right, toolBar.getBounds().bottom);
	glVertex2f(toolBar.getBounds().left, toolBar.getBounds().bottom);
	glEnd();*/

	// render all buttons within toolbar
	/*for (int i = 0; i < toolBar.getButtons().size(); i++)
	{
		std::dynamic_pointer_cast<ButtonClass>(toolBar.getButtons().at(i))->renderButton();
	}*/

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void WindowClass::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	auto* myWindow = static_cast<WindowClass*>(glfwGetWindowUserPointer(window));

	if (myWindow != nullptr)
	{
		myWindow->handleMouseMove(xpos, ypos);
	}
}

void WindowClass::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	auto* myWindow = static_cast<WindowClass*>(glfwGetWindowUserPointer(window));

	if (myWindow != nullptr)
	{
		myWindow->handleMouseButton(button, action, mods);
	}
}

void WindowClass::handleMouseMove(double xpos, double ypos)
{
	if (currentTool == ToolType::Brush && isDrawing)
	{
		currentStroke->emplace_back(xpos, ypos);
	}

	if (currentTool == ToolType::Eraser && isErasing)
	{
		eraseAtCursor(xpos, ypos);
	}
}

void WindowClass::handleMouseButton(int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		double xpos = 0;
		double ypos = 0;
		glfwGetCursorPos(window, &xpos, &ypos);

		// checks through every button to see if it was pressed
		/*for (int i = 0; i < toolBar.getButtons().size(); i++)
		{
			Bounds bounds = toolBar.getButtons().at(i)->getBounds();
			toolBar.getButtons().at(i)->setPressed(xpos >= bounds.left && xpos <= bounds.right &&
												   ypos >= bounds.top && ypos <= bounds.bottom);
		}*/

		if (action == GLFW_PRESS)
		{
			// hard-coded button actions for testing purposes
			/*if (toolBar.getButtons().at(0)->isPressed() && currentTool != ToolType::Brush)
			{
				currentTool = ToolType::Brush;

				std::cout << "Switched to Brush" << std::endl;
				return;
			}
			else if (toolBar.getButtons().at(1)->isPressed() && currentTool != ToolType::Eraser)
			{
				currentTool = ToolType::Eraser;

				std::cout << "Switched to Eraser" << std::endl;
				return;
			}*/

			if (currentTool == ToolType::Brush)
			{
				isDrawing = true;
				strokes.emplace_back();
				currentStroke = &strokes.back();
			}
			else if (currentTool == ToolType::Eraser)
			{
				isErasing = true;
			}
		}
		else if (action == GLFW_RELEASE)
		{
			isDrawing	  = false;
			isErasing	  = false;
			currentStroke = nullptr;

			for (const auto& button : toolBar.getButtons())
			{
				button->setPressed(false);
			}
		}
	}
}

void WindowClass::characterCallback(GLFWwindow* window, unsigned int codepoint)
{
	auto* myWindow = static_cast<WindowClass*>(glfwGetWindowUserPointer(window));

	if (myWindow != nullptr)
	{
		myWindow->handleCharacterInput(codepoint);
	}
}

// TODO: Implement the character input handling function
void WindowClass::handleCharacterInput(unsigned int codepoint) {}

// Erases what is within the erasers radius and breaks up any required stroke vectors
void WindowClass::eraseAtCursor(double xpos, double ypos)
{
	std::vector<std::vector<std::pair<double, double>>> newStrokes;

	for (const auto& stroke : strokes)
	{
		std::vector<std::pair<double, double>> currentSegment;

		for (const auto& pt : stroke)
		{
			double dx		= pt.first - xpos;
			double dy		= pt.second - ypos;
			bool   isErased = std::sqrt((dx * dx) + (dy * dy)) <= eraser_radius;

			if (isErased)
			{
				if (!currentSegment.empty())
				{
					newStrokes.push_back(currentSegment);
					currentSegment.clear();
				}
			}
			else
			{
				currentSegment.push_back(pt);
			}
		}
		newStrokes.push_back(currentSegment);
	}
	strokes = std::move(newStrokes);
}
