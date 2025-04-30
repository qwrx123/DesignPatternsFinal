#ifndef BUTTON_CLASS_H
#define BUTTON_CLASS_H

#include <GLFW/glfw.h>

class ButtonClass
{
    private:
        double top;
        double bottom;
        double left;
        double right;
        double red;
        double green;
        double blue;

    public:
        ButtonClass(double x, double y, double width, double height, double percentRed, double percentGreen, double percentBlue);
        ~ButtonClass();
        double getTop();
        double getBottom();
        double getLeft();
        double getRight();
        void renderButton();
};

#endif