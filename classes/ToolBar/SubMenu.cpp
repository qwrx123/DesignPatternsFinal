#include "SubMenu.h"

SubMenu::SubMenu() : label(""), bounds(Bounds(0, 0, 0, 0)), selectedIndex(0) {}
SubMenu::~SubMenu() = default;
SubMenu::SubMenu(const SubMenu& other)
    : label(other.label), bounds(other.bounds), buttons(other.buttons), selectedIndex(other.selectedIndex) {}
SubMenu& SubMenu::operator=(const SubMenu& other)
{
    if (this != &other)
    {
        label			= other.label;
        bounds			= other.bounds;
        buttons			= other.buttons;
        selectedIndex	= other.selectedIndex;
    }
    return *this;
}

SubMenu::SubMenu(SubMenu&& other) noexcept
    : label(std::move(other.label)), bounds(std::move(other.bounds)), buttons(std::move(other.buttons)),
      selectedIndex(other.selectedIndex)
{
    other.selectedIndex = 0;
}
SubMenu& SubMenu::operator=(SubMenu&& other) noexcept
{
    if (this != &other)
    {
        label			= std::move(other.label);
        bounds			= std::move(other.bounds);
        buttons			= std::move(other.buttons);
        selectedIndex	= other.selectedIndex;
        other.selectedIndex = 0;
    }
    return *this;
}
std::string SubMenu::getLabel() const
{
    return label;
}
void SubMenu::setLabel(const std::string& label)
{
    this->label = label;
}
Bounds SubMenu::getBounds() const
{
    return bounds;
}
void SubMenu::setBounds(const Bounds& bounds)
{
    this->bounds = bounds;
}
bool SubMenu::isOpen() const
{
    return isOpenState;
}
bool SubMenu::isClosed() const
{
    return !isOpenState;
}
void SubMenu::open()
{
    isOpenState = true;
}
void SubMenu::close()
{
    isOpenState = false;
}
void SubMenu::addButton(std::shared_ptr<IButton> button)
{
    buttons.push_back(std::move(button));
}
void SubMenu::clearButtons()
{
    buttons.clear();
}
const std::vector<std::shared_ptr<IButton>>& SubMenu::getButtons() const
{
    return buttons;
}
int SubMenu::getSelectedIndex() const
{
    return selectedIndex;
}
void SubMenu::setSelectedIndex(int index)
{
    if (index >= 0 && index < static_cast<int>(buttons.size()))
    {
        selectedIndex = index;
    }
}
std::shared_ptr<IButton> SubMenu::getSelectedItem() const
{
    if (selectedIndex >= 0 && selectedIndex < static_cast<int>(buttons.size()))
    {
        return buttons[selectedIndex];
    }
    return nullptr;
}
bool SubMenu::showSelectedLabelWhenClosed() const
{
    return false; // Not applicable since SubMenu is always open
}
void SubMenu::setShowSelectedLabelWhenClosed(bool show)
{
    // No action needed, always open
}
std::vector<std::shared_ptr<IButton>> SubMenu::cloneButtons() const
{
    std::vector<std::shared_ptr<IButton>> clonedButtons;
    for (const auto& button : buttons)
    {
        clonedButtons.push_back(button); // Assuming IButton has a proper copy constructor
    }
    return clonedButtons;
}

