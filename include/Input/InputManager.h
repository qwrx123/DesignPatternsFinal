#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "IInputManager.h"
#include <vector>
#include <memory>

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

private:
    std::vector<std::shared_ptr<IInputReceiver>> receivers;
};

#endif // INPUTMANAGER_H