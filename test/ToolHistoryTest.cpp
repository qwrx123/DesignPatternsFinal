// #include <gtest/gtest.h>
// #include "Tools/ToolManager.h"
// #include "drawing/IDrawingTool.h"
// #include "BrushTool.h"
// #include "Stroke.h"
// #include "EraserTool.h"
// #include "StrokeManager.h"
// #include "History.h"

// class ToolHistoryTest : public ::testing::Test {
// protected:
//     void SetUp() override 
//     {
//         history = std::make_shared<History<std::shared_ptr<IStroke>>>();
//         strokeManager = std::make_shared<StrokeManager>();
//         brush = std::make_shared<BrushTool>(strokeManager, Color{1.0F, 0.0F, 0.0F, 1.0F}, 5.0F);
//         eraser = std::make_shared<EraserTool>(strokeManager, 5.0F);
//         s1 = std::make_shared<Stroke>();
//         s2 = std::make_shared<Stroke>();
//         s3 = std::make_shared<Stroke>();
//         expected = std::shared_ptr<IStroke>();
//         actual = std::shared_ptr<IStroke>();

//         p1 = {10, 10};
//         p2 = {20, 20};
//         p3 = {30, 30};
//         p4 = {40, 40};
//         p5 = {50, 50};
//         p6 = {60, 60};
//         p7 = {70, 70};
//         p8 = {80, 80};
//         p9 = {90, 90};

//         brush->beginStroke(p1);
//         brush->addPoint(p2);
//         brush->endStroke(p3);
//         brush->beginStroke(p4);
//         brush->addPoint(p5);
//         brush->endStroke(p6);
//         brush->beginStroke(p7);
//         brush->addPoint(p8);
//         brush->endStroke(p9);

//         s1->addPoint(p1);
//         s1->addPoint(p2);
//         s1->addPoint(p3);

//         s2->addPoint(p4);
//         s2->addPoint(p5);
//         s2->addPoint(p6);

//         s3->addPoint(p7);
//         s3->addPoint(p8);
//         s3->addPoint(p9);

//         history->push(s1);
//         history->push(s2);
//         history->push(s3);
//     }

//     void TearDown() override 
//     {

//     }

//     std::shared_ptr<History<std::shared_ptr<IStroke>>> history;
//     std::shared_ptr<BrushTool> brush;
//     std::shared_ptr<EraserTool> eraser;
//     std::shared_ptr<StrokeManager> strokeManager;
//     std::shared_ptr<IStroke> s1;
//     std::shared_ptr<IStroke> s2;
//     std::shared_ptr<IStroke> s3;
//     Point p1;
//     Point p2;
//     Point p3;
//     Point p4;
//     Point p5;
//     Point p6;
//     Point p7;
//     Point p8;
//     Point p9;
//     std::shared_ptr<IStroke> expected;
//     std::shared_ptr<IStroke> actual;
// };

// TEST_F(ToolHistoryTest, Undo)
// {
//     history->undo();
//     expected = s2;
//     actual = history->peek();
//     const auto& exp = expected->getPoints();
//     const auto& act = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act.size(), 3);
//     EXPECT_EQ(exp.size(), act.size());
//     EXPECT_EQ(exp[0].x, act[0].x);
//     EXPECT_EQ(exp[0].y, act[0].y);
//     EXPECT_EQ(exp[1].x, act[1].x);
//     EXPECT_EQ(exp[1].y, act[1].y);
//     EXPECT_EQ(exp[2].x, act[2].x);
//     EXPECT_EQ(exp[2].y, act[2].y);
// }

// TEST_F(ToolHistoryTest, Redo)
// {
//     history->undo();
//     history->undo();
//     history->redo();
//     expected = s2;
//     actual = history->peek();
//     const auto& exp = expected->getPoints();
//     const auto& act = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act.size(), 3);
//     EXPECT_EQ(exp.size(), act.size());
//     EXPECT_EQ(exp[0].x, act[0].x);
//     EXPECT_EQ(exp[0].y, act[0].y);
//     EXPECT_EQ(exp[1].x, act[1].x);
//     EXPECT_EQ(exp[1].y, act[1].y);
//     EXPECT_EQ(exp[2].x, act[2].x);
//     EXPECT_EQ(exp[2].y, act[2].y);
    
// }

// TEST_F(ToolHistoryTest, BrushUndo)
// {
//     brush->undoStroke();
//     expected = s2;
//     actual = brush->getHistory().peek();
//     const auto& exp = expected->getPoints();
//     const auto& act = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act.size(), 3);
//     EXPECT_EQ(exp.size(), act.size());
//     EXPECT_EQ(exp[0].x, act[0].x);
//     EXPECT_EQ(exp[0].y, act[0].y);
//     EXPECT_EQ(exp[1].x, act[1].x);
//     EXPECT_EQ(exp[1].y, act[1].y);
//     EXPECT_EQ(exp[2].x, act[2].x);
//     EXPECT_EQ(exp[2].y, act[2].y);
//     actual = strokeManager->getStrokes().back();
//     const auto& act2 = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act2.size(), 3);
//     EXPECT_EQ(exp.size(), act2.size());
//     EXPECT_EQ(exp[0].x, act2[0].x);
//     EXPECT_EQ(exp[0].y, act2[0].y);
//     EXPECT_EQ(exp[1].x, act2[1].x);
//     EXPECT_EQ(exp[1].y, act2[1].y);
//     EXPECT_EQ(exp[2].x, act2[2].x);
//     EXPECT_EQ(exp[2].y, act2[2].y);
// }

