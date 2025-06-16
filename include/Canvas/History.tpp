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

template <typename T>
void History<T>::clear()
{
	undoneHistory.clear();
	history.clear();
}

template <typename T>
void History<T>::clearUndone()
{
	undoneHistory.clear();
}
