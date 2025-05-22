// CanvasRenderer.h
#ifndef CANVASRENDERER_H
#define CANVASRENDERER_H

#include "ICanvasRenderer.h"
#include "IStroke.h"
#include "IText.h"
#include <GLFW/glfw3.h>

class CanvasRenderer : public ICanvasRenderer {
public:
    CanvasRenderer(GLFWwindow* window);
    ~CanvasRenderer();

    void resize(int width, int height);

    void beginFrame() override;
    void drawStroke(const IStroke& stroke) override;
    void renderText(const IText& text);
    void endFrame() override;

    void textRenderTest();

private:
    GLFWwindow* window_;
};

#endif // CANVASRENDERER_H