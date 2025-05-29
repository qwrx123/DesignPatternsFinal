#include <gtest/gtest.h>
#include "TextManager.h"
#include "Text.h"

TEST(TextManagerTest, CanAddText) {
    TextManager manager;
    auto text = std::make_shared<Text>("Hello, World!", Bounds{0, 0, 100, 50}, "Arial", 12, Color{0.0F, 0.0F, 0.0F, 1.0F}, true);

    manager.addText(text);

    const auto& texts = manager.getTexts();
    ASSERT_EQ(texts.size(), 1);
    EXPECT_EQ(texts[0], text);
}

TEST(TextManagerTest, CanAddMultipleTexts) {
    TextManager manager;
    auto t1 = std::make_shared<Text>("First Text", Bounds{0, 0, 100, 50}, "Arial", 12, Color{0.0F, 0.0F, 0.0F, 1.0F}, true);
    auto t2 = std::make_shared<Text>("Second Text", Bounds{0, 0, 100, 50}, "Arial", 12, Color{0.0F, 0.0F, 0.0F, 1.0F}, true);

    manager.addText(t1);
    manager.addText(t2);

    const auto& texts = manager.getTexts();
    ASSERT_EQ(texts.size(), 2);
    EXPECT_EQ(texts[0], t1);
    EXPECT_EQ(texts[1], t2);
}

TEST(TextManagerTest, CanRemoveText) {
    TextManager manager;
    auto text = std::make_shared<Text>("Text to Remove", Bounds{0, 0, 100, 50}, "Arial", 12, Color{0.0F, 0.0F, 0.0F, 1.0F}, true);

    manager.addText(text);
    manager.removeText(text);

    const auto& texts = manager.getTexts();
    EXPECT_TRUE(texts.empty());
}

TEST(TextManagerTest, CanClearAllTexts) {
    TextManager manager;
    manager.addText(std::make_shared<Text>("Text 1", Bounds{0, 0, 100, 50}, "Arial", 12, Color{0.0F, 0.0F, 0.0F, 1.0F}, true));
    manager.addText(std::make_shared<Text>("Text 2", Bounds{0, 0, 100, 50}, "Arial", 12, Color{0.0F, 0.0F, 0.0F, 1.0F}, true));

    manager.clearAll();

    EXPECT_TRUE(manager.getTexts().empty());
}

TEST(TextManagerTest, CanGetTextAtPosition) {
    TextManager manager;
    auto text1 = std::make_shared<Text>("Text at (10, 30)", Bounds{10, 20, 30, 50}, "Arial", 12, Color{0.0F, 0.0F, 0.0F, 1.0F}, true);
    auto text2 = std::make_shared<Text>("Text at (30, 10)", Bounds{30, 40, 10, 50}, "Arial", 12, Color{0.0F, 0.0F, 0.0F, 1.0F}, true);

    manager.addText(text1);
    manager.addText(text2);

    auto foundText = manager.getTextAt(45, 15);
    EXPECT_EQ(foundText, text1);

    foundText = manager.getTextAt(25, 35);
    EXPECT_EQ(foundText, text2);

    foundText = manager.getTextAt(60, 50);
    EXPECT_EQ(foundText, nullptr);
}

TEST(TextManagerTest, CanRegisterTextTool) {
    TextManager manager;
    auto textTool = std::make_shared<Text>("Text Tool", Bounds{0, 0, 50, 100}, "Arial", 12, Color{0.0F, 0.0F, 0.0F, 1.0F}, true);

    manager.registerTextTool(textTool);
    manager.setTextToolActive();
    EXPECT_TRUE(manager.isTextToolActive());

    const auto& texts = manager.getTexts();
    ASSERT_EQ(texts.size(), 1);
    EXPECT_EQ(texts[0], textTool);
}

TEST(TextManagerTest, CanSetTextToolActiveAndInactive) {
    TextManager manager;

    EXPECT_FALSE(manager.isTextToolActive());
    manager.setTextToolActive();
    EXPECT_TRUE(manager.isTextToolActive());

    manager.setTextToolInactive();
    EXPECT_FALSE(manager.isTextToolActive());
}