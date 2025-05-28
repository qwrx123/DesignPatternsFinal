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

	TextManager(const TextManager& other);
	TextManager& operator=(const TextManager& other);
	TextManager(TextManager&& other) noexcept;
	TextManager& operator=(TextManager&& other) noexcept;

	void addText(std::shared_ptr<IText> text) override;
	void removeText(std::shared_ptr<IText> text) override;

	[[nodiscard]] const std::vector<std::shared_ptr<IText>>& getTexts() const override;

	[[nodiscard]] std::shared_ptr<IText> getTextAt(double x, double y) const override;

	void clearAll() override;

   private:
	std::vector<std::shared_ptr<IText>> texts;

	[[nodiscard]] std::vector<std::shared_ptr<IText>> copyTexts() const;
};

#endif	// TEXTMANAGER_H