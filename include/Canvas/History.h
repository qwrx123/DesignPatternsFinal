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

   private:
	std::vector<T> history;
	std::vector<T> undoneHistory;
	int			   limit = 100;
};

template <typename T>
void History<T>::push(T item)
{
	history.push_back(item);
}

template <typename T>
void History<T>::pop()
{
	if (!history.empty())
	{
		undoneHistory.push_back(history.back());
		history.pop_back();
	}
}

template <typename T>
T History<T>::peek()
{
	if (history.empty())
	{
		return T{};
	}
	return history.back();
}

template <typename T>
std::vector<T> History<T>::getHistory()
{
	return history;
}

template <typename T>
bool History<T>::isEmpty() const
{
	return history.empty();
}

template <typename T>
size_t History<T>::size() const
{
	return history.size();
}

template <typename T>
void History<T>::redo()
{
	if (!undoneHistory.empty())
	{
		push(undoneHistory.back());
		undoneHistory.pop_back();
	}
}

template <typename T>
void History<T>::undo()
{
	if (!history.empty())
	{
		pop();
	}
}

template <typename T>
T History<T>::peekLastUndone() const
{
	if (undoneHistory.empty())
	{
		return T{};
	}
	return undoneHistory.back();
}

template <typename T>
bool History<T>::isLastUndoneEmpty() const
{
	return undoneHistory.empty();
}

template <typename T>
size_t History<T>::undoneSize() const
{
	return undoneHistory.size();
}

template <typename T>
std::vector<T> History<T>::getUndoneHistory() const
{
	return undoneHistory;
}

#endif