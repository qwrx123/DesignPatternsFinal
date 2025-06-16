#include <gtest/gtest.h>
#include "StrokeManager.h"
#include "Stroke.h"
#include "LayerManager.h"

TEST(StrokeManagerTest, CanAddStroke) {
    auto layerManager = std::make_shared<LayerManager>();
    StrokeManager manager(layerManager);

    auto stroke = std::make_shared<Stroke>();
    manager.addStroke(stroke);

    const auto& strokes = manager.getStrokes();
    ASSERT_EQ(strokes.size(), 1);
    EXPECT_EQ(strokes[0], stroke);
}

TEST(StrokeManagerTest, CanAddMultipleStrokes) {
    auto layerManager = std::make_shared<LayerManager>();
    StrokeManager manager(layerManager);

    auto s1 = std::make_shared<Stroke>();
    auto s2 = std::make_shared<Stroke>();

    manager.addStroke(s1);
    manager.addStroke(s2);

    const auto& strokes = manager.getStrokes();
    ASSERT_EQ(strokes.size(), 2);
    EXPECT_EQ(strokes[0], s1);
    EXPECT_EQ(strokes[1], s2);
}

TEST(StrokeManagerTest, CanClearStrokes) {
    auto layerManager = std::make_shared<LayerManager>();
    StrokeManager manager(layerManager);

    manager.addStroke(std::make_shared<Stroke>());
    manager.addStroke(std::make_shared<Stroke>());

    manager.clear();

    EXPECT_TRUE(manager.getStrokes().empty());
}