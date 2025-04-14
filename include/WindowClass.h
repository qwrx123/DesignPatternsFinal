#include <GLFW/glfw3.h>
#include <vector>

class WindowClass
{
public:
    WindowClass();
    ~WindowClass();
    bool CreateWindow(int width, int height, const char *title);
    bool shouldClose() const;
    void defaultEvent();
    bool initCallbacks();

    void render();
protected:
	static void windowSizeCallback(GLFWwindow* window, int width, int height);
	void handleWindowSize(int width, int height);

protected:
    int width;
    int height;
    const char* title;
    GLFWwindow* window;

//Basic brush stroke implementation
protected:
    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    void handleMouseMove(double xpos, double ypos);
    void handleMouseButton(int button, int action, int mods);

    std::vector<std::pair<float, float>> strokePoints;
    bool isDrawing = false;
};