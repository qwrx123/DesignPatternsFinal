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

TEST_F(MenuBarIntegrationTest, DropdownOpensAndClosesProperly) {
    auto dropdownButton = getButton(*menuBar, "Select Layer");

    // Initially closed
    EXPECT_FALSE(menuBar->getLayerDropdownButtons().size() > 0);

    // Open dropdown
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Press, dropdownButton->getBounds().left + 1, dropdownButton->getBounds().top + 1);
    menuBar->update();

    EXPECT_TRUE(menuBar->getLayerDropdownButtons().size() > 0);

    // Close dropdown (press again)
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Press, dropdownButton->getBounds().left + 1, dropdownButton->getBounds().top + 1);
    menuBar->update();

    EXPECT_EQ(menuBar->getLayerDropdownButtons().size(), 0);
}

TEST_F(MenuBarIntegrationTest, DropdownShowsCorrectLayerCount) {
    layerManager->addLayer(); // Layer 1
    layerManager->addLayer(); // Layer 2

    auto dropdownButton = getButton(*menuBar, "Select Layer");

    menuBar->onMouseButton(MouseButton::Left, KeyAction::Press, dropdownButton->getBounds().left + 1, dropdownButton->getBounds().top + 1);
    menuBar->update();

    EXPECT_EQ(menuBar->getLayerDropdownButtons().size(), 3);
}

TEST_F(MenuBarIntegrationTest, CanSelectLayerFromDropdown) {
    layerManager->addLayer(); // Layer 1
    layerManager->addLayer(); // Layer 2

    auto dropdownButton = getButton(*menuBar, "Select Layer");

    menuBar->onMouseButton(MouseButton::Left, KeyAction::Press, dropdownButton->getBounds().left + 1, dropdownButton->getBounds().top + 1);
    menuBar->update();

    auto dropdownLayers = menuBar->getLayerDropdownButtons();

    // Click second layer button (index 1)
    auto layerBtn = dropdownLayers[1];
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Press, layerBtn->getBounds().left + 1, layerBtn->getBounds().top + 1);
    menuBar->update();

    EXPECT_EQ(layerManager->getActiveLayerIndex(), 1);
}

TEST_F(MenuBarIntegrationTest, CanDeleteLayerFromDropdown) {
    layerManager->addLayer();
    layerManager->addLayer();

    auto dropdownButton = getButton(*menuBar, "Select Layer");

    menuBar->onMouseButton(MouseButton::Left, KeyAction::Press, dropdownButton->getBounds().left + 1, dropdownButton->getBounds().top + 1);
    menuBar->update();

    auto deleteButtons = menuBar->getLayerDeleteButtons();

    // Delete first layer
    auto deleteBtn = deleteButtons[0];
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Press, deleteBtn->getBounds().left + 1, deleteBtn->getBounds().top + 1);
    menuBar->update();

    EXPECT_EQ(layerManager->getAllLayers().size(), 2);
}

TEST_F(MenuBarIntegrationTest, RenameBufferAcceptsCharacters) {
    layerManager->addLayer();

    auto renameButton = getButton(*menuBar, "Rename Layer");

    // Begin renaming mode
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Press, renameButton->getBounds().left + 1, renameButton->getBounds().top + 1);

    // Type characters: "ABC"
    menuBar->onChar('A');
    menuBar->onChar('B');
    menuBar->onChar('C');

    EXPECT_EQ(menuBar->getRenameBuffer(), "ABC");
}

TEST_F(MenuBarIntegrationTest, RenameBufferHandlesBackspace) {
    layerManager->addLayer();

    auto renameButton = getButton(*menuBar, "Rename Layer");

    menuBar->onMouseButton(MouseButton::Left, KeyAction::Press, renameButton->getBounds().left + 1, renameButton->getBounds().top + 1);
    menuBar->onChar('A');
    menuBar->onChar('B');
    menuBar->onChar('C');

    // Backspace once: should leave "AB"
    menuBar->onKey(GLFW_KEY_BACKSPACE, KeyAction::Press);

    EXPECT_EQ(menuBar->getRenameBuffer(), "AB");
}