// TEST_F(ToolHistoryTest, BrushRedo)
// {
//     brush->undoStroke();
//     brush->undoStroke();
//     brush->redoStroke();
//     expected = s2;
//     actual = brush->getHistory().peek();
//     const auto& exp = expected->getPoints();
//     const auto& act = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act.size(), 3);
//     EXPECT_EQ(exp.size(), act.size());
//     EXPECT_EQ(exp[0].x, act[0].x);
//     EXPECT_EQ(exp[0].y, act[0].y);
//     EXPECT_EQ(exp[1].x, act[1].x);
//     EXPECT_EQ(exp[1].y, act[1].y);
//     EXPECT_EQ(exp[2].x, act[2].x);
//     EXPECT_EQ(exp[2].y, act[2].y);
//     actual = strokeManager->getStrokes().back();
//     const auto& act2 = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act2.size(), 3);
//     EXPECT_EQ(exp.size(), act2.size());
//     EXPECT_EQ(exp[0].x, act2[0].x);
//     EXPECT_EQ(exp[0].y, act2[0].y);
//     EXPECT_EQ(exp[1].x, act2[1].x);
//     EXPECT_EQ(exp[1].y, act2[1].y);
//     EXPECT_EQ(exp[2].x, act2[2].x);
//     EXPECT_EQ(exp[2].y, act2[2].y);
// }

// TEST_F(ToolHistoryTest, DoubleBrushUndo)
// {
//     brush->undoStroke();
//     brush->undoStroke();
//     expected = s1;
//     actual = brush->getHistory().peek();
//     const auto& exp = expected->getPoints();
//     const auto& act = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act.size(), 3);
//     EXPECT_EQ(exp.size(), act.size());
//     EXPECT_EQ(exp[0].x, act[0].x);
//     EXPECT_EQ(exp[0].y, act[0].y);
//     EXPECT_EQ(exp[1].x, act[1].x);
//     EXPECT_EQ(exp[1].y, act[1].y);
//     EXPECT_EQ(exp[2].x, act[2].x);
//     EXPECT_EQ(exp[2].y, act[2].y);
//     actual = strokeManager->getStrokes().back();
//     const auto& act2 = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act2.size(), 3);
//     EXPECT_EQ(exp.size(), act2.size());
//     EXPECT_EQ(exp[0].x, act2[0].x);
//     EXPECT_EQ(exp[0].y, act2[0].y);
//     EXPECT_EQ(exp[1].x, act2[1].x);
//     EXPECT_EQ(exp[1].y, act2[1].y);
//     EXPECT_EQ(exp[2].x, act2[2].x);
//     EXPECT_EQ(exp[2].y, act2[2].y);
// }

// TEST_F(ToolHistoryTest, DoubleBrushRedo)
// {
//     brush->undoStroke();
//     brush->undoStroke();
//     brush->undoStroke();
//     brush->redoStroke();
//     brush->redoStroke();
//     expected = s2;
//     actual = brush->getHistory().peek();
//     const auto& exp = expected->getPoints();
//     const auto& act = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act.size(), 3);
//     EXPECT_EQ(exp.size(), act.size());
//     EXPECT_EQ(exp[0].x, act[0].x);
//     EXPECT_EQ(exp[0].y, act[0].y);
//     EXPECT_EQ(exp[1].x, act[1].x);
//     EXPECT_EQ(exp[1].y, act[1].y);
//     EXPECT_EQ(exp[2].x, act[2].x);
//     EXPECT_EQ(exp[2].y, act[2].y);
//     actual = strokeManager->getStrokes().back();
//     const auto& act2 = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act2.size(), 3);
//     EXPECT_EQ(exp.size(), act2.size());
//     EXPECT_EQ(exp[0].x, act2[0].x);
//     EXPECT_EQ(exp[0].y, act2[0].y);
//     EXPECT_EQ(exp[1].x, act2[1].x);
//     EXPECT_EQ(exp[1].y, act2[1].y);
//     EXPECT_EQ(exp[2].x, act2[2].x);
//     EXPECT_EQ(exp[2].y, act2[2].y);
// }

