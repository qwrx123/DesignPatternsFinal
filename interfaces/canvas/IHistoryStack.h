#ifndef I_HISTORY_STACK_H
#define I_HISTORY_STACK_H

#include <vector>

template <class T>
class IHistoryStack
{
   public:
	IHistoryStack()			 = default;
	virtual ~IHistoryStack() = default;

	virtual void	  push(T)	   = 0;
	virtual T		  pop()		   = 0;
	virtual T		  peek()	   = 0;
	virtual vector<T> getHistory() = 0;

   protected:
	std::vector<T> history;
};

#endif