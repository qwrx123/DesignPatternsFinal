#include <GL/glew.h>
#include <gtest/gtest.h>
#include <GLFW/glfw3.h>

#include "CanvasRenderer.h"
#include "Stroke.h"
#include "FileLocation.h"

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

TEST(CanvasRendererTest, CanExportCanvas) {
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
    stroke.addPoint({20.0f, 30.0f});
    stroke.addPoint({50.0f, 20.0f});
    stroke.addPoint({80.0f, 30.0f});

    CanvasRenderer renderer(testWindow);
    
    int width, height;
    glfwGetFramebufferSize(testWindow, &width, &height);
    CanvasRenderer::resize(width, height);

    renderer.beginFrame();
    renderer.drawStroke(stroke);
    renderer.endFrame();
    
    glFlush();
    glFinish();

    auto canvasData = renderer.exportCanvas();
    

    bool foundPixel = false;
    for (int i = 0; i < canvasData.bufferSize; ++i) {
        if (canvasData.bufferLocation[i] != 0) {
            foundPixel = true;
        }
    }

    ASSERT_TRUE(canvasData.bufferLocation != nullptr);
    ASSERT_GT(canvasData.bufferSize, 0);
    ASSERT_TRUE(foundPixel);

    // Cleanup
    glfwDestroyWindow(testWindow);
    glfwTerminate();
}

TEST(CanvasRendererTest, CanExportFile) {
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
    stroke.addPoint({20.0f, 30.0f});
    stroke.addPoint({50.0f, 20.0f});
    stroke.addPoint({80.0f, 30.0f});

    CanvasRenderer renderer(testWindow);
    
    int width, height;
    glfwGetFramebufferSize(testWindow, &width, &height);
    CanvasRenderer::resize(width, height);

    renderer.beginFrame();
    renderer.drawStroke(stroke);
    renderer.endFrame();

    glFlush();
    glFinish();

    std::string fileLocation = FileLocation::getDownloadLocation();
    std::string fileName = "TESTEXPORTCANVASBITMAP";

    bool exportSuccess = renderer.exportBitmap(fileName, fileLocation);
    ASSERT_TRUE(exportSuccess);

    std::filesystem::path path(fileLocation + fileName + ".bmp");
    EXPECT_TRUE(std::filesystem::exists(path));

    std::filesystem::remove(path);

    // Cleanup
    glfwDestroyWindow(testWindow);
    glfwTerminate();
}