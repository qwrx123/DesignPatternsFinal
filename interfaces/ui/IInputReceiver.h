#ifndef IINPUTRECEIVER_H
#define IINPUTRECEIVER_H

enum class MouseButton : std::uint8_t
{
	Left,
	Right,
	Middle
};
enum class KeyAction : std::uint8_t
{
	Press,
	Release,
	Repeat
};

class IInputReceiver
{
   public:
	IInputReceiver()		  = default;
	virtual ~IInputReceiver() = default;

	virtual void onMouseMove(double x, double y)										 = 0;
	virtual void onMouseButton(MouseButton button, KeyAction action, double x, double y) = 0;
	virtual void onKey(int key, KeyAction action)										 = 0;
	virtual void onChar(unsigned int codepoint)											 = 0;
};

#endif	// IINPUTRECEIVER