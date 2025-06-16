#include <GLFW/glfw3.h>
#include "gtest/gtest.h"
#include "MenuBar.h"
#include "ToolManager.h"
#include "BrushTool.h"
#include "EraserTool.h"
#include "TextManager.h"
#include "LayerManager.h"

// Helper function to find button by label
std::shared_ptr<IButton> getButton(MenuBar& mb, const std::string& label) {
    for (const auto& btn : mb.getButtons()) {
        if (btn->getLabel() == label) return btn;
    }
    return nullptr;
}

class MenuBarIntegrationTest : public ::testing::Test {
protected:
    std::shared_ptr<MenuBar> menuBar;
    std::shared_ptr<ToolManager> toolManager;
    std::shared_ptr<TextManager> textManager;
    std::shared_ptr<LayerManager> layerManager;

    void SetUp() override {
        menuBar = std::make_shared<MenuBar>();
        
        toolManager = std::make_shared<ToolManager>();
        toolManager->registerTool("Brush", std::make_shared<BrushTool>(layerManager, Color{1.0f, 0.0f, 0.0f, 1.0f}, 2.0f));
        toolManager->registerTool("Eraser", std::make_shared<EraserTool>(layerManager, 2.0f));
        toolManager->selectTool("Brush");

        textManager = std::make_shared<TextManager>();
        layerManager = std::make_shared<LayerManager>();

        menuBar->setToolPointer(toolManager);
        menuBar->setTextPointer(textManager);
        menuBar->setLayerPointer(layerManager);
        menuBar->setBounds({.top = 0, .bottom = 100, .left = 0, .right = 500});
        menuBar->setDefaultButtons();
    }
};

TEST_F(MenuBarIntegrationTest, AddLayerButtonColorFlashesOnClick) {
    auto addButton = getButton(*menuBar, "Add Layer");
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Press, addButton->getBounds().left + 1, addButton->getBounds().top + 1);
    EXPECT_EQ(addButton->getColor().r, 0.5f); // Gray while pressed
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Release, addButton->getBounds().left + 1, addButton->getBounds().top + 1);
    EXPECT_EQ(addButton->getColor().r, 1.0f); // White after release
}

TEST_F(MenuBarIntegrationTest, RenameLayerButtonChangesColor) {
    layerManager->addLayer(); // Need one layer

    auto renameButton = getButton(*menuBar, "Rename Layer");

    // Click Rename
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Press, renameButton->getBounds().left + 1, renameButton->getBounds().top + 1);
    EXPECT_EQ(renameButton->getColor().r, 0.5f); // Gray while renaming

    // Finish renaming
    menuBar->onKey(GLFW_KEY_ENTER, KeyAction::Press);
    EXPECT_EQ(renameButton->getColor().r, 1.0f); // Back to white
}

TEST_F(MenuBarIntegrationTest, EraserButtonColorChangesOnSelection) {
    auto eraserButton = getButton(*menuBar, "Eraser");
    auto brushButton  = getButton(*menuBar, "Brush");

    // Click Eraser button
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Press, eraserButton->getBounds().left + 1, eraserButton->getBounds().top + 1);
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Release, eraserButton->getBounds().left + 1, eraserButton->getBounds().top + 1);
    EXPECT_EQ(eraserButton->getColor().r, 0.5f);

    // Click Brush button
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Press, brushButton->getBounds().left + 1, brushButton->getBounds().top + 1);
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Release, brushButton->getBounds().left + 1, brushButton->getBounds().top + 1);
    EXPECT_EQ(eraserButton->getColor().r, 1.0f);
}

TEST_F(MenuBarIntegrationTest, BrushButtonFlashesGrayAndRestoresColor) {
    auto brushButton = getButton(*menuBar, "Brush");

    EXPECT_EQ(brushButton->getColor().r, 1.0f); // Initial brush color = red

    // Press
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Press, brushButton->getBounds().left + 1, brushButton->getBounds().top + 1);
    EXPECT_EQ(brushButton->getColor().r, 0.5f); // Flash gray

    // Release
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Release, brushButton->getBounds().left + 1, brushButton->getBounds().top + 1);
    EXPECT_EQ(brushButton->getColor().r, toolManager->getActiveTool()->getColor().r); // Back to brush color
}