// TEST_F(ToolHistoryTest, BrushUndoneCheck)
// {
//     brush->undoStroke();
//     brush->undoStroke();
//     brush->undoStroke();
//     expected = s1;
//     actual = brush->getHistory().peekLastUndone();
//     const auto& exp = expected->getPoints();
//     const auto& act = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act.size(), 3);
//     EXPECT_EQ(exp.size(), act.size());
//     EXPECT_EQ(exp[0].x, act[0].x);
//     EXPECT_EQ(exp[0].y, act[0].y);
//     EXPECT_EQ(exp[1].x, act[1].x);
//     EXPECT_EQ(exp[1].y, act[1].y);
//     EXPECT_EQ(exp[2].x, act[2].x);
//     EXPECT_EQ(exp[2].y, act[2].y);
//     brush->redoStroke();
//     expected = s2;
//     actual = brush->getHistory().peekLastUndone();
//     const auto& exp2 = expected->getPoints();
//     const auto& act2 = actual->getPoints();
//     ASSERT_EQ(exp2.size(), 3);
//     ASSERT_EQ(act2.size(), 3);
//     EXPECT_EQ(exp2.size(), act2.size());
//     EXPECT_EQ(exp2[0].x, act2[0].x);
//     EXPECT_EQ(exp2[0].y, act2[0].y);
//     EXPECT_EQ(exp2[1].x, act2[1].x);
//     EXPECT_EQ(exp2[1].y, act2[1].y);
//     EXPECT_EQ(exp2[2].x, act2[2].x);
//     EXPECT_EQ(exp2[2].y, act2[2].y);
//     brush->redoStroke();
//     expected = s3;
//     actual = brush->getHistory().peekLastUndone();
//     const auto& exp3 = expected->getPoints();
//     const auto& act3 = actual->getPoints();
//     ASSERT_EQ(exp3.size(), 3);
//     ASSERT_EQ(act3.size(), 3);
//     EXPECT_EQ(exp3.size(), act3.size());
//     EXPECT_EQ(exp3[0].x, act3[0].x);
//     EXPECT_EQ(exp3[0].y, act3[0].y);
//     EXPECT_EQ(exp3[1].x, act3[1].x);
//     EXPECT_EQ(exp3[1].y, act3[1].y);
//     EXPECT_EQ(exp3[2].x, act3[2].x);
//     EXPECT_EQ(exp3[2].y, act3[2].y);
// }

// TEST_F(ToolHistoryTest, BrushHistoryCheck)
// {
//     expected = s3;
//     actual = brush->getHistory().peek();
//     const auto& exp = expected->getPoints();
//     const auto& act = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act.size(), 3);
//     EXPECT_EQ(exp.size(), act.size());
//     EXPECT_EQ(exp[0].x, act[0].x);
//     EXPECT_EQ(exp[0].y, act[0].y);
//     EXPECT_EQ(exp[1].x, act[1].x);
//     EXPECT_EQ(exp[1].y, act[1].y);
//     EXPECT_EQ(exp[2].x, act[2].x);
//     EXPECT_EQ(exp[2].y, act[2].y);
//     brush->undoStroke();
//     expected = s2;
//     actual = brush->getHistory().peek();
//     const auto& exp2 = expected->getPoints();
//     const auto& act2 = actual->getPoints();
//     ASSERT_EQ(exp2.size(), 3);
//     ASSERT_EQ(act2.size(), 3);
//     EXPECT_EQ(exp2.size(), act2.size());
//     EXPECT_EQ(exp2[0].x, act2[0].x);
//     EXPECT_EQ(exp2[0].y, act2[0].y);
//     EXPECT_EQ(exp2[1].x, act2[1].x);
//     EXPECT_EQ(exp2[1].y, act2[1].y);
//     EXPECT_EQ(exp2[2].x, act2[2].x);
//     EXPECT_EQ(exp2[2].y, act2[2].y);
//     brush->undoStroke();
//     expected = s1;
//     actual = brush->getHistory().peek();
//     const auto& exp3 = expected->getPoints();
//     const auto& act3 = actual->getPoints();
//     ASSERT_EQ(exp3.size(), 3);
//     ASSERT_EQ(act3.size(), 3);
//     EXPECT_EQ(exp3.size(), act3.size());
//     EXPECT_EQ(exp3[0].x, act3[0].x);
//     EXPECT_EQ(exp3[0].y, act3[0].y);
//     EXPECT_EQ(exp3[1].x, act3[1].x);
//     EXPECT_EQ(exp3[1].y, act3[1].y);
//     EXPECT_EQ(exp3[2].x, act3[2].x);
//     EXPECT_EQ(exp3[2].y, act3[2].y);
// }

// TEST_F(ToolHistoryTest, UndoAll)
// {
//     brush->undoStroke();
//     brush->undoStroke();
//     brush->undoStroke();
//     actual = brush->getHistory().peek();
//     expected = nullptr;
//     EXPECT_EQ(actual, expected);
// }

