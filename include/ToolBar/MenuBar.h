#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <memory>
#include <string>
#include <vector>
#include "Bounds.h"
#include "IButton.h"
#include "IMenu.h"
#include "IInputReceiver.h"
#include "IToolManager.h"
#include "ITextManager.h"

class MenuBar : public IMenu, public IInputReceiver
{
   public:
	MenuBar();
	~MenuBar() override;
	MenuBar(const MenuBar& other);
	MenuBar& operator=(const MenuBar& other);
	MenuBar(MenuBar&& other) noexcept;
	MenuBar& operator=(MenuBar&& other) noexcept;

	[[nodiscard]] std::string getLabel() const override;
	void					  setLabel(const std::string& label) override;

	[[nodiscard]] Bounds getBounds() const override;
	void				 setBounds(const Bounds& bounds) override;

	// MenuBar is being implemented as always open
	[[nodiscard]] bool isOpen() const override;
	[[nodiscard]] bool isClosed()
		const override;	 // wait why is there both, isOpen():false == isClosed():true?
	void open() override;
	void close() override;

	void setDefaultButtons();
	void addButton(std::shared_ptr<IButton> button) override;
	void clearButtons() override;
	[[nodiscard]] const std::vector<std::shared_ptr<IButton>>& getButtons() const override;

	[[nodiscard]] int					   getSelectedIndex() const override;
	void								   setSelectedIndex(int index) override;
	[[nodiscard]] std::shared_ptr<IButton> getSelectedItem() const override;

	// since MenuBar is implemented as always open, these will be false/unused
	[[nodiscard]] bool showSelectedLabelWhenClosed() const override;
	void			   setShowSelectedLabelWhenClosed(bool show) override;

	void onMouseMove(double x, double y) override;
	void onMouseButton(MouseButton click, KeyAction action, double x, double y) override;
	void onKey(int key, KeyAction action) override;
	void onChar(unsigned int codepoint) override;

	void setToolPointer(const std::shared_ptr<IToolManager>& ptr);
	void setTextPointer(const std::shared_ptr<ITextManager>& ptr);

   private:
	std::string							  label;
	Bounds								  bounds;
	std::vector<std::shared_ptr<IButton>> buttons;
	std::shared_ptr<IToolManager>		  tool;
	std::shared_ptr<ITextManager>		  text;
	int									  selectedIndex = 0;

	int halfHeight;
	int quarterHeight;

	// Functions
	[[nodiscard]] std::vector<std::shared_ptr<IButton>> cloneButtons() const;
};

#endif	// MENU_BAR_H