#include <GLFW/glfw3.h>

#include "WindowClass.h"

int main(int argc, char** argv)
{
    WindowClass testWindow;
    testWindow.CreateWindow(800, 600, "TestApp");
    testWindow.initCallbacks();

    while(testWindow.shouldClose() == false) {
        testWindow.render();
        testWindow.defaultEvent();
    }
    return 0;
}