// TEST_F(ToolHistoryTest, RedoAll)
// {
//     brush->undoStroke();
//     brush->undoStroke();
//     brush->undoStroke();
//     brush->redoStroke();
//     brush->redoStroke();
//     brush->redoStroke();
//     actual = brush->getHistory().peek();
//     expected = s3;
//     const auto& exp2 = expected->getPoints();
//     const auto& act2 = actual->getPoints();
//     ASSERT_EQ(exp2.size(), 3);
//     ASSERT_EQ(act2.size(), 3);
//     EXPECT_EQ(exp2.size(), act2.size());
//     EXPECT_EQ(exp2[0].x, act2[0].x);
//     EXPECT_EQ(exp2[0].y, act2[0].y);
//     EXPECT_EQ(exp2[1].x, act2[1].x);
//     EXPECT_EQ(exp2[1].y, act2[1].y);
//     EXPECT_EQ(exp2[2].x, act2[2].x);
//     EXPECT_EQ(exp2[2].y, act2[2].y);
//     actual = brush->getHistory().peekLastUndone();
//     expected = nullptr;
//     EXPECT_EQ(actual, expected);
// }

// TEST_F(ToolHistoryTest, UndoOnEmpty)
// {
//     brush->undoStroke();
//     brush->undoStroke();
//     brush->undoStroke();
//     EXPECT_TRUE(brush->getHistory().isEmpty());
//     EXPECT_EQ(brush->getHistory().undoneSize(), 3);
//     brush->undoStroke();
//     EXPECT_TRUE(brush->getHistory().isEmpty());
//     EXPECT_EQ(brush->getHistory().undoneSize(), 3);
// }

// TEST_F(ToolHistoryTest, RedoOnEmpty)
// {
//     brush->undoStroke();
//     EXPECT_EQ(brush->getHistory().size(), 2);
//     brush->redoStroke();
//     EXPECT_TRUE(brush->getHistory().isLastUndoneEmpty());
//     EXPECT_EQ(brush->getHistory().size(), 3);
//     brush->redoStroke();
//     EXPECT_TRUE(brush->getHistory().isLastUndoneEmpty());
//     EXPECT_EQ(brush->getHistory().size(), 3);
// }

// TEST_F(ToolHistoryTest, EraseStroke)
// {
//     EXPECT_EQ(strokeManager->getStrokes().size(), 3);
//     eraser->beginStroke(p1);
//     EXPECT_EQ(eraser->getHistory().size(), 1);
//     EXPECT_EQ(eraser->getHistory().peek().size(), 3);
//     eraser->addPoint(p2);
//     eraser->endStroke(p3);
//     EXPECT_EQ(strokeManager->getStrokes().size(), 2);
//     EXPECT_EQ(eraser->getHistory().size(), 2);
//     EXPECT_EQ(eraser->getHistory().peek().size(), 2);
//     expected = strokeManager->getStrokes().back();
//     actual = eraser->getHistory().peek().back();
//     const auto& exp = expected->getPoints();
//     const auto& act = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act.size(), 3);
//     EXPECT_EQ(exp.size(), act.size());
//     EXPECT_EQ(exp[0].x, act[0].x);
//     EXPECT_EQ(exp[0].y, act[0].y);
//     EXPECT_EQ(exp[1].x, act[1].x);
//     EXPECT_EQ(exp[1].y, act[1].y);
//     EXPECT_EQ(exp[2].x, act[2].x);
//     EXPECT_EQ(exp[2].y, act[2].y);
//     expected = strokeManager->getStrokes().front();
//     actual = eraser->getHistory().peek().front();
//     const auto& exp2 = expected->getPoints();
//     const auto& act2 = actual->getPoints();
//     ASSERT_EQ(exp2.size(), 3);
//     ASSERT_EQ(act2.size(), 3);
//     EXPECT_EQ(exp2.size(), act2.size());
//     EXPECT_EQ(exp2[0].x, act2[0].x);
//     EXPECT_EQ(exp2[0].y, act2[0].y);
//     EXPECT_EQ(exp2[1].x, act2[1].x);
//     EXPECT_EQ(exp2[1].y, act2[1].y);
//     EXPECT_EQ(exp2[2].x, act2[2].x);
//     EXPECT_EQ(exp2[2].y, act2[2].y);
// }

// TEST_F(ToolHistoryTest, UndoErase)
// {
//     eraser->beginStroke(p1);
//     eraser->addPoint(p2);
//     eraser->endStroke(p3);
//     eraser->undoStroke();
//     EXPECT_EQ(strokeManager->getStrokes().size(), 3);
//     EXPECT_EQ(eraser->getHistory().size(), 1);
//     EXPECT_EQ(eraser->getHistory().peek().size(), 3);
//     EXPECT_EQ(eraser->getHistory().undoneSize(), 1);
//     expected = strokeManager->getStrokes().back();
//     actual = eraser->getHistory().peek().back();
//     const auto& exp = expected->getPoints();
//     const auto& act = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act.size(), 3);
//     EXPECT_EQ(exp.size(), act.size());
//     EXPECT_EQ(exp[0].x, act[0].x);
//     EXPECT_EQ(exp[0].y, act[0].y);
//     EXPECT_EQ(exp[1].x, act[1].x);
//     EXPECT_EQ(exp[1].y, act[1].y);
//     EXPECT_EQ(exp[2].x, act[2].x);
//     EXPECT_EQ(exp[2].y, act[2].y);
//     expected = strokeManager->getStrokes().front();
//     actual = eraser->getHistory().peek().front();
//     const auto& exp2 = expected->getPoints();
//     const auto& act2 = actual->getPoints();
//     ASSERT_EQ(exp2.size(), 3);
//     ASSERT_EQ(act2.size(), 3);
//     EXPECT_EQ(exp2.size(), act2.size());
//     EXPECT_EQ(exp2[0].x, act2[0].x);
//     EXPECT_EQ(exp2[0].y, act2[0].y);
//     EXPECT_EQ(exp2[1].x, act2[1].x);
//     EXPECT_EQ(exp2[1].y, act2[1].y);
//     EXPECT_EQ(exp2[2].x, act2[2].x);
//     EXPECT_EQ(exp2[2].y, act2[2].y);
// }

