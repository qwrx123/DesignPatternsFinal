#include <gtest/gtest.h>
#include "Tools/ToolManager.h"
#include "drawing/IDrawingTool.h"
#include "BrushTool.h"
#include "Stroke.h"
#include "EraserTool.h"
#include "StrokeManager.h"
#include "ToolHistory.h"

class ToolHistoryTest : public ::testing::Test {
protected:
    void SetUp() override 
    {
        history = std::make_shared<ToolHistory>();
        brushStrokeManager = std::make_shared<StrokeManager>();
        brush = std::make_shared<BrushTool>(brushStrokeManager, Color{1.0F, 0.0F, 0.0F, 1.0F}, 5.0F);
        //eraserStrokeManager = std::make_shared<StrokeManager>();
        //eraser = std::make_shared<EraserTool>(eraserStrokeManager, 3.0F);
        s1 = std::make_shared<Stroke>();
        s2 = std::make_shared<Stroke>();
        s3 = std::make_shared<Stroke>();
        expected = std::shared_ptr<IStroke>();
        actual = std::shared_ptr<IStroke>();

        p1 = {10, 10};
        p2 = {20, 20};
        p3 = {30, 30};
        p4 = {40, 40};
        p5 = {50, 50};
        p6 = {60, 60};
        p7 = {70, 70};
        p8 = {80, 80};
        p9 = {90, 90};

        brush->beginStroke(p1);
        brush->addPoint(p2);
        brush->endStroke(p3);
        brush->beginStroke(p4);
        brush->addPoint(p5);
        brush->endStroke(p6);
        brush->beginStroke(p7);
        brush->addPoint(p8);
        brush->endStroke(p9);

        s1->addPoint(p1);
        s1->addPoint(p2);
        s1->addPoint(p3);

        s2->addPoint(p4);
        s2->addPoint(p5);
        s2->addPoint(p6);

        s3->addPoint(p7);
        s3->addPoint(p8);
        s3->addPoint(p9);

        history->push(s1);
        history->push(s2);
        history->push(s3);

        /*
        eraser->beginStroke(p1);
        eraser->addPoint(p2);
        eraser->endStroke(p3);
        eraser->beginStroke(p4);
        eraser->addPoint(p5);
        eraser->endStroke(p6);
        eraser->beginStroke(p7);
        eraser->addPoint(p8);
        eraser->endStroke(p9);
        */
    }

    void TearDown() override 
    {

    }

    std::shared_ptr<ToolHistory> history;
    std::shared_ptr<BrushTool> brush;
    //std::shared_ptr<EraserTool> eraser;
    std::shared_ptr<StrokeManager> brushStrokeManager;
    //std::shared_ptr<StrokeManager> eraserStrokeManager;
    std::shared_ptr<IStroke> s1;
    std::shared_ptr<IStroke> s2;
    std::shared_ptr<IStroke> s3;
    Point p1;
    Point p2;
    Point p3;
    Point p4;
    Point p5;
    Point p6;
    Point p7;
    Point p8;
    Point p9;
    std::shared_ptr<IStroke> expected;
    std::shared_ptr<IStroke> actual;
};

TEST_F(ToolHistoryTest, Undo)
{
    history->undo();
    expected = s2;
    actual = history->peek();
    const auto& exp = expected->getPoints();
    const auto& act = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act.size(), 3);
    EXPECT_EQ(exp.size(), act.size());
    EXPECT_EQ(exp[0].x, act[0].x);
    EXPECT_EQ(exp[0].y, act[0].y);
    EXPECT_EQ(exp[1].x, act[1].x);
    EXPECT_EQ(exp[1].y, act[1].y);
    EXPECT_EQ(exp[2].x, act[2].x);
    EXPECT_EQ(exp[2].y, act[2].y);
}

