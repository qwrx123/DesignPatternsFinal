#ifndef HISTORY_H
#define HISTORY_H

#include "IHistoryStack.h"
#include <vector>

template <typename T>

class History : public IHistoryStack<T>
{
   public:
	History()				= default;
	History(const History&) = default;

	History& operator=(const History&)	   = default;
	History(History&&) noexcept			   = default;
	History& operator=(History&&) noexcept = default;
	~History() override					   = default;

	void						 push(T item) override;
	void						 pop() override;
	T							 peek() override;
	[[nodiscard]] std::vector<T> getHistory() override;
	[[nodiscard]] bool			 isEmpty() const override;
	[[nodiscard]] size_t		 size() const override;
	void						 redo();
	void						 undo();
	[[nodiscard]] T				 peekLastUndone() const;
	[[nodiscard]] bool			 isLastUndoneEmpty() const;
	[[nodiscard]] size_t		 undoneSize() const;
	[[nodiscard]] std::vector<T> getUndoneHistory() const;
	void						 clear() override;

   private:
	std::vector<T> history;
	std::vector<T> undoneHistory;
};

#include "History.tpp"

#endif