// TEST_F(ToolHistoryTest, RedoErase)
// {
//     eraser->beginStroke(p1);
//     eraser->addPoint(p2);
//     eraser->endStroke(p3);
//     eraser->undoStroke();
//     EXPECT_EQ(eraser->getHistory().undoneSize(), 1);
//     eraser->redoStroke();
//     EXPECT_EQ(strokeManager->getStrokes().size(), 2);
//     EXPECT_EQ(eraser->getHistory().size(), 2);
//     EXPECT_EQ(eraser->getHistory().peek().size(), 2);
//     EXPECT_EQ(eraser->getHistory().undoneSize(), 0);
//     expected = strokeManager->getStrokes().back();
//     actual = eraser->getHistory().peek().back();
//     const auto& exp = expected->getPoints();
//     const auto& act = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act.size(), 3);
//     EXPECT_EQ(exp.size(), act.size());
//     EXPECT_EQ(exp[0].x, act[0].x);
//     EXPECT_EQ(exp[0].y, act[0].y);
//     EXPECT_EQ(exp[1].x, act[1].x);
//     EXPECT_EQ(exp[1].y, act[1].y);
//     EXPECT_EQ(exp[2].x, act[2].x);
//     EXPECT_EQ(exp[2].y, act[2].y);
//     expected = strokeManager->getStrokes().front();
//     actual = eraser->getHistory().peek().front();
//     const auto& exp2 = expected->getPoints();
//     const auto& act2 = actual->getPoints();
//     ASSERT_EQ(exp2.size(), 3);
//     ASSERT_EQ(act2.size(), 3);
//     EXPECT_EQ(exp2.size(), act2.size());
//     EXPECT_EQ(exp2[0].x, act2[0].x);
//     EXPECT_EQ(exp2[0].y, act2[0].y);
//     EXPECT_EQ(exp2[1].x, act2[1].x);
//     EXPECT_EQ(exp2[1].y, act2[1].y);
//     EXPECT_EQ(exp2[2].x, act2[2].x);
//     EXPECT_EQ(exp2[2].y, act2[2].y);
// }

// TEST_F(ToolHistoryTest, FirstUndoEraseThenUndoBrush)
// {
//     eraser->beginStroke(p1);
//     eraser->addPoint(p2);
//     eraser->endStroke(p3);
//     eraser->undoStroke();
//     brush->undoStroke();
//     EXPECT_EQ(strokeManager->getStrokes().size(), 2);
//     EXPECT_EQ(eraser->getHistory().size(), 1);
//     EXPECT_EQ(eraser->getHistory().peek().size(), 3);
//     EXPECT_EQ(eraser->getHistory().undoneSize(), 1);
//     EXPECT_EQ(brush->getHistory().size(), 2);
//     EXPECT_EQ(brush->getHistory().undoneSize(), 1);
//     expected = s2;
//     actual = strokeManager->getStrokes().back();
//     const auto& exp = expected->getPoints();
//     const auto& act = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act.size(), 3);
//     EXPECT_EQ(exp.size(), act.size());
//     EXPECT_EQ(exp[0].x, act[0].x);
//     EXPECT_EQ(exp[0].y, act[0].y);
//     EXPECT_EQ(exp[1].x, act[1].x);
//     EXPECT_EQ(exp[1].y, act[1].y);
//     EXPECT_EQ(exp[2].x, act[2].x);
//     EXPECT_EQ(exp[2].y, act[2].y);
//     expected = s1;
//     actual = strokeManager->getStrokes().front();
//     const auto& exp2 = expected->getPoints();
//     const auto& act2 = actual->getPoints();
//     ASSERT_EQ(exp2.size(), 3);
//     ASSERT_EQ(act2.size(), 3);
//     EXPECT_EQ(exp2.size(), act2.size());
//     EXPECT_EQ(exp2[0].x, act2[0].x);
//     EXPECT_EQ(exp2[0].y, act2[0].y);
//     EXPECT_EQ(exp2[1].x, act2[1].x);
//     EXPECT_EQ(exp2[1].y, act2[1].y);
//     EXPECT_EQ(exp2[2].x, act2[2].x);
//     EXPECT_EQ(exp2[2].y, act2[2].y);
// }

