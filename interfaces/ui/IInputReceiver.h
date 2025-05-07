#ifndef IINPUTRECEIVER_H
#define IINPUTRECEIVER_H

enum class MouseButton { Left, Right, Middle };
enum class KeyAction { Press, Release, Repeat };

class IInputReceiver {
public:
 IInputReceiver()		   = default;
 virtual ~IInputReceiver() = default;

 virtual void onMouseMove(double x, double y)										  = 0;
 virtual void onMouseButton(MouseButton button, KeyAction action, double x, double y) = 0;
 virtual void onKey(int key, KeyAction action)										  = 0;
};

#endif // IINPUTRECEIVER