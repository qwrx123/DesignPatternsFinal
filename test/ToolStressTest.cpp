#include <gtest/gtest.h>
#include "BrushTool.h"
#include "EraserTool.h"
#include "StrokeManager.h"
#include "Stroke.h"
#include "History.h"
#include "LayerManager.h"

class ToolStressTest : public ::testing::Test {
protected:
    void SetUp() override {
        layerManager = std::make_shared<LayerManager>();
        strokeManager = std::make_shared<StrokeManager>(layerManager);
        layerManager->addLayer();
        layerManager->setActiveLayer(0);

        brush = std::make_shared<BrushTool>(layerManager, strokeManager, Color{1.0F, 0.0F, 0.0F, 1.0F}, 5.0F);
        eraser = std::make_shared<EraserTool>(layerManager, strokeManager, 5.0F);
    }

    std::shared_ptr<LayerManager> layerManager;
    std::shared_ptr<StrokeManager> strokeManager;
    std::shared_ptr<BrushTool> brush;
    std::shared_ptr<EraserTool> eraser;
};

TEST_F(ToolStressTest, CanHandleManyBrushStrokes) {
    for (int i = 0; i < 100; ++i) {
        Point p{static_cast<float>(i), static_cast<float>(i)};
        brush->beginStroke(p);
        brush->endStroke(p);
    }
    EXPECT_EQ(strokeManager->getStrokes().size(), 100);
}

TEST_F(ToolStressTest, UndoAllBrushes) {
    for (int i = 0; i < 10; ++i) {
        Point p{static_cast<float>(i), static_cast<float>(i)};
        brush->beginStroke(p);
        brush->endStroke(p);
    }
    for (int i = 0; i < 10; ++i)
        brush->undoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 0);
}

TEST_F(ToolStressTest, RedoAllBrushes) {
    for (int i = 0; i < 10; ++i) {
        Point p{static_cast<float>(i), static_cast<float>(i)};
        brush->beginStroke(p);
        brush->endStroke(p);
    }
    for (int i = 0; i < 10; ++i)
        brush->undoStroke();
    for (int i = 0; i < 10; ++i)
        brush->redoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 10);
}

TEST_F(ToolStressTest, EraserMultipleLayers) {
    for (int i = 0; i < 5; ++i)
        layerManager->addLayer();

    for (int i = 0; i < 6; ++i) {
        layerManager->setActiveLayer(i);
        Point p{10.0F, 10.0F};
        brush->beginStroke(p);
        brush->endStroke(p);
    }

    for (int i = 0; i < 6; ++i) {
        layerManager->setActiveLayer(i);
        eraser->beginStroke(Point{10.0F, 10.0F});
        eraser->endStroke(Point{10.0F, 10.0F});
    }

    EXPECT_EQ(strokeManager->getStrokes().size(), 0);
}

TEST_F(ToolStressTest, MixedBrushAndEraserStressTest) {
    for (int i = 0; i < 20; ++i) {
        Point p{static_cast<float>(i), static_cast<float>(i)};
        brush->beginStroke(p);
        brush->endStroke(p);
    }

    for (int i = 0; i < 5; ++i) {
        eraser->beginStroke(Point{static_cast<float>(i), static_cast<float>(i)});
        eraser->endStroke(Point{static_cast<float>(i), static_cast<float>(i)});
    }

    EXPECT_TRUE(strokeManager->getStrokes().size() <= 20);
}

TEST_F(ToolStressTest, EraserUndoWorksAcrossStressTest) {
    for (int i = 0; i < 10; i++) {
        Point p{static_cast<float>(i), static_cast<float>(i)};
        brush->beginStroke(p);
        brush->endStroke(p);
    }

    for (int i = 0; i < 3; i++) {
        eraser->beginStroke(Point{static_cast<float>(i), static_cast<float>(i)});
        eraser->endStroke(Point{static_cast<float>(i), static_cast<float>(i)});
    }

    eraser->undoStroke();
    eraser->undoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 5);
}

TEST_F(ToolStressTest, LayerIsolationStressTest) {
    for (int i = 0; i < 3; ++i)
        layerManager->addLayer();

    for (int i = 0; i < 4; ++i) {
        layerManager->setActiveLayer(i);
        Point p{5.0F, 5.0F};
        brush->beginStroke(p);
        brush->endStroke(p);
    }

    for (int i = 0; i < 4; ++i) {
        layerManager->setActiveLayer(i);
        eraser->beginStroke(Point{5.0F, 5.0F});
        eraser->endStroke(Point{5.0F, 5.0F});
    }

    EXPECT_EQ(strokeManager->getStrokes().size(), 0);
}

TEST_F(ToolStressTest, UndoRedoAlternationStressTest) {
    for (int i = 0; i < 20; ++i) {
        Point p{static_cast<float>(i), static_cast<float>(i)};
        brush->beginStroke(p);
        brush->endStroke(p);
    }

    for (int i = 0; i < 10; ++i) {
        brush->undoStroke();
        brush->redoStroke();
    }

    EXPECT_EQ(strokeManager->getStrokes().size(), 20);
}

TEST_F(ToolStressTest, HandlesUndoAfterLayerSwitchStress) {
    layerManager->addLayer();
    layerManager->setActiveLayer(1);
    brush->beginStroke(Point{10.0F, 10.0F});
    brush->endStroke(Point{20.0F, 20.0F});
    brush->undoStroke();
    EXPECT_EQ(strokeManager->getStrokes().size(), 0);
}

TEST_F(ToolStressTest, NoCrashWhenUndoEmpty) {
    brush->undoStroke();
    brush->undoStroke();
    brush->undoStroke();
    brush->redoStroke();
    brush->redoStroke();
    brush->redoStroke();

    EXPECT_EQ(strokeManager->getStrokes().size(), 0);
}