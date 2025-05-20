#include <iostream>
#include <memory>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "CanvasRenderer.h"
#include "StrokeManager.h"
#include "InputManager.h"
#include "ToolManager.h"

InputManager* g_inputManager = nullptr;

// --- Callback Setup ---
void mouseMoveCallback(GLFWwindow*, double x, double y) {
    if (g_inputManager) g_inputManager->handleMouseMove(x, y);
}

void mouseButtonCallback(GLFWwindow*, int button, int action, int /*mods*/) {
    if (!g_inputManager) return;

    MouseButton mb;
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:   mb = MouseButton::Left;   break;
        case GLFW_MOUSE_BUTTON_RIGHT:  mb = MouseButton::Right;  break;
        case GLFW_MOUSE_BUTTON_MIDDLE: mb = MouseButton::Middle; break;
        default: return;
    }

    KeyAction ka;
    switch (action) {
        case GLFW_PRESS:   ka = KeyAction::Press;   break;
        case GLFW_RELEASE: ka = KeyAction::Release; break;
        case GLFW_REPEAT:  ka = KeyAction::Repeat;  break;
        default: return;
    }

    double xPos, yPos;
    glfwGetCursorPos(glfwGetCurrentContext(), &xPos, &yPos);
    g_inputManager->handleMouseButton(mb, ka, xPos, yPos);
}

void keyCallback(GLFWwindow*, int key, int /*scancode*/, int action, int /*mods*/) {
    if (!g_inputManager) return;

    KeyAction ka;
    switch (action) {
        case GLFW_PRESS:   ka = KeyAction::Press;   break;
        case GLFW_RELEASE: ka = KeyAction::Release; break;
        case GLFW_REPEAT:  ka = KeyAction::Repeat;  break;
        default: return;
    }

    g_inputManager->handleKey(key, ka);
}

// --- Main Entry ---
int main() {
    if (!glfwInit()) {
        std::cerr << "GLFW failed to initialize\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Drawing App", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // --- Core Systems ---
    auto renderer       = std::make_unique<CanvasRenderer>(window);
    auto strokeManager  = std::make_shared<StrokeManager>();
    auto toolManager    = std::make_shared<ToolManager>(strokeManager);  // assuming ToolManager takes StrokeManager
    auto inputManager   = std::make_shared<InputManager>();
    g_inputManager      = inputManager.get();

    inputManager->registerReceiver(toolManager);

    // --- Set GLFW Callbacks ---
    glfwSetCursorPosCallback(window, mouseMoveCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetKeyCallback(window, keyCallback);

    // --- Main Loop ---
    while (!glfwWindowShouldClose(window)) {
        inputManager->beginFrame();
        glfwPollEvents();

        renderer->beginFrame();
        for (const auto& stroke : strokeManager->getStrokes()) {
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