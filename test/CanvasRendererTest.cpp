#include <GL/glew.h>
#include <gtest/gtest.h>
#include <GLFW/glfw3.h>

#include "CanvasRenderer.h"
#include "Stroke.h"

TEST(CanvasRendererTest, CanRenderSimpleStrokeWithoutCrash) {
    // Setup minimal OpenGL context for testing
    if (!glfwInit()) {
        FAIL() << "GLFW failed to initialize";
    }

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // 👈 prevent test window from popping up
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLFWwindow* testWindow = glfwCreateWindow(100, 100, "TestContext", nullptr, nullptr);
    ASSERT_NE(testWindow, nullptr) << "Failed to create GLFW test window";

    glfwMakeContextCurrent(testWindow);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        glfwDestroyWindow(testWindow);
        glfwTerminate();
        FAIL() << "GLEW failed to initialize";
    }

    // Prepare test stroke and renderer
    Color red = {1.0f, 0.0f, 0.0f, 1.0f};
    float thickness = 3.0f;
    Stroke stroke(red, thickness);
    stroke.addPoint({-0.5f, 0.0f});
    stroke.addPoint({0.0f, 0.5f});
    stroke.addPoint({0.5f, 0.0f});

    CanvasRenderer renderer(testWindow);

    // Just ensure it doesn't crash
    renderer.beginFrame();
    renderer.drawStroke(stroke);
    renderer.endFrame();

    // Cleanup
    glfwDestroyWindow(testWindow);
    glfwTerminate();
}