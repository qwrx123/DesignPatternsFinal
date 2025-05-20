#include <gtest/gtest.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "CanvasRenderer.h"
#include "Stroke.h"

class CanvasRendererTest : public ::testing::Test {
protected:
    GLFWwindow* window = nullptr;
    CanvasRenderer* renderer = nullptr;

    void SetUp() override {
        ASSERT_TRUE(glfwInit());

        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);  // Hide window
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(800, 600, "Offscreen Test", nullptr, nullptr);
        ASSERT_NE(window, nullptr);

        glfwMakeContextCurrent(window);
        ASSERT_TRUE(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

        renderer = new CanvasRenderer(window);
    }

    void TearDown() override {
        delete renderer;
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

TEST_F(CanvasRendererTest, CanRenderSimpleStrokeWithoutCrash) {
	Color red = {1.0f, 0.0f, 0.0f, 1.0f};
	float  thickness = 3.0f;
	Stroke stroke(red, thickness);

    stroke.addPoint({-0.5f, 0.0f});
    stroke.addPoint({0.0f, 0.5f});
    stroke.addPoint({0.5f, 0.0f});

    EXPECT_NO_THROW({
        renderer->beginFrame();
        renderer->drawStroke(stroke);
        renderer->endFrame();
    });
}