TEST_F(ToolHistoryTest, Redo)
{
    history->undo();
    history->undo();
    history->redo();
    expected = s2;
    actual = history->peek();
    const auto& exp = expected->getPoints();
    const auto& act = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act.size(), 3);
    EXPECT_EQ(exp.size(), act.size());
    EXPECT_EQ(exp[0].x, act[0].x);
    EXPECT_EQ(exp[0].y, act[0].y);
    EXPECT_EQ(exp[1].x, act[1].x);
    EXPECT_EQ(exp[1].y, act[1].y);
    EXPECT_EQ(exp[2].x, act[2].x);
    EXPECT_EQ(exp[2].y, act[2].y);
    
}

TEST_F(ToolHistoryTest, BrushUndo)
{
    brush->undoStroke();
    expected = s2;
    actual = brush->getHistory().peek();
    const auto& exp = expected->getPoints();
    const auto& act = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act.size(), 3);
    EXPECT_EQ(exp.size(), act.size());
    EXPECT_EQ(exp[0].x, act[0].x);
    EXPECT_EQ(exp[0].y, act[0].y);
    EXPECT_EQ(exp[1].x, act[1].x);
    EXPECT_EQ(exp[1].y, act[1].y);
    EXPECT_EQ(exp[2].x, act[2].x);
    EXPECT_EQ(exp[2].y, act[2].y);
    actual = brushStrokeManager->getStrokes().back();
    const auto& act2 = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act2.size(), 3);
    EXPECT_EQ(exp.size(), act2.size());
    EXPECT_EQ(exp[0].x, act2[0].x);
    EXPECT_EQ(exp[0].y, act2[0].y);
    EXPECT_EQ(exp[1].x, act2[1].x);
    EXPECT_EQ(exp[1].y, act2[1].y);
    EXPECT_EQ(exp[2].x, act2[2].x);
    EXPECT_EQ(exp[2].y, act2[2].y);
}

TEST_F(ToolHistoryTest, BrushRedo)
{
    brush->undoStroke();
    brush->undoStroke();
    brush->redoStroke();
    expected = s2;
    actual = brush->getHistory().peek();
    const auto& exp = expected->getPoints();
    const auto& act = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act.size(), 3);
    EXPECT_EQ(exp.size(), act.size());
    EXPECT_EQ(exp[0].x, act[0].x);
    EXPECT_EQ(exp[0].y, act[0].y);
    EXPECT_EQ(exp[1].x, act[1].x);
    EXPECT_EQ(exp[1].y, act[1].y);
    EXPECT_EQ(exp[2].x, act[2].x);
    EXPECT_EQ(exp[2].y, act[2].y);
    actual = brushStrokeManager->getStrokes().back();
    const auto& act2 = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act2.size(), 3);
    EXPECT_EQ(exp.size(), act2.size());
    EXPECT_EQ(exp[0].x, act2[0].x);
    EXPECT_EQ(exp[0].y, act2[0].y);
    EXPECT_EQ(exp[1].x, act2[1].x);
    EXPECT_EQ(exp[1].y, act2[1].y);
    EXPECT_EQ(exp[2].x, act2[2].x);
    EXPECT_EQ(exp[2].y, act2[2].y);
}

TEST_F(ToolHistoryTest, DoubleBrushUndo)
{
    brush->undoStroke();
    brush->undoStroke();
    expected = s1;
    actual = brush->getHistory().peek();
    const auto& exp = expected->getPoints();
    const auto& act = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act.size(), 3);
    EXPECT_EQ(exp.size(), act.size());
    EXPECT_EQ(exp[0].x, act[0].x);
    EXPECT_EQ(exp[0].y, act[0].y);
    EXPECT_EQ(exp[1].x, act[1].x);
    EXPECT_EQ(exp[1].y, act[1].y);
    EXPECT_EQ(exp[2].x, act[2].x);
    EXPECT_EQ(exp[2].y, act[2].y);
    actual = brushStrokeManager->getStrokes().back();
    const auto& act2 = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act2.size(), 3);
    EXPECT_EQ(exp.size(), act2.size());
    EXPECT_EQ(exp[0].x, act2[0].x);
    EXPECT_EQ(exp[0].y, act2[0].y);
    EXPECT_EQ(exp[1].x, act2[1].x);
    EXPECT_EQ(exp[1].y, act2[1].y);
    EXPECT_EQ(exp[2].x, act2[2].x);
    EXPECT_EQ(exp[2].y, act2[2].y);
}

