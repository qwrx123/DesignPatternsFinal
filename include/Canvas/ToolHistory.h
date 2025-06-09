#ifndef TOOLHISTORY_H
#define TOOLHISTORY_H

#include <memory>
#include <vector>
#include "IHistoryStack.h"
#include "IStroke.h"

class ToolHistory : public IHistoryStack<std::shared_ptr<IStroke>>
{
   public:
	ToolHistory()					= default;
	ToolHistory(const ToolHistory&) = default;

	ToolHistory& operator=(const ToolHistory&)	   = default;
	ToolHistory(ToolHistory&&) noexcept			   = default;
	ToolHistory& operator=(ToolHistory&&) noexcept = default;
	~ToolHistory() override						   = default;

	void					 push(std::shared_ptr<IStroke> tool) override;
	void					 pop() override;
	std::shared_ptr<IStroke> peek() override;
	[[nodiscard]] std::vector<std::shared_ptr<IStroke>> getHistory() override;
	[[nodiscard]] bool									isEmpty() const override;
	[[nodiscard]] size_t								size() const override;
	std::shared_ptr<IStroke>							redo();
	void												undo();
	[[nodiscard]] std::shared_ptr<IStroke>				peekLastUndone() const;
	[[nodiscard]] bool									isLastUndoneEmpty() const;
	[[nodiscard]] size_t								undoneSize() const;
	[[nodiscard]] std::vector<std::shared_ptr<IStroke>> getUndoneHistory() const;

   private:
	std::vector<std::shared_ptr<IStroke>> history;
	std::vector<std::shared_ptr<IStroke>> undoneHistory;
	int									  limit = 100;
};

#endif