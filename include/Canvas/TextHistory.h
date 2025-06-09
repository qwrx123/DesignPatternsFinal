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
	void											  pop() override;
	std::shared_ptr<IText>							  peek() override;
	[[nodiscard]] std::vector<std::shared_ptr<IText>> getHistory() override;
	[[nodiscard]] bool								  isEmpty() const override;
	[[nodiscard]] size_t							  size() const override;
	std::shared_ptr<IText>							  redo();
	void											  undo();
	[[nodiscard]] std::shared_ptr<IText>			  peekLastUndone() const;
	[[nodiscard]] bool								  isLastUndoneEmpty() const;
	[[nodiscard]] size_t							  undoneSize() const;
	[[nodiscard]] std::vector<std::shared_ptr<IText>> getUndoneHistory() const;

   private:
	std::vector<std::shared_ptr<IText>> history;
	std::vector<std::shared_ptr<IText>> undoneHistory;
	int									limit = 100;
};

#endif