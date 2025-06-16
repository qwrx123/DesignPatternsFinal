#include <gtest/gtest.h>
#include "Tools/ToolManager.h"
#include "BrushTool.h"
#include "EraserTool.h"
#include "Stroke.h"
#include "StrokeManager.h"
#include "History.h"
#include "LayerManager.h"

class ToolHistoryTest : public ::testing::Test {
protected:
    std::shared_ptr<LayerManager> layerManager;
    std::shared_ptr<StrokeManager> strokeManager;
    std::shared_ptr<BrushTool> brush;
    std::shared_ptr<EraserTool> eraser;

    Point p1{10, 10}, p2{20, 20}, p3{30, 30}, p4{40, 40}, p5{50, 50};
    std::shared_ptr<IStroke> s1, s2;

    void SetUp() override {
        // Initialize managers
        layerManager = std::make_shared<LayerManager>();
        strokeManager = std::make_shared<StrokeManager>(layerManager);

        // Register one layer
        layerManager->addLayer();

        // Initialize tools
        brush = std::make_shared<BrushTool>(layerManager, strokeManager, Color{1.0f, 0.0f, 0.0f, 1.0f}, 5.0f);
        eraser = std::make_shared<EraserTool>(layerManager, strokeManager, 5.0f);

        // Simulate two strokes
        brush->beginStroke(p1);
        brush->addPoint(p2);
        brush->endStroke(p3);

        brush->beginStroke(p4);
        brush->addPoint(p5);
        brush->endStroke(p3);

        // Store strokes for verification
        s1 = std::make_shared<Stroke>();
        s1->addPoint(p1);
        s1->addPoint(p2);
        s1->addPoint(p3);

        s2 = std::make_shared<Stroke>();
        s2->addPoint(p4);
        s2->addPoint(p5);
        s2->addPoint(p3);
    }
};

// Brush tool undo/redo tests

TEST_F(ToolHistoryTest, BrushUndo) {
    brush->undoStroke();

    auto last = brush->getHistory().peek();
    auto points = last->getPoints();

    ASSERT_EQ(points.size(), 3);
    EXPECT_EQ(points[0].x, p1.x);
    EXPECT_EQ(points[0].y, p1.y);
}

TEST_F(ToolHistoryTest, BrushRedo) {
    brush->undoStroke();
    brush->redoStroke();

    auto last = brush->getHistory().peek();
    auto points = last->getPoints();

    ASSERT_EQ(points.size(), 3);
    EXPECT_EQ(points[0].x, p4.x);
    EXPECT_EQ(points[0].y, p4.y);
}

TEST_F(ToolHistoryTest, BrushUndoAll) {
    brush->undoStroke();
    brush->undoStroke();

    EXPECT_TRUE(brush->getHistory().isEmpty());
}

// Eraser tests

TEST_F(ToolHistoryTest, EraserHistoryTracking) {
    auto initialHistory = layerManager->getActiveLayer()->getEraserHistory();
    ASSERT_EQ(initialHistory.size(), 0); // initial state snapshot

    eraser->beginStroke(p1);
    eraser->addPoint(p2);
    eraser->endStroke(p3);

    auto updatedHistory = layerManager->getActiveLayer()->getEraserHistory();
    ASSERT_EQ(updatedHistory.size(), 3); // after erasure update
}

TEST_F(ToolHistoryTest, EraserUndoRedoFlow) {
    eraser->beginStroke(p1);
    eraser->addPoint(p2);
    eraser->endStroke(p3);

    eraser->undoStroke();
    auto undoHistory = layerManager->getActiveLayer()->getEraserHistory();
    ASSERT_EQ(undoHistory.size(), 2);

    eraser->redoStroke();
    auto redoHistory = layerManager->getActiveLayer()->getEraserHistory();
    ASSERT_EQ(redoHistory.size(), 3);
}

TEST_F(ToolHistoryTest, CombinedBrushAndEraserUndoRedo) {
    eraser->beginStroke(p1);
    eraser->addPoint(p2);
    eraser->endStroke(p3);

    eraser->undoStroke();
    brush->undoStroke();

    ASSERT_EQ(brush->getHistory().size(), 1);
    ASSERT_EQ(layerManager->getActiveLayer()->getEraserHistory().size(), 2);

    brush->redoStroke();
    eraser->redoStroke();

    ASSERT_EQ(brush->getHistory().size(), 2);
    ASSERT_EQ(layerManager->getActiveLayer()->getEraserHistory().size(), 3);
}