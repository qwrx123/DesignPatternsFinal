#include <gtest/gtest.h>
#include "BrushTool.h"
#include "EraserTool.h"
#include "StrokeManager.h"
#include "Stroke.h"
#include "History.h"
#include "LayerManager.h"

class ToolIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        layerManager = std::make_shared<LayerManager>();
        strokeManager = std::make_shared<StrokeManager>(layerManager);
        layerManager->addLayer();
        layerManager->setActiveLayer(0);

        brush = std::make_shared<BrushTool>(layerManager, strokeManager, Color{1.0F, 0.0F, 0.0F, 1.0F}, 5.0F);
        eraser = std::make_shared<EraserTool>(layerManager, strokeManager, 5.0F);

        Point p1{10, 10}, p2{20, 20}, p3{30, 30};
        Point p4{40, 40}, p5{50, 50}, p6{60, 60};
        Point p7{70, 70}, p8{80, 80}, p9{90, 90};

        brush->beginStroke(p1); brush->addPoint(p2); brush->endStroke(p3);
        brush->beginStroke(p4); brush->addPoint(p5); brush->endStroke(p6);
        brush->beginStroke(p7); brush->addPoint(p8); brush->endStroke(p9);
    }

    std::shared_ptr<LayerManager> layerManager;
    std::shared_ptr<StrokeManager> strokeManager;
    std::shared_ptr<BrushTool> brush;
    std::shared_ptr<EraserTool> eraser;
};

TEST_F(ToolIntegrationTest, BrushUndoFollowedByEraserUndo) {
    auto pErase = Point{15, 15};

    eraser->beginStroke(pErase);
    eraser->endStroke(pErase);
    EXPECT_EQ(strokeManager->getStrokes().size(), 3);

    brush->undoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 2);

    eraser->undoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 3);
}

TEST_F(ToolIntegrationTest, EraserUndoFollowedByBrushUndo) {
    auto pErase = Point{15, 15};

    eraser->beginStroke(pErase);
    eraser->endStroke(pErase);
    EXPECT_EQ(strokeManager->getStrokes().size(), 3);

    eraser->undoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 3);

    brush->undoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 2);
}

TEST_F(ToolIntegrationTest, MixedUndoRedoSequence) {
    auto pErase = Point{15, 15};

    eraser->beginStroke(pErase);
    eraser->endStroke(pErase);
    EXPECT_EQ(strokeManager->getStrokes().size(), 3);

    brush->undoStroke();
    brush->redoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 3);

    eraser->undoStroke();
    eraser->redoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 3);
}

TEST_F(ToolIntegrationTest, EraserMultipleActionsThenUndoRedo) {
    auto pErase1 = Point{15, 15};
    auto pErase2 = Point{45, 45};

    eraser->beginStroke(pErase1);
    eraser->endStroke(pErase1);
    eraser->beginStroke(pErase2);
    eraser->endStroke(pErase2);

    EXPECT_EQ(strokeManager->getStrokes().size(), 3);

    eraser->undoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 3);

    eraser->redoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 3);
}

TEST_F(ToolIntegrationTest, UndoRedoWithNoEraserApplied) {
    brush->undoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 2);
    brush->redoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 3);
}

TEST_F(ToolIntegrationTest, RedoWithoutUndoHasNoEffect) {
    brush->redoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 3);
    eraser->redoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 3);
}

TEST_F(ToolIntegrationTest, UndoBeyondBrushHistoryKeepsZero) {
    brush->undoStroke();
    brush->undoStroke();
    brush->undoStroke();
    brush->undoStroke(); // extra undo

    EXPECT_EQ(strokeManager->getStrokes().size(), 0);
}

TEST_F(ToolIntegrationTest, EraserUndoBeyondLimitSafe) {
    auto pErase = Point{15, 15};
    eraser->beginStroke(pErase);
    eraser->endStroke(pErase);

    eraser->undoStroke();
    eraser->undoStroke();
    eraser->undoStroke();

    EXPECT_EQ(strokeManager->getStrokes().size(), 3);
}

TEST_F(ToolIntegrationTest, EraserRedoBeyondLimitSafe) {
    auto pErase = Point{15, 15};
    eraser->beginStroke(pErase);
    eraser->endStroke(pErase);
    eraser->undoStroke();

    eraser->redoStroke();
    eraser->redoStroke();

    EXPECT_EQ(strokeManager->getStrokes().size(), 3);
}

TEST_F(ToolIntegrationTest, SwitchingLayersKeepsIndependentHistories) {
    layerManager->addLayer();
    layerManager->setActiveLayer(1);

    brush->beginStroke(Point{5, 5});
    brush->endStroke(Point{10, 10});

    EXPECT_EQ(strokeManager->getStrokes().size(), 1);

    brush->undoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 0);
}