// TEST_F(ToolHistoryTest, FirstRedoEraseThenUndoBrush)
// {
//     eraser->beginStroke(p1);
//     eraser->addPoint(p2);
//     eraser->endStroke(p3);
//     eraser->undoStroke();
//     eraser->redoStroke();
//     brush->undoStroke();
//     EXPECT_EQ(strokeManager->getStrokes().size(), 1);
//     EXPECT_EQ(eraser->getHistory().size(), 2);
//     EXPECT_EQ(eraser->getHistory().peek().size(), 2);
//     EXPECT_EQ(eraser->getHistory().undoneSize(), 0);
//     EXPECT_EQ(brush->getHistory().size(), 2);
//     EXPECT_EQ(brush->getHistory().undoneSize(), 1);
//     expected = s2;
//     actual = strokeManager->getStrokes().back();
//     const auto& exp = expected->getPoints();
//     const auto& act = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act.size(), 3);
//     EXPECT_EQ(exp.size(), act.size());
//     EXPECT_EQ(exp[0].x, act[0].x);
//     EXPECT_EQ(exp[0].y, act[0].y);
//     EXPECT_EQ(exp[1].x, act[1].x);
//     EXPECT_EQ(exp[1].y, act[1].y);
//     EXPECT_EQ(exp[2].x, act[2].x);
//     EXPECT_EQ(exp[2].y, act[2].y);
//     expected = s2;
//     actual = strokeManager->getStrokes().front();
//     const auto& exp2 = expected->getPoints();
//     const auto& act2 = actual->getPoints();
//     ASSERT_EQ(exp2.size(), 3);
//     ASSERT_EQ(act2.size(), 3);
//     EXPECT_EQ(exp2.size(), act2.size());
//     EXPECT_EQ(exp2[0].x, act2[0].x);
//     EXPECT_EQ(exp2[0].y, act2[0].y);
//     EXPECT_EQ(exp2[1].x, act2[1].x);
//     EXPECT_EQ(exp2[1].y, act2[1].y);
//     EXPECT_EQ(exp2[2].x, act2[2].x);
//     EXPECT_EQ(exp2[2].y, act2[2].y);
// }

// TEST_F(ToolHistoryTest, FirstUndoEraseThenRedoBrush)
// {
//     eraser->beginStroke(p1);
//     eraser->addPoint(p2);
//     eraser->endStroke(p3);
//     eraser->undoStroke();
//     brush->undoStroke();
//     brush->redoStroke();
//     EXPECT_EQ(strokeManager->getStrokes().size(), 3);
//     EXPECT_EQ(eraser->getHistory().size(), 1);
//     EXPECT_EQ(eraser->getHistory().peek().size(), 3);
//     EXPECT_EQ(eraser->getHistory().undoneSize(), 1);
//     EXPECT_EQ(brush->getHistory().size(), 3);
//     EXPECT_EQ(brush->getHistory().undoneSize(), 0);
//     expected = s3;
//     actual = strokeManager->getStrokes().back();
//     const auto& exp = expected->getPoints();
//     const auto& act = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act.size(), 3);
//     EXPECT_EQ(exp.size(), act.size());
//     EXPECT_EQ(exp[0].x, act[0].x);
//     EXPECT_EQ(exp[0].y, act[0].y);
//     EXPECT_EQ(exp[1].x, act[1].x);
//     EXPECT_EQ(exp[1].y, act[1].y);
//     EXPECT_EQ(exp[2].x, act[2].x);
//     EXPECT_EQ(exp[2].y, act[2].y);
//     expected = s1;
//     actual = strokeManager->getStrokes().front();
//     const auto& exp2 = expected->getPoints();
//     const auto& act2 = actual->getPoints();
//     ASSERT_EQ(exp2.size(), 3);
//     ASSERT_EQ(act2.size(), 3);
//     EXPECT_EQ(exp2.size(), act2.size());
//     EXPECT_EQ(exp2[0].x, act2[0].x);
//     EXPECT_EQ(exp2[0].y, act2[0].y);
//     EXPECT_EQ(exp2[1].x, act2[1].x);
//     EXPECT_EQ(exp2[1].y, act2[1].y);
//     EXPECT_EQ(exp2[2].x, act2[2].x);
//     EXPECT_EQ(exp2[2].y, act2[2].y);  
// }

