#pragma once

#include "Uninitialiaed.h"

template<class T>
class Vector
{
public:
	typedef T ValueType;
	typedef ValueType* Iterator;
	typedef const ValueType* ConstIterator;

	typedef ReverseIterator<Iterator>	ReverseIterator;

	typedef SimpleAlloc<ValueType, Alloc> DataAllocator;

	Vector()
		:_start(0)
		,_finish(0)
		,_endOfStorage(0)
	{}

	~Vector()
	{
		//delete[] _start;
		if (_start)
		{
			Destroy(_start, _finish);
			DataAllocator::Deallocate(_start, _endOfStorage-_start);
		}

		_start = _finish = _endOfStorage = 0;
	}

	Iterator Begin()
	{
		return _start;
	}

	ConstIterator Begin() const
	{
		return _start;
	}

	Iterator End()
	{
		return _finish;
	}

	ConstIterator End() const
	{
		return _finish;
	}

	ReverseIterator RBegin()
	{
		return ReverseIterator(End());
	}

	ReverseIterator REnd()
	{
		return ReverseIterator(Begin());
	}

	void PushBack(const T& x)
	{
		_CheckStorage();

		*_finish = x;
		++_finish;
	}

	void PopBack()
	{
		assert(_finish != _start);
		--_finish;
	}

	size_t Size()
	{
		return _finish-_start;
	}

	ValueType& operator[](size_t index)
	{
		assert(_start+index < _finish);

		return _start[index];
	}

	void _CheckStorage()
	{
		/*if (_finish == _endOfStorage)
		{
			size_t size = _finish-_start;
			size_t newSize = size*2+3;
			ValueType* tmp = new ValueType[newSize];
			for (size_t i = 0; i < size; ++i)
			{
				tmp[i] = _start[i];
			}

			delete[] _start;
			_start = tmp;
			_finish = _start+size;
			_endOfStorage = _start+newSize;
		}*/

		if (_finish == _endOfStorage)
		{
			size_t size = _finish-_start;
			size_t newSize = size*2+3;
			ValueType* tmp = DataAllocator::Allocate(newSize);
			
			// 调用析构函数
			// 并调用空间配置器释放空间
			if (_start)
			{
				// 完成拷贝
				UninitializedCopy(_start, _finish, tmp);

				Destroy(_start, _finish);
				DataAllocator::Deallocate(_start);
			}

			_start = tmp;
			_finish = _start+size;
			_endOfStorage = _start+newSize;
		}
	}

protected:
	Iterator _start;
	Iterator _finish;
	Iterator _endOfStorage;

	/*T* _a;
	size_t size;
	size_t capacity;*/
};

void PrintVector1(const Vector<int>& v)
{
	Vector<int>::ConstIterator it = v.Begin();
	while (it != v.End())
	{
		//(*it)++;
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}

void PrintVector2(Vector<int>& v)
{
	Vector<int>::Iterator it = v.Begin();
	while (it != v.End())
	{
		(*it)++;
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}

void TestVector()
{
	Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);

	PrintVector1(v);
	PrintVector2(v);

	for (size_t i = 0; i < v.Size(); ++i)
	{
		v[i]++;
		cout<<v[i]<<" ";
	}
	cout<<endl;

	Vector<int>::ReverseIterator it = v.RBegin();
	while (it != v.REnd())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}