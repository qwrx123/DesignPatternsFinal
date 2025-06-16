#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <memory>
#include <string>
#include <vector>
#include "Bounds.h"
#include "SliderButton.h"
#include "IButton.h"
#include "IMenu.h"
#include "IInputReceiver.h"
#include "IToolManager.h"
#include "ITextManager.h"
#include "LayerManager.h"

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
	void			   open() override;
	void			   close() override;

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
	void onResize(int width, int height) override;

	void setToolPointer(const std::shared_ptr<IToolManager>& ptr);
	void setTextPointer(const std::shared_ptr<ITextManager>& ptr);
	void setLayerPointer(std::shared_ptr<LayerManager> ptr);

	[[nodiscard]] const std::vector<std::shared_ptr<IButton>>& getLayerDropdownButtons() const;
	[[nodiscard]] const std::vector<std::shared_ptr<IButton>>& getLayerDeleteButtons() const;
	void													   rebuildLayerDropdownButtons();
	void handleDropdownButtons(KeyAction action, double x, double y, bool& clickedInsideDropdown);
	void update();
	void updateBrushButtonColor(Color newColor);

	void					  beginRenameLayer(int layerIndex);
	[[nodiscard]] bool		  isRenaming() const;
	[[nodiscard]] std::string getRenameBuffer() const;
	[[nodiscard]] int		  getLayerBeingRenamed() const;

   private:
	std::string							  label;
	Bounds								  bounds;
	std::vector<std::shared_ptr<IButton>> buttons;
	std::shared_ptr<IToolManager>		  tool;
	std::shared_ptr<ITextManager>		  text;
	int									  selectedIndex = 0;

	std::shared_ptr<LayerManager>		  layerManager;
	bool								  dropdownOpen = false;
	std::vector<std::shared_ptr<IButton>> layerDropdownButtons;
	std::vector<std::shared_ptr<IButton>> layerDeleteButtons;
	std::vector<std::shared_ptr<IButton>> layerRenameButtons;
	bool								  renamingLayer		= false;
	int									  layerBeingRenamed = -1;
	std::string							  renameBuffer;

	float halfHeight	= 0;
	float quarterHeight = 0;

	// Functions
	[[nodiscard]] std::vector<std::shared_ptr<IButton>> cloneButtons() const;

	void		 setSliderButtonValues();
	static float sliderValueCalc(const std::shared_ptr<SliderButton>& slider, double x);
	void onButton(const std::shared_ptr<IButton>& button, const std::string& label, double x,
				  double y, int itCount);
	void sliderLogic(const std::shared_ptr<SliderButton>& slider, const std::string& label,
					 double x, double y);
	void onColorButton(const std::shared_ptr<IButton>& button, const std::string& label, double x,
					   double y, int itCount);
	void onHistoryButton(const std::shared_ptr<IButton>& button, const std::string& label, double x,
						 double y, int itCount);
	void onToolButton(const std::shared_ptr<IButton>& button, const std::string& label, double x,
					  double y, int itCount);
};

#endif	// MENU_BAR_H