TEST_F(ToolHistoryTest, DoubleBrushRedo)
{
    brush->undoStroke();
    brush->undoStroke();
    brush->undoStroke();
    brush->redoStroke();
    brush->redoStroke();
    expected = s2;
    actual = brush->getHistory().peek();
    const auto& exp = expected->getPoints();
    const auto& act = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act.size(), 3);
    EXPECT_EQ(exp.size(), act.size());
    EXPECT_EQ(exp[0].x, act[0].x);
    EXPECT_EQ(exp[0].y, act[0].y);
    EXPECT_EQ(exp[1].x, act[1].x);
    EXPECT_EQ(exp[1].y, act[1].y);
    EXPECT_EQ(exp[2].x, act[2].x);
    EXPECT_EQ(exp[2].y, act[2].y);
    actual = brushStrokeManager->getStrokes().back();
    const auto& act2 = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act2.size(), 3);
    EXPECT_EQ(exp.size(), act2.size());
    EXPECT_EQ(exp[0].x, act2[0].x);
    EXPECT_EQ(exp[0].y, act2[0].y);
    EXPECT_EQ(exp[1].x, act2[1].x);
    EXPECT_EQ(exp[1].y, act2[1].y);
    EXPECT_EQ(exp[2].x, act2[2].x);
    EXPECT_EQ(exp[2].y, act2[2].y);
}

TEST_F(ToolHistoryTest, BrushUndoneCheck)
{
    brush->undoStroke();
    brush->undoStroke();
    brush->undoStroke();
    expected = s1;
    actual = brush->getHistory().peekLastUndone();
    const auto& exp = expected->getPoints();
    const auto& act = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act.size(), 3);
    EXPECT_EQ(exp.size(), act.size());
    EXPECT_EQ(exp[0].x, act[0].x);
    EXPECT_EQ(exp[0].y, act[0].y);
    EXPECT_EQ(exp[1].x, act[1].x);
    EXPECT_EQ(exp[1].y, act[1].y);
    EXPECT_EQ(exp[2].x, act[2].x);
    EXPECT_EQ(exp[2].y, act[2].y);
    brush->redoStroke();
    expected = s2;
    actual = brush->getHistory().peekLastUndone();
    const auto& exp2 = expected->getPoints();
    const auto& act2 = actual->getPoints();
    ASSERT_EQ(exp2.size(), 3);
    ASSERT_EQ(act2.size(), 3);
    EXPECT_EQ(exp2.size(), act2.size());
    EXPECT_EQ(exp2[0].x, act2[0].x);
    EXPECT_EQ(exp2[0].y, act2[0].y);
    EXPECT_EQ(exp2[1].x, act2[1].x);
    EXPECT_EQ(exp2[1].y, act2[1].y);
    EXPECT_EQ(exp2[2].x, act2[2].x);
    EXPECT_EQ(exp2[2].y, act2[2].y);
    brush->redoStroke();
    expected = s3;
    actual = brush->getHistory().peekLastUndone();
    const auto& exp3 = expected->getPoints();
    const auto& act3 = actual->getPoints();
    ASSERT_EQ(exp3.size(), 3);
    ASSERT_EQ(act3.size(), 3);
    EXPECT_EQ(exp3.size(), act3.size());
    EXPECT_EQ(exp3[0].x, act3[0].x);
    EXPECT_EQ(exp3[0].y, act3[0].y);
    EXPECT_EQ(exp3[1].x, act3[1].x);
    EXPECT_EQ(exp3[1].y, act3[1].y);
    EXPECT_EQ(exp3[2].x, act3[2].x);
    EXPECT_EQ(exp3[2].y, act3[2].y);
}

