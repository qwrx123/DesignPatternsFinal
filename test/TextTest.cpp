#include <gtest/gtest.h>
#include "Text.h"

TEST(TextTest, DefaultConstructor) {
    Text text;
    Bounds defaultBounds{0.0F, 0.0F, 0.0F, 0.0F};
    Color defaultColor{0.0F, 0.0F, 0.0F, 1.0F};
    EXPECT_EQ(text.getContent(), "");
    EXPECT_EQ(text.getBounds().top, defaultBounds.top);
    EXPECT_EQ(text.getBounds().bottom, defaultBounds.bottom);
    EXPECT_EQ(text.getBounds().left, defaultBounds.left);
    EXPECT_EQ(text.getBounds().right, defaultBounds.right);
    EXPECT_EQ(text.getFontName(), "");
    EXPECT_EQ(text.getFontSize(), 0);
    EXPECT_EQ(text.getColor().r, defaultColor.r);
    EXPECT_EQ(text.getColor().g, defaultColor.g);
    EXPECT_EQ(text.getColor().b, defaultColor.b);
    EXPECT_EQ(text.getColor().a, defaultColor.a);
    EXPECT_FALSE(text.isEditable());
}

TEST(TextTest, ParameterizedConstructor) {
    Bounds bounds{10, 20, 30, 40};
    Color color{1.0F, 0.5F, 0.0F, 1.0F};
    Text text("Hello", bounds, "Arial", 12, color, true);

    EXPECT_EQ(text.getContent(), "Hello");
    EXPECT_EQ(text.getBounds().top, bounds.top);
    EXPECT_EQ(text.getBounds().bottom, bounds.bottom);
    EXPECT_EQ(text.getBounds().left, bounds.left);
    EXPECT_EQ(text.getBounds().right, bounds.right);
    EXPECT_EQ(text.getFontName(), "Arial");
    EXPECT_EQ(text.getFontSize(), 12);
    EXPECT_EQ(text.getColor().r, color.r);
    EXPECT_EQ(text.getColor().g, color.g);
    EXPECT_EQ(text.getColor().b, color.b);
    EXPECT_EQ(text.getColor().a, color.a);
    EXPECT_TRUE(text.isEditable());
}

TEST(TextTest, CopyConstructor) {
    Bounds bounds{10, 20, 30, 40};
    Color color{1.0F, 0.5F, 0.0F, 1.0F};
    Text original("Hello", bounds, "Arial", 12, color, true);
    Text copy(original);

    EXPECT_EQ(copy.getContent(), "Hello");
    EXPECT_EQ(copy.getBounds().top, bounds.top);
    EXPECT_EQ(copy.getBounds().bottom, bounds.bottom);
    EXPECT_EQ(copy.getBounds().left, bounds.left);
    EXPECT_EQ(copy.getBounds().right, bounds.right);
    EXPECT_EQ(copy.getFontName(), "Arial");
    EXPECT_EQ(copy.getFontSize(), 12);
    EXPECT_EQ(copy.getColor().r, color.r);
    EXPECT_EQ(copy.getColor().g, color.g);
    EXPECT_EQ(copy.getColor().b, color.b);
    EXPECT_EQ(copy.getColor().a, color.a);
    EXPECT_TRUE(copy.isEditable());
}

TEST(TextTest, MoveConstructor) {
    Bounds bounds{10, 20, 30, 40};
    Color color{1.0F, 0.5F, 0.0F, 1.0F};
    Text original("Hello", bounds, "Arial", 12, color, true);
    Text moved(std::move(original));

    EXPECT_EQ(moved.getContent(), "Hello");
    EXPECT_EQ(moved.getBounds().top, bounds.top);
    EXPECT_EQ(moved.getBounds().bottom, bounds.bottom);
    EXPECT_EQ(moved.getBounds().left, bounds.left);
    EXPECT_EQ(moved.getBounds().right, bounds.right);
    EXPECT_EQ(moved.getFontName(), "Arial");
    EXPECT_EQ(moved.getFontSize(), 12);
    EXPECT_EQ(moved.getColor().r, color.r);
    EXPECT_EQ(moved.getColor().g, color.g);
    EXPECT_EQ(moved.getColor().b, color.b);
    EXPECT_EQ(moved.getColor().a, color.a);
    EXPECT_TRUE(moved.isEditable());
}

TEST(TextTest, SetContent) {
    Text text;
    text.setContent("New Content");
    EXPECT_EQ(text.getContent(), "New Content");
}

TEST(TextTest, SetBounds) {
    Text text;
    Bounds bounds{5, 15, 10, 20};
    text.setPosition(10, 20);
    EXPECT_EQ(text.getBounds().top, 20);
    EXPECT_EQ(text.getBounds().left, 10);
}

TEST(TextTest, SetFontName) {
    Text text;
    text.setFontName("Times New Roman");
    EXPECT_EQ(text.getFontName(), "Times New Roman");
}

TEST(TextTest, SetFontSize) {
    Text text;
    text.setFontSize(16);
    EXPECT_EQ(text.getFontSize(), 16);
}

TEST(TextTest, SetColor) {
    Text text;
    Color color{0.5F, 0.5F, 0.5F, 1.0F};
    text.setColor(color);
    EXPECT_EQ(text.getColor().r, color.r);
    EXPECT_EQ(text.getColor().g, color.g);
    EXPECT_EQ(text.getColor().b, color.b);
    EXPECT_EQ(text.getColor().a, color.a);
}

TEST(TextTest, SetEditable) {
    Text text;
    text.setEditable(true);
    EXPECT_TRUE(text.isEditable());
    text.setEditable(false);
    EXPECT_FALSE(text.isEditable());
}

TEST(TextTest, GetBoundsContains) {
    Text text("Sample", Bounds{0, 100, 0, 200}, "Arial", 12, Color{0.0F, 0.0F, 0.0F, 1.0F}, true);
    EXPECT_TRUE(text.getBounds().contains(50, 50));
    EXPECT_FALSE(text.getBounds().contains(150, 150));
}

TEST(TextTest, GetBoundsEdgeCases) {
    Text text("Edge Case", Bounds{0, 100, 0, 200}, "Arial", 12, Color{0.0F, 0.0F, 0.0F, 1.0F}, true);
    EXPECT_TRUE(text.getBounds().contains(0, 0));
    EXPECT_TRUE(text.getBounds().contains(200, 100));
    EXPECT_FALSE(text.getBounds().contains(-1, -1));
    EXPECT_FALSE(text.getBounds().contains(101, 201));
}

