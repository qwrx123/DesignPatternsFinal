#include <gtest/gtest.h>
#include "ToolManager.h"
#include "BrushTool.h"
#include "EraserTool.h"
#include "LayerManager.h"
#include "StrokeManager.h"

class ToolManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        layerManager = std::make_shared<LayerManager>();
        strokeManager = std::make_shared<StrokeManager>(layerManager);
        layerManager->addLayer();
        layerManager->setActiveLayer(0);

        toolManager = std::make_shared<ToolManager>();

        brush = std::make_shared<BrushTool>(layerManager, strokeManager, Color{1.0F, 0.0F, 0.0F, 1.0F}, 3.0F);
        eraser = std::make_shared<EraserTool>(layerManager, strokeManager, 5.0F);

        toolManager->registerTool("Brush", brush);
        toolManager->registerTool("Eraser", eraser);
    }

    std::shared_ptr<LayerManager> layerManager;
    std::shared_ptr<StrokeManager> strokeManager;
    std::shared_ptr<ToolManager> toolManager;
    std::shared_ptr<BrushTool> brush;
    std::shared_ptr<EraserTool> eraser;
};

TEST_F(ToolManagerTest, SelectToolUpdatesActiveTool) {
    toolManager->selectTool("Brush");
    EXPECT_EQ(toolManager->getActiveTool(), brush);

    toolManager->selectTool("Eraser");
    EXPECT_EQ(toolManager->getActiveTool(), eraser);
}

TEST_F(ToolManagerTest, UndoDelegatesToActiveTool) {
    // Generate a stroke for undo test
    toolManager->selectTool("Brush");
    Point p{10, 10};
    brush->beginStroke(p);
    brush->addPoint(Point{20, 20});
    brush->endStroke(Point{30, 30});
    EXPECT_EQ(strokeManager->getStrokes().size(), 1);

    toolManager->undoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 0);
}

TEST_F(ToolManagerTest, RedoDelegatesToActiveTool) {
    toolManager->selectTool("Brush");
    Point p{10, 10};
    brush->beginStroke(p);
    brush->endStroke(Point{20, 20});
    toolManager->undoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 0);

    toolManager->redoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 1);
}

TEST_F(ToolManagerTest, EraserDelegatesUndoRedoCorrectly) {
    // Create one brush stroke first
    toolManager->selectTool("Brush");
    brush->beginStroke(Point{10, 10});
    brush->endStroke(Point{20, 20});
    EXPECT_EQ(strokeManager->getStrokes().size(), 1);

    // Use eraser to erase
    toolManager->selectTool("Eraser");
    eraser->beginStroke(Point{10, 10});
    eraser->endStroke(Point{10, 10});
    EXPECT_EQ(strokeManager->getStrokes().size(), 1);

    // Undo eraser
    toolManager->undoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 1);
}

TEST_F(ToolManagerTest, SwitchingToolsDoesNotAffectHistories) {
    toolManager->selectTool("Brush");
    brush->beginStroke(Point{10, 10});
    brush->endStroke(Point{20, 20});
    toolManager->undoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 0);

    toolManager->selectTool("Eraser");
    toolManager->undoStroke(); // Eraser undo should not affect brush strokes
    EXPECT_EQ(strokeManager->getStrokes().size(), 0);
}

TEST_F(ToolManagerTest, InvalidToolSelectionDoesNotCrash) {
    EXPECT_NO_THROW(toolManager->selectTool("NonExistentTool"));
}

TEST_F(ToolManagerTest, ActiveToolIsNullIfNoToolSelectedInitially) {
    auto emptyManager = std::make_shared<ToolManager>();
    EXPECT_EQ(emptyManager->getActiveTool(), nullptr);
}

TEST_F(ToolManagerTest, CanClearStrokesViaActiveTool) {
    toolManager->selectTool("Brush");
    brush->beginStroke(Point{10, 10});
    brush->endStroke(Point{20, 20});
    EXPECT_EQ(strokeManager->getStrokes().size(), 1);

    toolManager->clearStrokes();
    EXPECT_EQ(strokeManager->getStrokes().size(), 0);
}