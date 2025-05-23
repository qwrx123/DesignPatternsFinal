#include <GLFW/glfw3.h>
#include <vector>
#include "MenuBar.h"

class WindowClass
{
   public:
	WindowClass();
	~WindowClass();
	bool			   CreateWindow(int width, int height, const char* title);
	[[nodiscard]] bool shouldClose() const;
	static void		   defaultEvent();
	bool			   initCallbacks();
	void			   render();

   private:
	// Window Constants
	static const int				   DEFAULT_WIDTH  = 800;
	static const int				   DEFAULT_HEIGHT = 600;
	static constexpr const char* const DEFAULT_TITLE  = "Drawing App";
	static constexpr const float	   DEFAULT_RADIUS = 20.0F;

	static void windowSizeCallback(GLFWwindow* window, int width, int height);
	void		handleWindowSize(int width, int height);

	int			width  = DEFAULT_WIDTH;
	int			height = DEFAULT_HEIGHT;
	const char* title  = DEFAULT_TITLE;
	GLFWwindow* window = nullptr;
	MenuBar		toolBar;  // added to test toolBar

	// Mouse Interactions
	static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void		handleMouseMove(double xpos, double ypos);
	void		handleMouseButton(int button, int action, int mods);

	// Keyboard Interactions
	static void characterCallback(GLFWwindow* window, unsigned int codepoint);
	void		handleCharacterInput(unsigned int codepoint);

	// Tools
	enum class ToolType : uint8_t
	{
		Brush,
		Eraser
	};
	ToolType currentTool = ToolType::Brush;

	// Brush
	std::vector<std::vector<std::pair<double, double>>> strokes;
	std::vector<std::pair<double, double>>*				currentStroke = nullptr;
	bool												isDrawing	  = false;

	// Eraser
	void   eraseAtCursor(double xpos, double ypos);
	double eraser_radius = DEFAULT_RADIUS;
	double prevEraserX	 = 0;
	double prevEraserY	 = 0;
	bool   isErasing	 = false;
};