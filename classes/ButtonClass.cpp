#include <GLFW/glfw3.h>
#include "ButtonClass.h"

ButtonClass::ButtonClass(double x, double y, double width, double height, double percentRed, double percentGreen, double percentBlue)
    : left(x), top(y), red(percentRed), green(percentGreen), blue(percentBlue)
{
    right = left + width - 1;
    bottom = top + height - 1;
}

ButtonClass::~ButtonClass()
{

}

double ButtonClass::getTop()
{
    return top;
}

double ButtonClass::getBottom()
{
    return bottom;
}

double ButtonClass::getLeft()
{
    return left;
}

double ButtonClass::getRight()
{
    return right;
}

void ButtonClass::renderButton()
{
    glBegin(GL_QUADS);
        glColor3f(red, green, blue);
        glVertex2f(left, top);
        glVertex2f(right, top);
        glVertex2f(right, bottom);
        glVertex2f(left, bottom);
    glEnd();
}