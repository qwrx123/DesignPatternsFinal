#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <memory>
#include <vector>
#include "ITextManager.h"
#include "Text.h"
#include "IInputReceiver.h"
#include "TextHistory.h"

class TextManager : public ITextManager, public IInputReceiver
{
   public:
	TextManager();
	~TextManager() override;

	TextManager(const TextManager& other);
	TextManager& operator=(const TextManager& other);
	TextManager(TextManager&& other) noexcept;
	TextManager& operator=(TextManager&& other) noexcept;

	void addText(std::shared_ptr<IText> text) override;
	void removeText(std::shared_ptr<IText> text) override;

	void			   registerTextTool(std::shared_ptr<IText> text) override;
	[[nodiscard]] bool isTextToolActive() const override;
	void			   setTextToolActive() override;
	void			   setTextToolInactive() override;

	[[nodiscard]] const std::vector<std::shared_ptr<IText>>& getTexts() const override;

	[[nodiscard]] std::shared_ptr<IText> getTextAt(double x, double y) const override;

	void clearAll() override;

	void		onMouseMove(double x, double y) override;
	void		onMouseButton(MouseButton button, KeyAction action, double x, double y) override;
	void		onKey(int key, KeyAction action) override;
	void		onChar(unsigned int codepoint) override;
	void		onResize(int width, int height) override;
	void		setFontSize(int size) override;
	void		undoText() override;
	void		redoText() override;
	TextHistory getHistory();

   private:
	std::vector<std::shared_ptr<IText>> texts;

	[[nodiscard]] std::vector<std::shared_ptr<IText>> copyTexts() const;

	bool		active = false;
	Bounds		bounds;
	std::string fontName;
	int			fontSize = 0;
	Color		color	 = {.r = 0.0F, .g = 0.0F, .b = 0.0F, .a = 1.0F};

	TextHistory textHistory;

	void insertTab();
	void handleBackspace();
	void handleEnter();
};

#endif	// TEXTMANAGER_H