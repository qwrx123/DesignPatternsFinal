#include <gtest/gtest.h>
#include "Tools/ToolManager.h"
#include "drawing/IDrawingTool.h"
#include "BrushTool.h"
#include "Stroke.h"
#include "EraserTool.h"
#include "Text.h"
#include "StrokeManager.h"

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
    auto strokeManager = std::make_shared<StrokeManager>();
    auto brush = std::make_shared<BrushTool>(strokeManager, Color{0.0f, 1.0f, 0.0f, 1.0f}, 3.0f);

    ToolManager tm;
    tm.registerTool("Brush", brush);
    tm.selectTool("Brush");

    Point p1{10, 10};
    Point p2{20, 20};
    Point p3{30, 30};

    tm.beginStroke(p1);
    tm.addPoint(p2);
    tm.endStroke(p3);

    const auto& strokes = strokeManager->getStrokes();
    ASSERT_EQ(strokes.size(), 1);
    auto stroke = std::dynamic_pointer_cast<Stroke>(strokes[0]);
    ASSERT_NE(stroke, nullptr);

    const auto& pts = stroke->getPoints();
    ASSERT_EQ(pts.size(), 3);
    EXPECT_EQ(pts[0].x, 10);
    EXPECT_EQ(pts[1].y, 20);
    EXPECT_EQ(pts[2].x, 30);
}

TEST(ToolManagerTest, SwitchesBetweenBrushAndEraser) {
    ToolManager tm;

    auto brush = std::make_shared<BrushTool>(Color{1, 0, 0, 1}, 2.0f);
    auto eraser = std::make_shared<EraserTool>(10.0f);

    tm.registerTool("Brush", brush);
    tm.registerTool("Eraser", eraser);

    // ToolManager should default to the first registered tool
    EXPECT_EQ(tm.getActiveToolName(), "Brush");
    EXPECT_EQ(tm.getActiveTool(), brush);

    // Switch to Eraser
    EXPECT_TRUE(tm.selectTool("Eraser"));
    EXPECT_EQ(tm.getActiveToolName(), "Eraser");
    EXPECT_EQ(tm.getActiveTool(), eraser);

    // Switch back to Brush
    EXPECT_TRUE(tm.selectTool("Brush"));
    EXPECT_EQ(tm.getActiveToolName(), "Brush");
    EXPECT_EQ(tm.getActiveTool(), brush);

    // Should not switch to unregistered tool
    EXPECT_FALSE(tm.selectTool("MagicWand"));
}