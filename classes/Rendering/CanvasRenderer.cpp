#include "CanvasRenderer.h"

CanvasRenderer::CanvasRenderer(GLFWwindow* window)
    : window_(window) {}

CanvasRenderer::~CanvasRenderer() {}

void CanvasRenderer::beginFrame() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background
    glClear(GL_COLOR_BUFFER_BIT);
}

void CanvasRenderer::drawStroke(const IStroke& stroke) {
    const auto& points = stroke.getPoints();
    float thickness = stroke.getThickness();
    const auto& color = stroke.getColor();

    glColor4f(color.r, color.g, color.b, color.a);
    glLineWidth(thickness);

    glBegin(GL_LINE_STRIP);
    for (const auto& pt : points) {
        glVertex2f(pt.x, pt.y);
    }
    glEnd();
}

void CanvasRenderer::endFrame() {
    glfwSwapBuffers(window_);
}