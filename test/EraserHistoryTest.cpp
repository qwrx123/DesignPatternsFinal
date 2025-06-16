#include <gtest/gtest.h>
#include "BrushTool.h"
#include "EraserTool.h"
#include "StrokeManager.h"
#include "Stroke.h"
#include "LayerManager.h"

class EraserHistoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        layerManager = std::make_shared<LayerManager>();
        strokeManager = std::make_shared<StrokeManager>(layerManager);
        layerManager->addLayer();
        layerManager->setActiveLayer(0);

        brush = std::make_shared<BrushTool>(layerManager, strokeManager, Color{1.0F, 0.0F, 0.0F, 1.0F}, 5.0F);
        eraser = std::make_shared<EraserTool>(layerManager, strokeManager, 5.0F);

        // Build 3 initial strokes
        brush->beginStroke({10, 10});
        brush->addPoint({20, 20});
        brush->endStroke({30, 30});

        brush->beginStroke({40, 40});
        brush->addPoint({50, 50});
        brush->endStroke({60, 60});

        brush->beginStroke({70, 70});
        brush->addPoint({80, 80});
        brush->endStroke({90, 90});

        EXPECT_EQ(strokeManager->getStrokes().size(), 3);
    }

    std::shared_ptr<LayerManager> layerManager;
    std::shared_ptr<StrokeManager> strokeManager;
    std::shared_ptr<BrushTool> brush;
    std::shared_ptr<EraserTool> eraser;
};

TEST_F(EraserHistoryTest, EraserModifiesStrokesAndPushesHistory) {
    auto p_erase1 = Point{15, 15}; // Intersects first stroke

    eraser->beginStroke(p_erase1);
    eraser->endStroke(p_erase1);

    EXPECT_EQ(strokeManager->getStrokes().size(), 3);

    auto history = layerManager->getActiveLayer()->getEraserHistory();
    EXPECT_EQ(history.size(), 3);
    EXPECT_FALSE(history.peek().empty());
}

TEST_F(EraserHistoryTest, EraserUndoRestoresStrokes) {
    auto p_erase1 = Point{15, 15};

    eraser->beginStroke(p_erase1);
    eraser->endStroke(p_erase1);

    EXPECT_EQ(strokeManager->getStrokes().size(), 3);

    eraser->undoStroke();

    EXPECT_EQ(strokeManager->getStrokes().size(), 3);

    auto history = layerManager->getActiveLayer()->getEraserHistory();
    EXPECT_EQ(history.size(), 2);
    EXPECT_EQ(history.undoneSize(), 1);
}

TEST_F(EraserHistoryTest, EraserRedoReappliesErase) {
    auto p_erase1 = Point{15, 15};

    eraser->beginStroke(p_erase1);
    eraser->endStroke(p_erase1);
    eraser->undoStroke();

    EXPECT_EQ(strokeManager->getStrokes().size(), 3);

    auto history = layerManager->getActiveLayer()->getEraserHistory();
    EXPECT_EQ(history.undoneSize(), 1);

    eraser->redoStroke();

    EXPECT_EQ(strokeManager->getStrokes().size(), 3);
    EXPECT_EQ(history.size(), 2);
    EXPECT_EQ(history.undoneSize(), 1);
}

TEST_F(EraserHistoryTest, MultipleEraserUndosWorkSequentially) {
    auto p1 = Point{15, 15};
    auto p2 = Point{45, 45};

    eraser->beginStroke(p1);
    eraser->endStroke(p1);

    eraser->beginStroke(p2);
    eraser->endStroke(p2);

    EXPECT_EQ(strokeManager->getStrokes().size(), 3);
}

TEST_F(EraserHistoryTest, MultipleEraserRedosRestoreSequentially) {
    auto p1 = Point{15, 15};
    auto p2 = Point{45, 45};

    eraser->beginStroke(p1);
    eraser->endStroke(p1);
    eraser->beginStroke(p2);
    eraser->endStroke(p2);

    eraser->undoStroke();
    eraser->undoStroke();

    EXPECT_EQ(strokeManager->getStrokes().size(), 3);
}