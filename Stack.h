
#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <type_traits>
#include <iterator>
#include <cstddef>
#include <stdexcept>
#include <initializer_list>

/*
*************************************************************************************************************************************************
* class Node
*/

template < typename Type >
class Node
{
public:
	Node() :
		_ptrNext(nullptr)
	{}

	Node(const Type &data, Node<Type> * ptrNode = nullptr) :
		_data(data),
		_ptrNext(ptrNode)
	{}

	~Node()
	{
		this->_ptrNext = nullptr;
	}

	Type _data;
	Node<Type> *_ptrNext;
};

/*
*************************************************************************************************************************************************
*/



/*
*************************************************************************************************************************************************
* class Stack
*/

template < typename Type,
	typename UnqualifiedType = typename std::remove_const< Type >::type >
class Stack_iterator;

template < typename Type >
class Stack
{
public:

	using iterator = Stack_iterator< Type >;
	using const_iterator = Stack_iterator< const Type >;

	Stack() :
		_ptrHead(nullptr),
		_sizeStack(0)
	{};

	/*
	* Constructor with initializer_list.
	*/
	Stack(const std::initializer_list<Type> &initList) :
		Stack()
	{
		for (auto i : initList)
		{
			this->push(i);
		}
	};

	/*
	* Copy constructor.
	*/
	Stack(const Stack<Type> &obj) :
		Stack()
	{
		this->copyStack(obj);
	}

	/*
	* Move constructor.
	*/
	Stack(Stack &&obj) :
		Stack()
	{
		*this = std::move(obj);
	}

	/*
	* Copy assignment operator.
	*/
	Stack<Type> & operator=(const Stack<Type> &obj)
	{
		if (this != &obj)
		{
			this->clear();
			this->copyStack(obj);
		}
		return *this;
	}

	/*
	* Move assignment operator.
	*/
	Stack<Type> & operator=(Stack &&obj)
	{
		if (this != &obj)
		{
			this->clear();

			this->_ptrHead = obj._ptrHead;
			this->_sizeStack = obj._sizeStack;

			obj._ptrHead = nullptr;
			obj._sizeStack = 0;
		}
		return *this;
	}

	/*
	* Inserts a new element at the top of the stack, above its current top element.
	* The content of this new element is initialized to a copy of data.
	*/
	void push(const Type &data)
	{
		Node<Type> *ptrTemp = new Node<Type>(data, this->_ptrHead);
		this->_ptrHead = ptrTemp;
		this->_sizeStack++;
	}

	/*
	* Removes the element on top of the stack, reducing its size by one.
	*/
	void pop()
	{
		if (this->_ptrHead == nullptr)
			return;

		Node<Type> *ptrTemp = this->_ptrHead;
		this->_ptrHead = this->_ptrHead->_ptrNext;
		delete ptrTemp;

		this->_sizeStack--;
	}

	/*
	* Returns a reference to the top element in the stack.
	*/
	Type & top()
	{
		if (this->_ptrHead == nullptr)
			throw std::out_of_range("The stack is empty");

		return this->_ptrHead->_data;
	}

	/*
	* Returns the number of elements in the stack.
	*/
	size_t size() const
	{
		return this->_sizeStack;
	}

	/*
	* Checks if the stack has no elements.
	* Return value : true if the stack is empty,
	*				  false otherwise
	*/
	bool empty() const
	{
		return this->_sizeStack == 0 ? true : false;
	}

	/*
	* Clears the stack.
	*/
	void clear()
	{
		while (this->_ptrHead)
		{
			this->pop();
		}
	}

	iterator begin()
	{
		return iterator(this->_ptrHead);
	}

	iterator end()
	{
		return iterator();
	}

	const_iterator cbegin() const
	{
		return const_iterator(this->_ptrHead);
	}
	
	const_iterator  cend() const
	{
		return const_iterator();
	}

	~Stack()
	{
		this->clear();
	}

private:
	Node<Type> *_ptrHead;
	size_t _sizeStack;

	void copyStack(const Stack<Type> &obj)
	{
		if (obj._ptrHead == nullptr)
		{
			this->_ptrHead = nullptr;
		}
		else
		{
			Node<Type> *ptrTemp = obj._ptrHead;
			Node<Type> *ptrCurrent = new Node<Type>(ptrTemp->_data);
			this->_ptrHead = ptrCurrent;
			Node<Type> *ptrPrevious = ptrCurrent;
			while (ptrTemp->_ptrNext != nullptr)
			{
				ptrTemp = ptrTemp->_ptrNext;
				ptrCurrent = new Node<Type>(ptrTemp->_data);
				ptrPrevious->_ptrNext = ptrCurrent;
				ptrPrevious = ptrCurrent;
			}

			this->_sizeStack = obj._sizeStack;
		}
	}
};

/*
*************************************************************************************************************************************************
*/



/*
*************************************************************************************************************************************************
* class Stack_iterator
*/

template < typename Type,
	typename UnqualifiedType>
class Stack_iterator : public std::iterator<std::forward_iterator_tag,
	UnqualifiedType,
	std::ptrdiff_t,
	Type *,
	Type &>
{

	friend class Stack< Type >;

public:
	explicit Stack_iterator() :
		_ptrArg(nullptr)
	{}

	explicit Stack_iterator(Node< UnqualifiedType > *ptrArg) :
		_ptrArg(ptrArg)
	{}

	/*
	* Copy constructor.
	*/
	Stack_iterator(const Stack_iterator< Type > &rhs) :
		_ptrArg(rhs._ptrArg)
	{}

	/*
	* Move constructor.
	*/
	Stack_iterator(Stack_iterator< Type > &&rhs)
	{
		*this = std::move(rhs);
	}

	/*
	* Copy assignment operator.
	*/
	Stack_iterator< Type > & operator=(const Stack_iterator< Type > &rhs)
	{
		if (this != &rhs)
		{
			this->_ptrArg = rhs._ptrArg;
		}
		return *this;
	}

	/*
	* Move assignment operator.
	*/
	Stack_iterator< Type > & operator=(Stack_iterator< Type > &&rhs)
	{
		if (this != &rhs)
		{
			this->_ptrArg = rhs._ptrArg;
			rhs._ptrArg = nullptr;
		}
		return *this;
	}

	Type & operator*()
	{
		return this->_ptrArg->_data;
	}

	Type * operator->()
	{
		return (&this->_ptrArg->_data);
	}

	bool operator==(const Stack_iterator< Type > &rhs) const
	{
		return this->_ptrArg == rhs._ptrArg;
	}

	bool operator!=(const Stack_iterator< Type > &rhs) const
	{
		return this->_ptrArg != rhs._ptrArg;
	}

	Stack_iterator & operator++()
	{
		this->_ptrArg = this->_ptrArg->_ptrNext;
		return *this;
	}

	Stack_iterator operator++(int)
	{
		Stack_iterator< Type > ptrTemp(*this);
		this->_ptrArg = this->_ptrArg->_ptrNext;
		return ptrTemp;
	}

	/*
	* one way conversion: iterator -> const_iterator
	*/
	operator Stack_iterator< const Type >() const
	{
		return Stack_iterator<const Type>(this->_ptrArg);
	}

	~Stack_iterator()
	{
		this->_ptrArg = nullptr;
	}

private:
	Node< UnqualifiedType > *_ptrArg;
};

/*
*************************************************************************************************************************************************
*/

#endif