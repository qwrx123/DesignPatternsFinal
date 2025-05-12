#ifndef IINPUTMANAGER_H
#define IINPUTMANAGER_H

#include <memory>
#include "IInputReceiver.h"

class IInputManager
{
   public:
	IInputManager()			 = default;
	virtual ~IInputManager() = default;

	virtual void registerReceiver(std::shared_ptr<IInputReceiver> receiver)	  = 0;
	virtual void unregisterReceiver(std::shared_ptr<IInputReceiver> receiver) = 0;

	virtual void beginFrame() = 0;
	virtual void endFrame()	  = 0;

	// These get called from GLFW
	virtual void handleMouseMove(double x, double y)										 = 0;
	virtual void handleMouseButton(MouseButton button, KeyAction action, double x, double y) = 0;
	virtual void handleKey(int key, KeyAction action)										 = 0;
};

#endif	// IINPUTMANAGER_H