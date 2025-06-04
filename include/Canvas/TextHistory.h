#ifndef TEXTHISTORY_H
#define TEXTHISTORY_H

#include <memory>
#include <vector>
#include "IHistoryStack.h"
#include "ITextManager.h"

class TextHistory : public IHistoryStack<std::shared_ptr<IText>>
{
   public:
	TextHistory()					= default;
	TextHistory(const TextHistory&) = default;

	TextHistory& operator=(const TextHistory&)	   = default;
	TextHistory(TextHistory&&) noexcept			   = default;
	TextHistory& operator=(TextHistory&&) noexcept = default;
	~TextHistory() override						   = default;

	void											  push(std::shared_ptr<IText> text) override;
	std::shared_ptr<IText>							  pop() override;
	std::shared_ptr<IText>							  peek() override;
	[[nodiscard]] std::vector<std::shared_ptr<IText>> getHistory() override;
	[[nodiscard]] bool								  isEmpty() const override;
	[[nodiscard]] size_t							  size() const override;
	void											  redo();
	void											  undo();

   private:
	std::vector<std::shared_ptr<IText>> history;
	std::vector<std::shared_ptr<IText>> undoneHistory;
};

#endif