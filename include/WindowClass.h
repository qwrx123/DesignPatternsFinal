#include <GLFW/glfw3.h>


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
};