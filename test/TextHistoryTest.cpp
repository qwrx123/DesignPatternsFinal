#include <gtest/gtest.h>
#include "TextHistory.h"
#include "TextManager.h"
#include "Text.h"
#include <GLFW/glfw3.h>

class TextHistoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        testHistory = new TextHistory();
        textManager = new TextManager();
        textManager->registerTextTool(std::make_shared<Text>(
        "",
        Bounds(12, 100, 0, 100),
        "default", 12, Color{.r = 0.0F, .g = 0.0F, .b = 0.0F, .a = 1.0F}, true));
        textManager->addText(std::make_shared<Text>("", Bounds{0, 1, 0, 1}, "default", 12, Color{0.0F, 0.0F, 0.0F, 1.0F}, true));
        empty = std::make_shared<Text>("", Bounds{0, 1, 0, 1}, "default", 12, Color{0.0F, 0.0F, 0.0F, 1.0F}, true);
        a = std::make_shared<Text>("a", Bounds{0, 1, 0, 1}, "default", 12, Color{0.0F, 0.0F, 0.0F, 1.0F}, true);
        ab = std::make_shared<Text>("ab", Bounds{0, 1, 0, 1}, "default", 12, Color{0.0F, 0.0F, 0.0F, 1.0F}, true);
        abc = std::make_shared<Text>("abc", Bounds{0, 1, 0, 1}, "default", 12, Color{0.0F, 0.0F, 0.0F, 1.0F}, true);
        testHistory->push(empty);
        testHistory->push(a);
        testHistory->push(ab);
        testHistory->push(abc);
        actual = std::make_shared<Text>();
        expected = std::make_shared<Text>();
    }

    void TearDown() override {
        delete testHistory;
        delete textManager;
    }

    TextHistory* testHistory;
    TextManager* textManager;
    std::shared_ptr<IText> empty;
    std::shared_ptr<IText> a;
    std::shared_ptr<IText> ab;
    std::shared_ptr<IText> abc;
    std::shared_ptr<IText> actual;
    std::shared_ptr<IText> expected;
};

TEST_F(TextHistoryTest, Undo)
{
    actual = testHistory->undo();
    expected = ab;
    EXPECT_EQ(actual->getContent(), expected->getContent());
}

TEST_F(TextHistoryTest, Redo)
{
    testHistory->undo();
    testHistory->undo();
    actual = testHistory->redo();
    expected = ab;
    EXPECT_EQ(actual->getContent(), expected->getContent());
}

TEST_F(TextHistoryTest, AddText)
{
    unsigned int aCode = 'a';
    unsigned int bCode = 'b';
    textManager->onChar(aCode);
    textManager->onChar(bCode);
    actual = textManager->getHistory().peek();
    expected = ab;
    EXPECT_EQ(actual->getContent(), expected->getContent());
}

TEST_F(TextHistoryTest, UndoText)
{
    unsigned int aCode = 'a';
    unsigned int bCode = 'b';
    textManager->onChar(aCode);
    textManager->onChar(bCode);
    textManager->getHistory().undo();
    actual = textManager->getHistory().peek();
    expected = a;
    EXPECT_EQ(actual->getContent(), expected->getContent());
}

TEST_F(TextHistoryTest, RedoText)
{
    unsigned int aCode = 'a';
    unsigned int bCode = 'b';
    textManager->onChar(aCode);
    textManager->onChar(bCode);
    textManager->getHistory().undo();
    textManager->getHistory().redo();
    actual = textManager->getHistory().peek();
    expected = ab;
    EXPECT_EQ(actual->getContent(), expected->getContent());
}
