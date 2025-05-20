#include <gtest/gtest.h>
#include "Tools/ToolManager.h"
#include "drawing/IDrawingTool.h"
#include "BrushTool.h"
#include "Stroke.h"

TEST(ToolManagerTest, CanRegisterAndSelectTool) {
    ToolManager tm;
    auto brush = std::make_shared<BrushTool>(Color{1.0f, 0.0f, 0.0f, 1.0f}, 5.0f);

    tm.registerTool("Brush", brush);
    EXPECT_EQ(tm.getActiveToolName(), "Brush");
    EXPECT_EQ(tm.getActiveTool(), brush);

    EXPECT_TRUE(tm.selectTool("Brush"));
    EXPECT_FALSE(tm.selectTool("Eraser"));  // Not registered
}

TEST(ToolManagerTest, DelegatesToBrushTool) {
    ToolManager tm;
    auto brush = std::make_shared<BrushTool>(Color{0.0f, 1.0f, 0.0f, 1.0f}, 3.0f);
    tm.registerTool("Brush", brush);

    Point p1{10, 10};
    Point p2{20, 20};
    Point p3{30, 30};

    tm.beginStroke(p1);
    tm.addPoint(p2);
    tm.endStroke(p3);

    auto stroke = std::dynamic_pointer_cast<Stroke>(brush->getCurrentStroke());
    ASSERT_NE(stroke, nullptr);
    EXPECT_EQ(stroke->getPoints().size(), 3);
    EXPECT_EQ(stroke->getPoints()[0].x, 10);
    EXPECT_EQ(stroke->getPoints()[1].y, 20);
    EXPECT_EQ(stroke->getPoints()[2].x, 30);
}