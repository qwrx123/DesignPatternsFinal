#include <GLFW/glfw3.h>
#include <iostream>
#include "WindowClass.h"

WindowClass::WindowClass() 
    : width(0), height(0), title(nullptr), window(nullptr)
{

}

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
    this->width = width;
    this->height = height;
    this->title = title;

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

bool WindowClass::shouldClose() const {
        return glfwWindowShouldClose(window);
}

void WindowClass::defaultEvent()
{
    glfwPollEvents();
}

bool WindowClass::initCallbacks()
{
	glfwSetWindowSizeCallback(window, (GLFWwindowsizefun)(&windowSizeCallback));
	return true;
}

void WindowClass::windowSizeCallback(GLFWwindow *window, int width, int height)
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


    glfwSwapBuffers(window);
    glfwPollEvents();
}