// TEST_F(ToolHistoryTest, FirstRedoEraseThenRedoBrush)
// {
//     eraser->beginStroke(p1);
//     eraser->addPoint(p2);
//     eraser->endStroke(p3);
//     eraser->undoStroke();
//     eraser->redoStroke();
//     brush->undoStroke();
//     brush->redoStroke();
//     EXPECT_EQ(strokeManager->getStrokes().size(), 2);
//     EXPECT_EQ(eraser->getHistory().size(), 2);
//     EXPECT_EQ(eraser->getHistory().peek().size(), 2);
//     EXPECT_EQ(eraser->getHistory().undoneSize(), 0);
//     EXPECT_EQ(brush->getHistory().size(), 3);
//     EXPECT_EQ(brush->getHistory().undoneSize(), 0);
//     expected = s3;
//     actual = strokeManager->getStrokes().back();
//     const auto& exp = expected->getPoints();
//     const auto& act = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act.size(), 3);
//     EXPECT_EQ(exp.size(), act.size());
//     EXPECT_EQ(exp[0].x, act[0].x);
//     EXPECT_EQ(exp[0].y, act[0].y);
//     EXPECT_EQ(exp[1].x, act[1].x);
//     EXPECT_EQ(exp[1].y, act[1].y);
//     EXPECT_EQ(exp[2].x, act[2].x);
//     EXPECT_EQ(exp[2].y, act[2].y);
//     expected = s2;
//     actual = strokeManager->getStrokes().front();
//     const auto& exp2 = expected->getPoints();
//     const auto& act2 = actual->getPoints();
//     ASSERT_EQ(exp2.size(), 3);
//     ASSERT_EQ(act2.size(), 3);
//     EXPECT_EQ(exp2.size(), act2.size());
//     EXPECT_EQ(exp2[0].x, act2[0].x);
//     EXPECT_EQ(exp2[0].y, act2[0].y);
//     EXPECT_EQ(exp2[1].x, act2[1].x);
//     EXPECT_EQ(exp2[1].y, act2[1].y);
//     EXPECT_EQ(exp2[2].x, act2[2].x);
//     EXPECT_EQ(exp2[2].y, act2[2].y);
// }

// TEST_F(ToolHistoryTest, FirstUndoBrushThenUndoErase)
// {
//     eraser->beginStroke(p1);
//     eraser->addPoint(p2);
//     eraser->endStroke(p3);
//     brush->undoStroke();
//     eraser->undoStroke();
//     EXPECT_EQ(strokeManager->getStrokes().size(), 3);
//     EXPECT_EQ(eraser->getHistory().size(), 1);
//     EXPECT_EQ(eraser->getHistory().peek().size(), 3);
//     EXPECT_EQ(eraser->getHistory().undoneSize(), 1);
//     EXPECT_EQ(brush->getHistory().size(), 2);
//     EXPECT_EQ(brush->getHistory().undoneSize(), 1);
//     expected = s3;
//     actual = strokeManager->getStrokes().back();
//     const auto& exp = expected->getPoints();
//     const auto& act = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act.size(), 3);
//     EXPECT_EQ(exp.size(), act.size());
//     EXPECT_EQ(exp[0].x, act[0].x);
//     EXPECT_EQ(exp[0].y, act[0].y);
//     EXPECT_EQ(exp[1].x, act[1].x);
//     EXPECT_EQ(exp[1].y, act[1].y);
//     EXPECT_EQ(exp[2].x, act[2].x);
//     EXPECT_EQ(exp[2].y, act[2].y);
//     expected = s1;
//     actual = strokeManager->getStrokes().front();
//     const auto& exp2 = expected->getPoints();
//     const auto& act2 = actual->getPoints();
//     ASSERT_EQ(exp2.size(), 3);
//     ASSERT_EQ(act2.size(), 3);
//     EXPECT_EQ(exp2.size(), act2.size());
//     EXPECT_EQ(exp2[0].x, act2[0].x);
//     EXPECT_EQ(exp2[0].y, act2[0].y);
//     EXPECT_EQ(exp2[1].x, act2[1].x);
//     EXPECT_EQ(exp2[1].y, act2[1].y);
//     EXPECT_EQ(exp2[2].x, act2[2].x);
//     EXPECT_EQ(exp2[2].y, act2[2].y);
// }

// TEST_F(ToolHistoryTest, FirstUndoBrushThenRedoErase)
// {
//     eraser->beginStroke(p1);
//     eraser->addPoint(p2);
//     eraser->endStroke(p3);
//     brush->undoStroke();
//     eraser->undoStroke();
//     eraser->redoStroke();
//     EXPECT_EQ(strokeManager->getStrokes().size(), 2);
//     EXPECT_EQ(eraser->getHistory().size(), 2);
//     EXPECT_EQ(eraser->getHistory().peek().size(), 2);
//     EXPECT_EQ(eraser->getHistory().undoneSize(), 0);
//     EXPECT_EQ(brush->getHistory().size(), 2);
//     EXPECT_EQ(brush->getHistory().undoneSize(), 1);
//     expected = s3;
//     actual = strokeManager->getStrokes().back();
//     const auto& exp = expected->getPoints();
//     const auto& act = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act.size(), 3);
//     EXPECT_EQ(exp.size(), act.size());
//     EXPECT_EQ(exp[0].x, act[0].x);
//     EXPECT_EQ(exp[0].y, act[0].y);
//     EXPECT_EQ(exp[1].x, act[1].x);
//     EXPECT_EQ(exp[1].y, act[1].y);
//     EXPECT_EQ(exp[2].x, act[2].x);
//     EXPECT_EQ(exp[2].y, act[2].y);
//     expected = s2;
//     actual = strokeManager->getStrokes().front();
//     const auto& exp2 = expected->getPoints();
//     const auto& act2 = actual->getPoints();
//     ASSERT_EQ(exp2.size(), 3);
//     ASSERT_EQ(act2.size(), 3);
//     EXPECT_EQ(exp2.size(), act2.size());
//     EXPECT_EQ(exp2[0].x, act2[0].x);
//     EXPECT_EQ(exp2[0].y, act2[0].y);
//     EXPECT_EQ(exp2[1].x, act2[1].x);
//     EXPECT_EQ(exp2[1].y, act2[1].y);
//     EXPECT_EQ(exp2[2].x, act2[2].x);
//     EXPECT_EQ(exp2[2].y, act2[2].y);
// }

