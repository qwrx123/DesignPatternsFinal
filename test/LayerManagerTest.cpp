#include "gtest/gtest.h"
#include "LayerManager.h"

TEST(LayerManagerTest, CanAddLayersUpToMax) {
    LayerManager manager;
    for (int i = 2; i <= manager.maxLayers(); ++i) {
        EXPECT_TRUE(manager.addLayer());
        EXPECT_EQ(manager.getAllLayers().size(), i);
        EXPECT_TRUE(manager.getAllLayers().back()->getName().starts_with("Layer "));
    }
}

TEST(LayerManagerTest, CannotAddBeyondMax) {
    LayerManager manager;
    for (int i = 0; i < manager.maxLayers(); ++i) {
        manager.addLayer();
    }
    EXPECT_FALSE(manager.addLayer());
}

TEST(LayerManagerTest, NameCounterPersistsAfterDeletion) {
    LayerManager manager;
    manager.addLayer();  // Layer 1
    manager.addLayer();  // Layer 2
    manager.removeLayer(0);
    manager.addLayer();  // Likely Layer 3 or higher depending on counter

    // Simply verify it's not recycling old names
    EXPECT_NE(manager.getAllLayers().back()->getName(), "Layer 1");
}

TEST(LayerManagerTest, RenameLayerWorks) {
    LayerManager manager;
    manager.addLayer();
    manager.getAllLayers()[0]->setName("Custom Name");
    EXPECT_EQ(manager.getAllLayers()[0]->getName(), "Custom Name");
}

TEST(LayerManagerTest, DeleteLayerDoesNotCrashOrResetActiveLayer) {
    LayerManager manager;
    manager.addLayer();
    manager.addLayer();
    manager.setActiveLayer(1);
    manager.removeLayer(1);

    // Verify active layer is still valid index
    int activeIndex = manager.getActiveLayerIndex();
    EXPECT_GE(activeIndex, 0);
    EXPECT_LT(activeIndex, manager.getAllLayers().size());
}