TEST_F(ToolHistoryTest, BrushHistoryCheck)
{
    expected = s3;
    actual = brush->getHistory().peek();
    const auto& exp = expected->getPoints();
    const auto& act = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act.size(), 3);
    EXPECT_EQ(exp.size(), act.size());
    EXPECT_EQ(exp[0].x, act[0].x);
    EXPECT_EQ(exp[0].y, act[0].y);
    EXPECT_EQ(exp[1].x, act[1].x);
    EXPECT_EQ(exp[1].y, act[1].y);
    EXPECT_EQ(exp[2].x, act[2].x);
    EXPECT_EQ(exp[2].y, act[2].y);
    brush->undoStroke();
    expected = s2;
    actual = brush->getHistory().peek();
    const auto& exp2 = expected->getPoints();
    const auto& act2 = actual->getPoints();
    ASSERT_EQ(exp2.size(), 3);
    ASSERT_EQ(act2.size(), 3);
    EXPECT_EQ(exp2.size(), act2.size());
    EXPECT_EQ(exp2[0].x, act2[0].x);
    EXPECT_EQ(exp2[0].y, act2[0].y);
    EXPECT_EQ(exp2[1].x, act2[1].x);
    EXPECT_EQ(exp2[1].y, act2[1].y);
    EXPECT_EQ(exp2[2].x, act2[2].x);
    EXPECT_EQ(exp2[2].y, act2[2].y);
    brush->undoStroke();
    expected = s1;
    actual = brush->getHistory().peek();
    const auto& exp3 = expected->getPoints();
    const auto& act3 = actual->getPoints();
    ASSERT_EQ(exp3.size(), 3);
    ASSERT_EQ(act3.size(), 3);
    EXPECT_EQ(exp3.size(), act3.size());
    EXPECT_EQ(exp3[0].x, act3[0].x);
    EXPECT_EQ(exp3[0].y, act3[0].y);
    EXPECT_EQ(exp3[1].x, act3[1].x);
    EXPECT_EQ(exp3[1].y, act3[1].y);
    EXPECT_EQ(exp3[2].x, act3[2].x);
    EXPECT_EQ(exp3[2].y, act3[2].y);
}

