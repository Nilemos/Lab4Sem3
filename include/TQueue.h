#pragma once

#include <iostream>

const size_t MAX_QUEUE_SIZE = 100000000;

template <typename T>
class TQueue
{
protected:
	T* pMem;
	size_t memSize;
	size_t hi;
	size_t li;
	size_t dataCount;
	const static size_t unzero = ~0;
public:
	TQueue(size_t sz = 10);
	TQueue(const TQueue& q);
	TQueue(TQueue&& q) noexcept;
	TQueue& operator=(const TQueue& q);
	TQueue& operator=(TQueue&& q) noexcept;
	~TQueue();

	bool IsEmpty(void) const noexcept;
	bool IsFull(void) const noexcept;

	void Free(void) noexcept;
	void Push(const T& e);
	T Top(void) const;
	void Pop(void);
	T TopPop(void);

	bool operator==(const TQueue& q) const noexcept;
	bool operator!=(const TQueue& q) const noexcept;
};

template<typename T>
inline TQueue<T>::TQueue(size_t sz)
{
	hi = 0;
	li = 0;
	pMem = nullptr;
	dataCount = 0;
	if (sz == 0)
		throw "Err";
	if (sz > MAX_QUEUE_SIZE)
		throw "Err";
	memSize = sz;
	pMem = new T[memSize];
}

template<typename T>
inline TQueue<T>::TQueue(const TQueue<T>& q)
{
	if (q.pMem == nullptr)
	{
		memSize = 0;
		pMem = nullptr;
		Free();
	}
	else
	{
		memSize = q.memSize;
		hi = q.hi;
		li = q.li;
		dataCount = q.dataCount;
		pMem = new T[memSize];
		if (!(q.IsEmpty()))
		{
			size_t j = hi;
			for (size_t i = 0; i < dataCount; i++)
			{
				pMem[j] = q.pMem[j];
				j--;
				if (j == unzero)
					j = memSize - 1;
			}
		}
	}
}

template<typename T>
inline TQueue<T>::TQueue(TQueue<T>&& q) noexcept
{
	this->operator=(q);
}

template<typename T>
inline TQueue<T>& TQueue<T>::operator=(const TQueue<T>& q)
{
	if (this == &q)
		return *this;
	if (memSize != q.memSize)
	{
		T* tmp = new T[q.memSize];
		delete[] pMem;
		memSize = q.memSize;
		pMem = tmp;
	}
	hi = q.hi;
	li = q.li;
	dataCount = q.dataCount;
	if (!(q.IsEmpty()))
	{
		size_t j = hi;
		for (size_t i = 0; i < dataCount; i++)
		{
			pMem[j] = q.pMem[j];
			j--;
			if (j == unzero)
				j = memSize - 1;
		}
	}
	return *this;
}

template<typename T>
inline TQueue<T>& TQueue<T>::operator=(TQueue<T>&& q) noexcept
{
	pMem = nullptr;
	memSize = 0;
	Free();
	std::swap(pMem, q.pMem);
	std::swap(memSize, q.memSize);
	std::swap(hi, q.hi);
	std::swap(li, q.li);
	std::swap(dataCount, q.dataCount);
	return *this;
}

template<typename T>
inline TQueue<T>::~TQueue()
{
	delete[] pMem;
	memSize = 0;
	Free();
}

template<typename T>
inline bool TQueue<T>::IsEmpty(void) const noexcept
{
	return dataCount == 0;
}

template<typename T>
inline bool TQueue<T>::IsFull(void) const noexcept
{
	return dataCount == memSize;
}

template<typename T>
inline void TQueue<T>::Free(void) noexcept
{
	hi = 0;
	li = 0;
	dataCount = 0;
}

template<typename T>
inline void TQueue<T>::Push(const T& e)
{
	if (IsFull())
		throw "Err";
	pMem[li] = e;
	li++;
	li = (li < memSize) ? li : 0;
	dataCount++;
}

template<typename T>
inline T TQueue<T>::Top(void) const
{
	if (IsEmpty())
		throw "Err";
	return pMem[hi];
}

template<typename T>
inline void TQueue<T>::Pop(void)
{
	if (IsEmpty())
		throw "Err";
	hi++;
	hi = (hi < memSize) ? hi : 0;
	dataCount--;
}

template<typename T>
inline T TQueue<T>::TopPop(void)
{
	T tmp = Top();
	Pop();
	return tmp;
}

template<typename T>
inline bool TQueue<T>::operator==(const TQueue& q) const noexcept
{
	if (dataCount != q.dataCount)
		return false;
	size_t j = hi, k = q.hi;
	for (size_t i = 0; i < dataCount; i++)
	{
		if (pMem[j] != q.pMem[k])
			return false;
		j--;
		if (j == unzero)
			j = memSize - 1;
		k--;
		if (k == unzero)
			k = q.memSize - 1;
	}
	return true;
}

template<typename T>
inline bool TQueue<T>::operator!=(const TQueue& q) const noexcept
{
	return !(this->operator==(q));
}