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
        toolHistory = std::make_shared<ToolHistory>();
        strokeManager = std::make_shared<StrokeManager>();
        brush = std::make_shared<BrushTool>(strokeManager, Color{1.0F, 0.0F, 0.0F, 1.0F}, 5.0F);
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

        toolHistory->push(s1);
        toolHistory->push(s2);
        toolHistory->push(s3);
    }

    void TearDown() override 
    {

    }

    std::shared_ptr<ToolHistory> toolHistory;
    std::shared_ptr<BrushTool> brush;
    std::shared_ptr<StrokeManager> strokeManager;
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
    toolHistory->undo();
    expected = s2;
    actual = toolHistory->peek();
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
    toolHistory->undo();
    toolHistory->undo();
    toolHistory->redo();
    expected = s2;
    actual = toolHistory->peek();
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
    actual = strokeManager->getStrokes().back();
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
    actual = strokeManager->getStrokes().back();
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