#pragma once

#include "Iterator.h"
#include "Allocate.h"
#include "Construct.h"

template <class T>
struct __ListNode
{
	__ListNode<T>* _next;
	__ListNode<T>* _prev;
	T _data;

	__ListNode(const T& x = T())
		:_data(x)
		,_next(NULL)
		,_prev(NULL)
	{}
};

// T T& T*
// T const T& const T*
template<class T, class Ref, class Ptr>
struct __ListIterator
{
	typedef __ListIterator<T, Ref, Ptr> Self;
	typedef __ListNode<T> ListNode;
	
	typedef BidirectionalIteratorTag IteratorCategory;
	typedef T ValueType;
	typedef Ptr Pointer;
	typedef Ref Reference;
	typedef ptrdiff_t DifferenceType;

public:
	__ListIterator(ListNode* x) : _node(x) {}
	__ListIterator() {}
	
	bool operator==(const Self& x) const
	{
		return _node == x._node;
	}

	bool operator!=(const Self& x) const
	{
		return _node != x._node;
	}

	Reference operator*() const
	{ 
		return _node->_data;
	}

	Pointer operator->() const
	{ 
		return &(operator*());
	}

	Self& operator++()
	{ 
		_node = _node->_next;
		return *this;
	}

	Self operator++(int)
	{ 
		Self tmp = *this;
		++*this;
		return tmp;
	}

	Self& operator--()
	{ 
		_node = _node->_prev;
		return *this;
	}

	Self operator--(int) { 
		Self tmp = *this;
		--*this;
		return tmp;
	}

	ListNode* _node;
};

template<class T, class alloc = Alloc>
class List
{
	typedef __ListNode<T> ListNode;
public:
	typedef __ListIterator<T, T&, T*> Iterator;
	typedef __ListIterator<T, const T&, const T*> ConstIterator;
	typedef ReverseIterator<Iterator>	ReverseIterator;

	typedef SimpleAlloc<ListNode, alloc> ListNodeAllocator;

	List()
	{
		_head = BuyNode();
		_head->_next = _head;
		_head->_prev = _head;
	}

	~List()
	{
		Clear();
		//delete _head;
		DestoryNode(_head);
	}

	ListNode* BuyNode(const T& x = T())
	{
		ListNode* node = ListNodeAllocator::Allocate();
		Construct(node, x);
		return node;
	}

	void DestoryNode(ListNode* node)
	{
		Destroy(node);
		ListNodeAllocator::Deallocate(node);
	}

	void Clear()
	{
		Iterator it = Begin();
		while (it != End())
		{
			Iterator del = it;
			++it;

			//delete del._node;
			DestoryNode(del._node);
		}

		_head->_next = _head;
		_head->_prev = _head;
	}

	Iterator Begin()
	{
		return _head->_next;
	}

	ConstIterator Begin() const
	{
		return _head->_next;
	}

	Iterator End()
	{
		return _head;
	}

	ConstIterator End() const
	{
		return _head;
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
		Insert(End(), x);
	}

	void PushFront(const T& x)
	{
		Insert(Begin(), x);
	}

	void PopBack()
	{
		Erase(--End());
	}

	void PopFront()
	{
		Erase(Begin());
	}

	// 在pos前插入一个节点
	void Insert(Iterator pos, const T& x)
	{
		ListNode* tmp = BuyNode(x);

		ListNode* cur = pos._node;
		ListNode* prev = cur->_prev;
		prev->_next = tmp;
		tmp->_next = cur;

		tmp->_prev = prev;
		cur->_prev = tmp;
	}

	Iterator Erase(Iterator pos)
	{
		ListNode* prev = pos._node->_prev;
		ListNode* next = pos._node->_next;

		prev->_next = next;
		next->_prev = prev;

		//delete pos._node;
		DestoryNode(pos._node);

		return next;
	}

protected:
	ListNode* _head;
};

// const类型的迭代器
void PrintList1(const List<int>& l)
{
	List<int>::ConstIterator it = l.Begin();
	while (it != l.End())
	{
	//	(*it)++;
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}

void PrintList2(List<int>& l)
{
	List<int>::Iterator it = l.Begin();
	while (it != l.End())
	{
		(*it)++;
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}

void TestReverseiterator()
{
	List<int> l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);

	List<int>::ReverseIterator it = l.RBegin();
	while (it != l.REnd())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}


void TestList()
{
	List<int> l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);

	l.PopBack();
	l.PopBack();

	PrintList1(l);
	PrintList2(l);

	TestReverseiterator();
}