TEST_F(MenuBarIntegrationTest, RenameBufferAppliesNameOnEnter) {
    layerManager->addLayer();
    layerManager->setActiveLayer(0);

    auto renameButton = getButton(*menuBar, "Rename Layer");

    menuBar->onMouseButton(MouseButton::Left, KeyAction::Press, renameButton->getBounds().left + 1, renameButton->getBounds().top + 1);
    
    // Simulate clearing the buffer
    menuBar->onKey(GLFW_KEY_BACKSPACE, KeyAction::Press);
    menuBar->onKey(GLFW_KEY_BACKSPACE, KeyAction::Press);
    menuBar->onKey(GLFW_KEY_BACKSPACE, KeyAction::Press);
    menuBar->onKey(GLFW_KEY_BACKSPACE, KeyAction::Press);
    menuBar->onKey(GLFW_KEY_BACKSPACE, KeyAction::Press);
    menuBar->onKey(GLFW_KEY_BACKSPACE, KeyAction::Press);
    menuBar->onKey(GLFW_KEY_BACKSPACE, KeyAction::Press);

    // Now type "New"
    menuBar->onChar('N');
    menuBar->onChar('e');
    menuBar->onChar('w');

    menuBar->onKey(GLFW_KEY_ENTER, KeyAction::Press);

    EXPECT_EQ(layerManager->getAllLayers()[0]->getName(), "New");
}

TEST_F(MenuBarIntegrationTest, TextButtonTogglesGreenWhenActivated) {
    auto textButton = getButton(*menuBar, "Text");

    // Initial color should be white
    EXPECT_EQ(textButton->getColor().r, 1.0f);
    EXPECT_EQ(textButton->getColor().g, 1.0f);
    EXPECT_EQ(textButton->getColor().b, 1.0f);

    // Simulate click to activate
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Press, textButton->getBounds().left + 1, textButton->getBounds().top + 1);
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Release, textButton->getBounds().left + 1, textButton->getBounds().top + 1);

    // Should turn green when activated
    EXPECT_EQ(textButton->getColor().r, 0.0f);
    EXPECT_EQ(textButton->getColor().g, 0.7f);
    EXPECT_EQ(textButton->getColor().b, 0.1f);

    // Simulate click to deactivate
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Press, textButton->getBounds().left + 1, textButton->getBounds().top + 1);
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Release, textButton->getBounds().left + 1, textButton->getBounds().top + 1);

    // Should turn back to white
    EXPECT_EQ(textButton->getColor().r, 1.0f);
    EXPECT_EQ(textButton->getColor().g, 1.0f);
    EXPECT_EQ(textButton->getColor().b, 1.0f);
}

TEST_F(MenuBarIntegrationTest, ColorButtonUpdatesBrushColorAndButtonColor) {
    auto brushButton = getButton(*menuBar, "Brush");
    
    // Simulate selecting brush first
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Press, brushButton->getBounds().left + 1, brushButton->getBounds().top + 1);
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Release, brushButton->getBounds().left + 1, brushButton->getBounds().top + 1);

    // Pick one of the predefined color buttons — let's grab "Red"
    auto colorButton = getButton(*menuBar, "color");
    ASSERT_NE(colorButton, nullptr); // Ensure color button exists

    // Simulate clicking color button
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Press, colorButton->getBounds().left + 1, colorButton->getBounds().top + 1);
    menuBar->onMouseButton(MouseButton::Left, KeyAction::Release, colorButton->getBounds().left + 1, colorButton->getBounds().top + 1);

    // Verify brush color was updated
    Color currentColor = toolManager->getActiveTool()->getColor();
    EXPECT_EQ(currentColor.r, colorButton->getColor().r);
    EXPECT_EQ(currentColor.g, colorButton->getColor().g);
    EXPECT_EQ(currentColor.b, colorButton->getColor().b);
    EXPECT_EQ(currentColor.a, colorButton->getColor().a);

    // Verify brush button color updated as well
    EXPECT_EQ(brushButton->getColor().r, colorButton->getColor().r);
    EXPECT_EQ(brushButton->getColor().g, colorButton->getColor().g);
    EXPECT_EQ(brushButton->getColor().b, colorButton->getColor().b);
    EXPECT_EQ(brushButton->getColor().a, colorButton->getColor().a);
}