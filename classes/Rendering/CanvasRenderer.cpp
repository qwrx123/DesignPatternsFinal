#include "CanvasRenderer.h"
#include <iostream>

CanvasRenderer::CanvasRenderer(GLFWwindow* window)
    : window_(window)
{
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1); // ← Top-left is (0,0)
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

CanvasRenderer::~CanvasRenderer() {}

void CanvasRenderer::beginFrame() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background
    glClear(GL_COLOR_BUFFER_BIT);
}

void CanvasRenderer::drawStroke(const IStroke& stroke) {
    const auto& points = stroke.getPoints();
    if (points.size() < 2) return;
    
    glLineWidth(stroke.getThickness());
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_STRIP);
    for (const auto& p : points) {
        glVertex2d(p.x, p.y);
    }
    glEnd();
}

void CanvasRenderer::endFrame() {
    glfwSwapBuffers(window_);
}

void CanvasRenderer::resize(int width, int height) {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1); // Top-left origin

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}