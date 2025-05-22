// CanvasRenderer.h
#ifndef CANVASRENDERER_H
#define CANVASRENDERER_H

#include "ICanvasRenderer.h"
#include "IStroke.h"
#include <GLFW/glfw3.h>

class CanvasRenderer : public ICanvasRenderer {
public:
    CanvasRenderer(GLFWwindow* window);
    ~CanvasRenderer();

    void resize(int width, int height);

    void beginFrame() override;
    void drawStroke(const IStroke& stroke) override;
    void drawButton(const IButton& button) override;
    void drawMenu(const IMenu& menu) override;
    void endFrame() override;

private:
    GLFWwindow* window_;
};

#endif // CANVASRENDERER_H