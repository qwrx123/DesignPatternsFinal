#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "IInputManager.h"
#include <vector>
#include <memory>
#include <functional>
#include <GLFW/glfw3.h>

class InputManager : public IInputManager {
public:
    InputManager();

	void registerReceiver(std::shared_ptr<IInputReceiver> receiver) override;
    void unregisterReceiver(std::shared_ptr<IInputReceiver> receiver) override;

    void beginFrame() override;
    void endFrame() override;

    void handleMouseMove(double x, double y) override;
    void handleMouseButton(MouseButton button, KeyAction action, double x, double y) override;
    void handleKey(int key, KeyAction action) override;
    void handleChar(unsigned int codepoint) override;

    void setResizeCallback(std::function<void(int, int)> cb);

	void bindToWindow(GLFWwindow* window);  // Registers callbacks internally

private:
    std::vector<std::shared_ptr<IInputReceiver>> receivers;
    std::function<void(int, int)> resize_callback;
};

#endif // INPUTMANAGER_H