// TEST_F(ToolHistoryTest, FirstRedoBrushThenUndoErase)
// {
//     eraser->beginStroke(p1);
//     eraser->addPoint(p2);
//     eraser->endStroke(p3);
//     brush->undoStroke();
//     brush->redoStroke();
//     eraser->undoStroke();
//     EXPECT_EQ(strokeManager->getStrokes().size(), 3);
//     EXPECT_EQ(eraser->getHistory().size(), 1);
//     EXPECT_EQ(eraser->getHistory().peek().size(), 3);
//     EXPECT_EQ(eraser->getHistory().undoneSize(), 1);
//     EXPECT_EQ(brush->getHistory().size(), 3);
//     EXPECT_EQ(brush->getHistory().undoneSize(), 0);
//     expected = s3;
//     actual = strokeManager->getStrokes().back();
//     const auto& exp = expected->getPoints();
//     const auto& act = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act.size(), 3);
//     EXPECT_EQ(exp.size(), act.size());
//     EXPECT_EQ(exp[0].x, act[0].x);
//     EXPECT_EQ(exp[0].y, act[0].y);
//     EXPECT_EQ(exp[1].x, act[1].x);
//     EXPECT_EQ(exp[1].y, act[1].y);
//     EXPECT_EQ(exp[2].x, act[2].x);
//     EXPECT_EQ(exp[2].y, act[2].y);
//     expected = s1;
//     actual = strokeManager->getStrokes().front();
//     const auto& exp2 = expected->getPoints();
//     const auto& act2 = actual->getPoints();
//     ASSERT_EQ(exp2.size(), 3);
//     ASSERT_EQ(act2.size(), 3);
//     EXPECT_EQ(exp2.size(), act2.size());
//     EXPECT_EQ(exp2[0].x, act2[0].x);
//     EXPECT_EQ(exp2[0].y, act2[0].y);
//     EXPECT_EQ(exp2[1].x, act2[1].x);
//     EXPECT_EQ(exp2[1].y, act2[1].y);
//     EXPECT_EQ(exp2[2].x, act2[2].x);
//     EXPECT_EQ(exp2[2].y, act2[2].y);
// }

// TEST_F(ToolHistoryTest, FirstRedoBrushThenRedoErase)
// {
//     eraser->beginStroke(p1);
//     eraser->addPoint(p2);
//     eraser->endStroke(p3);
//     brush->undoStroke();
//     brush->redoStroke();
//     eraser->undoStroke();
//     eraser->redoStroke();
//     EXPECT_EQ(strokeManager->getStrokes().size(), 2);
//     EXPECT_EQ(eraser->getHistory().size(), 2);
//     EXPECT_EQ(eraser->getHistory().peek().size(), 2);
//     EXPECT_EQ(eraser->getHistory().undoneSize(), 0);
//     EXPECT_EQ(brush->getHistory().size(), 3);
//     EXPECT_EQ(brush->getHistory().undoneSize(), 0);
//     expected = s3;
//     actual = strokeManager->getStrokes().back();
//     const auto& exp = expected->getPoints();
//     const auto& act = actual->getPoints();
//     ASSERT_EQ(exp.size(), 3);
//     ASSERT_EQ(act.size(), 3);
//     EXPECT_EQ(exp.size(), act.size());
//     EXPECT_EQ(exp[0].x, act[0].x);
//     EXPECT_EQ(exp[0].y, act[0].y);
//     EXPECT_EQ(exp[1].x, act[1].x);
//     EXPECT_EQ(exp[1].y, act[1].y);
//     EXPECT_EQ(exp[2].x, act[2].x);
//     EXPECT_EQ(exp[2].y, act[2].y);
//     expected = s2;
//     actual = strokeManager->getStrokes().front();
//     const auto& exp2 = expected->getPoints();
//     const auto& act2 = actual->getPoints();
//     ASSERT_EQ(exp2.size(), 3);
//     ASSERT_EQ(act2.size(), 3);
//     EXPECT_EQ(exp2.size(), act2.size());
//     EXPECT_EQ(exp2[0].x, act2[0].x);
//     EXPECT_EQ(exp2[0].y, act2[0].y);
//     EXPECT_EQ(exp2[1].x, act2[1].x);
//     EXPECT_EQ(exp2[1].y, act2[1].y);
//     EXPECT_EQ(exp2[2].x, act2[2].x);
//     EXPECT_EQ(exp2[2].y, act2[2].y);
// }

// /*
//     TEST: 
//     redid the eraser and undid the lines, stoped halfway, 
//     redid eraser tried to undo more lines
// */