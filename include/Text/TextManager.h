#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <memory>
#include <vector>
#include "ITextManager.h"
#include "Text.h"

class TextManager : public ITextManager
{
   public:
	TextManager();
	~TextManager() override;

	void addText(std::shared_ptr<IText> text) override;
	void removeText(std::shared_ptr<IText> text) override;

	[[nodiscard]] const std::vector<std::shared_ptr<IText>>& getTexts() const override;

	[[nodiscard]] std::shared_ptr<IText> getTextAt(double x, double y) const override;

	void clearAll() override;

   private:
	std::vector<std::shared_ptr<IText>> texts;
};

#endif	// TEXTMANAGER_H