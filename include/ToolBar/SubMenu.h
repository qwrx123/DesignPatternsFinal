#ifndef SUB_MENU_H
#define SUB_MENU_H

#include <memory>
#include <string>
#include <vector>
#include "Bounds.h"
#include "IButton.h"
#include "IMenu.h"

class SubMenu : public IMenu
{
    public:
     SubMenu();
     ~SubMenu() override;
     SubMenu(const SubMenu& other);
     SubMenu& operator=(const SubMenu& other);
     SubMenu(SubMenu&& other) noexcept;
     SubMenu& operator=(SubMenu&& other) noexcept;
    
     [[nodiscard]] std::string getLabel() const override;
     void					  setLabel(const std::string& label) override;
    
     [[nodiscard]] Bounds getBounds() const override;
     void				 setBounds(const Bounds& bounds) override;
    
     [[nodiscard]] bool isOpen() const override;
     [[nodiscard]] bool isClosed() const override;
     void open() override;
     void close() override;
    
     void addButton(std::shared_ptr<IButton> button) override;
     void clearButtons() override;
     [[nodiscard]] const std::vector<std::shared_ptr<IButton>>& getButtons() const override;
    
     [[nodiscard]] int					   getSelectedIndex() const override;
     void								   setSelectedIndex(int index) override;
     [[nodiscard]] std::shared_ptr<IButton> getSelectedItem() const override;
    
     [[nodiscard]] bool showSelectedLabelWhenClosed() const override;
     void			   setShowSelectedLabelWhenClosed(bool show) override;
    
    private:
     std::string							  label;
     Bounds								  bounds;
     std::vector<std::shared_ptr<IButton>> buttons;
     int									  selectedIndex = 0;
     bool                                   isOpenState = false;
    
     // Functions
     [[nodiscard]] std::vector<std::shared_ptr<IButton>> cloneButtons() const;
};

#endif