/*
TEST_F(ToolHistoryTest, EraserUndo)
{
    eraser->undoStroke();
    expected = s2;
    actual = eraser->getHistory().peek();
    const auto& exp = expected->getPoints();
    const auto& act = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act.size(), 3);
    EXPECT_EQ(exp.size(), act.size());
    EXPECT_EQ(exp[0].x, act[0].x);
    EXPECT_EQ(exp[0].y, act[0].y);
    EXPECT_EQ(exp[1].x, act[1].x);
    EXPECT_EQ(exp[1].y, act[1].y);
    EXPECT_EQ(exp[2].x, act[2].x);
    EXPECT_EQ(exp[2].y, act[2].y);
    actual = eraserStrokeManager->getStrokes().back();
    const auto& act2 = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act2.size(), 3);
    EXPECT_EQ(exp.size(), act2.size());
    EXPECT_EQ(exp[0].x, act2[0].x);
    EXPECT_EQ(exp[0].y, act2[0].y);
    EXPECT_EQ(exp[1].x, act2[1].x);
    EXPECT_EQ(exp[1].y, act2[1].y);
    EXPECT_EQ(exp[2].x, act2[2].x);
    EXPECT_EQ(exp[2].y, act2[2].y);
}

TEST_F(ToolHistoryTest, EraserRedo)
{
    eraser->undoStroke();
    eraser->undoStroke();
    eraser->redoStroke();
    expected = s2;
    actual = eraser->getHistory().peek();
    const auto& exp = expected->getPoints();
    const auto& act = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act.size(), 3);
    EXPECT_EQ(exp.size(), act.size());
    EXPECT_EQ(exp[0].x, act[0].x);
    EXPECT_EQ(exp[0].y, act[0].y);
    EXPECT_EQ(exp[1].x, act[1].x);
    EXPECT_EQ(exp[1].y, act[1].y);
    EXPECT_EQ(exp[2].x, act[2].x);
    EXPECT_EQ(exp[2].y, act[2].y);
    actual = eraserStrokeManager->getStrokes().back();
    const auto& act2 = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act2.size(), 3);
    EXPECT_EQ(exp.size(), act2.size());
    EXPECT_EQ(exp[0].x, act2[0].x);
    EXPECT_EQ(exp[0].y, act2[0].y);
    EXPECT_EQ(exp[1].x, act2[1].x);
    EXPECT_EQ(exp[1].y, act2[1].y);
    EXPECT_EQ(exp[2].x, act2[2].x);
    EXPECT_EQ(exp[2].y, act2[2].y);
}

TEST_F(ToolHistoryTest, DoubleEraserUndo)
{
    eraser->undoStroke();
    eraser->undoStroke();
    expected = s1;
    actual = eraser->getHistory().peek();
    const auto& exp = expected->getPoints();
    const auto& act = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act.size(), 3);
    EXPECT_EQ(exp.size(), act.size());
    EXPECT_EQ(exp[0].x, act[0].x);
    EXPECT_EQ(exp[0].y, act[0].y);
    EXPECT_EQ(exp[1].x, act[1].x);
    EXPECT_EQ(exp[1].y, act[1].y);
    EXPECT_EQ(exp[2].x, act[2].x);
    EXPECT_EQ(exp[2].y, act[2].y);
    actual = eraserStrokeManager->getStrokes().back();
    const auto& act2 = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act2.size(), 3);
    EXPECT_EQ(exp.size(), act2.size());
    EXPECT_EQ(exp[0].x, act2[0].x);
    EXPECT_EQ(exp[0].y, act2[0].y);
    EXPECT_EQ(exp[1].x, act2[1].x);
    EXPECT_EQ(exp[1].y, act2[1].y);
    EXPECT_EQ(exp[2].x, act2[2].x);
    EXPECT_EQ(exp[2].y, act2[2].y);
}

TEST_F(ToolHistoryTest, DoubleEraserRedo)
{
    eraser->undoStroke();
    eraser->undoStroke();
    eraser->undoStroke();
    eraser->redoStroke();
    eraser->redoStroke();
    expected = s2;
    actual = eraser->getHistory().peek();
    const auto& exp = expected->getPoints();
    const auto& act = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act.size(), 3);
    EXPECT_EQ(exp.size(), act.size());
    EXPECT_EQ(exp[0].x, act[0].x);
    EXPECT_EQ(exp[0].y, act[0].y);
    EXPECT_EQ(exp[1].x, act[1].x);
    EXPECT_EQ(exp[1].y, act[1].y);
    EXPECT_EQ(exp[2].x, act[2].x);
    EXPECT_EQ(exp[2].y, act[2].y);
    actual = eraserStrokeManager->getStrokes().back();
    const auto& act2 = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act2.size(), 3);
    EXPECT_EQ(exp.size(), act2.size());
    EXPECT_EQ(exp[0].x, act2[0].x);
    EXPECT_EQ(exp[0].y, act2[0].y);
    EXPECT_EQ(exp[1].x, act2[1].x);
    EXPECT_EQ(exp[1].y, act2[1].y);
    EXPECT_EQ(exp[2].x, act2[2].x);
    EXPECT_EQ(exp[2].y, act2[2].y);
}

TEST_F(ToolHistoryTest, EraserUndoneCheck)
{
    eraser->undoStroke();
    eraser->undoStroke();
    eraser->undoStroke();
    expected = s1;
    actual = eraser->getHistory().peekLastUndone();
    const auto& exp = expected->getPoints();
    const auto& act = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act.size(), 3);
    EXPECT_EQ(exp.size(), act.size());
    EXPECT_EQ(exp[0].x, act[0].x);
    EXPECT_EQ(exp[0].y, act[0].y);
    EXPECT_EQ(exp[1].x, act[1].x);
    EXPECT_EQ(exp[1].y, act[1].y);
    EXPECT_EQ(exp[2].x, act[2].x);
    EXPECT_EQ(exp[2].y, act[2].y);
    eraser->redoStroke();
    expected = s2;
    actual = eraser->getHistory().peekLastUndone();
    const auto& exp2 = expected->getPoints();
    const auto& act2 = actual->getPoints();
    ASSERT_EQ(exp2.size(), 3);
    ASSERT_EQ(act2.size(), 3);
    EXPECT_EQ(exp2.size(), act2.size());
    EXPECT_EQ(exp2[0].x, act2[0].x);
    EXPECT_EQ(exp2[0].y, act2[0].y);
    EXPECT_EQ(exp2[1].x, act2[1].x);
    EXPECT_EQ(exp2[1].y, act2[1].y);
    EXPECT_EQ(exp2[2].x, act2[2].x);
    EXPECT_EQ(exp2[2].y, act2[2].y);
    eraser->redoStroke();
    expected = s3;
    actual = eraser->getHistory().peekLastUndone();
    const auto& exp3 = expected->getPoints();
    const auto& act3 = actual->getPoints();
    ASSERT_EQ(exp3.size(), 3);
    ASSERT_EQ(act3.size(), 3);
    EXPECT_EQ(exp3.size(), act3.size());
    EXPECT_EQ(exp3[0].x, act3[0].x);
    EXPECT_EQ(exp3[0].y, act3[0].y);
    EXPECT_EQ(exp3[1].x, act3[1].x);
    EXPECT_EQ(exp3[1].y, act3[1].y);
    EXPECT_EQ(exp3[2].x, act3[2].x);
    EXPECT_EQ(exp3[2].y, act3[2].y);
}

TEST_F(ToolHistoryTest, EraserHistoryCheck)
{
    expected = s3;
    actual = eraser->getHistory().peek();
    const auto& exp = expected->getPoints();
    const auto& act = actual->getPoints();
    ASSERT_EQ(exp.size(), 3);
    ASSERT_EQ(act.size(), 3);
    EXPECT_EQ(exp.size(), act.size());
    EXPECT_EQ(exp[0].x, act[0].x);
    EXPECT_EQ(exp[0].y, act[0].y);
    EXPECT_EQ(exp[1].x, act[1].x);
    EXPECT_EQ(exp[1].y, act[1].y);
    EXPECT_EQ(exp[2].x, act[2].x);
    EXPECT_EQ(exp[2].y, act[2].y);
    eraser->undoStroke();
    expected = s2;
    actual = eraser->getHistory().peek();
    const auto& exp2 = expected->getPoints();
    const auto& act2 = actual->getPoints();
    ASSERT_EQ(exp2.size(), 3);
    ASSERT_EQ(act2.size(), 3);
    EXPECT_EQ(exp2.size(), act2.size());
    EXPECT_EQ(exp2[0].x, act2[0].x);
    EXPECT_EQ(exp2[0].y, act2[0].y);
    EXPECT_EQ(exp2[1].x, act2[1].x);
    EXPECT_EQ(exp2[1].y, act2[1].y);
    EXPECT_EQ(exp2[2].x, act2[2].x);
    EXPECT_EQ(exp2[2].y, act2[2].y);
    eraser->undoStroke();
    expected = s1;
    actual = eraser->getHistory().peek();
    const auto& exp3 = expected->getPoints();
    const auto& act3 = actual->getPoints();
    ASSERT_EQ(exp3.size(), 3);
    ASSERT_EQ(act3.size(), 3);
    EXPECT_EQ(exp3.size(), act3.size());
    EXPECT_EQ(exp3[0].x, act3[0].x);
    EXPECT_EQ(exp3[0].y, act3[0].y);
    EXPECT_EQ(exp3[1].x, act3[1].x);
    EXPECT_EQ(exp3[1].y, act3[1].y);
    EXPECT_EQ(exp3[2].x, act3[2].x);
    EXPECT_EQ(exp3[2].y, act3[2].y);
}
*/