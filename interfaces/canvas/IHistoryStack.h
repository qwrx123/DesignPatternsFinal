#ifndef I_HISTORY_STACK_H
#define I_HISTORY_STACK_H

#include <vector>

template <class T>
class IHistoryStack
{
   public:
	IHistoryStack()			 = default;
	virtual ~IHistoryStack() = default;

	IHistoryStack(const IHistoryStack&)				   = default;
	IHistoryStack& operator=(const IHistoryStack&)	   = default;
	IHistoryStack(IHistoryStack&&) noexcept			   = default;
	IHistoryStack& operator=(IHistoryStack&&) noexcept = default;

	[[nodiscard]] virtual bool			 isEmpty() const = 0;
	[[nodiscard]] virtual size_t		 size() const	 = 0;
	virtual void						 push(T item)	 = 0;
	virtual void						 pop()			 = 0;
	[[nodiscard]] virtual T				 peek()			 = 0;
	[[nodiscard]] virtual std::vector<T> getHistory()	 = 0;
	virtual void						 clear()		 = 0;
	virtual void						 clearUndone()	 = 0;
};

#endif