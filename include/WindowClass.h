#include <GLFW/glfw3.h>
#include <vector>

class WindowClass
{
   public:
	WindowClass();
	~WindowClass();
	bool CreateWindow(int width, int height, const char* title);
	bool shouldClose() const;
	void defaultEvent();
	bool initCallbacks();
	void render();

   protected:
	static void windowSizeCallback(GLFWwindow* window, int width, int height);
	void		handleWindowSize(int width, int height);

   protected:
	int			width;
	int			height;
	const char* title;
	GLFWwindow* window;

	// Mouse Interactions
   protected:
	static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void		handleMouseMove(double xpos, double ypos);
	void		handleMouseButton(int button, int action, int mods);

	// Keyboard Interactions
   protected:
	static void characterCallback(GLFWwindow* window, unsigned int codepoint);
	void		handleCharacterInput(unsigned int codepoint);

	// Tools
   protected:
	enum class ToolType
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
	double eraser_radius = 20.0f;
	double prevEraserX;
	double prevEraserY;
	bool   isErasing = false;
};