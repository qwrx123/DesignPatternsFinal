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
