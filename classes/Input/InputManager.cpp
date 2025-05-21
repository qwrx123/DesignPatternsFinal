#include "InputManager.h"
#include <algorithm>

InputManager::InputManager() {}

void InputManager::registerReceiver(std::shared_ptr<IInputReceiver> receiver) {
    receivers.push_back(receiver);
}

void InputManager::unregisterReceiver(std::shared_ptr<IInputReceiver> receiver) {
    receivers.erase(
        std::remove(receivers.begin(), receivers.end(), receiver),
        receivers.end()
    );
}

void InputManager::beginFrame() {
    // No-op for now, useful for tracking state later
}

void InputManager::endFrame() {
    // No-op for now
}

void InputManager::handleMouseMove(double x, double y) {
    for (auto& receiver : receivers) {
        receiver->onMouseMove(x, y);
    }
}

void InputManager::handleMouseButton(MouseButton button, KeyAction action, double x, double y) {
    for (auto& receiver : receivers) {
        receiver->onMouseButton(button, action, x, y);
    }
}

void InputManager::handleKey(int key, KeyAction action) {
    for (auto& receiver : receivers) {
        receiver->onKey(key, action);
    }
}

void InputManager::setResizeCallback(std::function<void(int, int)> cb) {
    resize_callback = std::move(cb);
}


void InputManager::bindToWindow(GLFWwindow* window) {
    glfwSetWindowUserPointer(window, this);

    glfwSetCursorPosCallback(window, [](GLFWwindow* win, double x, double y) {
        auto* self = static_cast<InputManager*>(glfwGetWindowUserPointer(win));
        if (self) self->handleMouseMove(x, y);
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* win, int button, int action, int) {
        auto* self = static_cast<InputManager*>(glfwGetWindowUserPointer(win));
        if (!self) return;

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

        double x, y;
        glfwGetCursorPos(win, &x, &y);
        self->handleMouseButton(mb, ka, x, y);
    });

    glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int, int action, int) {
        auto* self = static_cast<InputManager*>(glfwGetWindowUserPointer(win));
        if (!self) return;

        KeyAction ka;
        switch (action) {
            case GLFW_PRESS:   ka = KeyAction::Press;   break;
            case GLFW_RELEASE: ka = KeyAction::Release; break;
            case GLFW_REPEAT:  ka = KeyAction::Repeat;  break;
            default: return;
        }

        self->handleKey(key, ka);
    });

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int width, int height) {
        auto* self = static_cast<InputManager*>(glfwGetWindowUserPointer(win));
        if (!self) return;

        // Broadcast resize to renderer (needs access to it)
        if (self->resize_callback) {
            self->resize_callback(width, height);
        }
    });
}