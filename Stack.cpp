/*
	For details, visit www.hammadmukhtar.com
*/

#include "Stack.h"

template <class T>
Stack<T>::Stack(int s)
{
	this->size = s;
	this->pointer = -1;
	CreateStack();
}

template <class T>
void Stack<T>::CreateStack()
{
	this->S = new T[this->size];
}

template <class T>
Stack<T>::~Stack()
{
	delete S;
}

template <class T>
bool Stack<T>::IsEmpty()
{
	if(this->pointer == -1)
		return true;
	else
		return false;
}

template <class T>
T Stack<T>::Pop()
{
	if(!this->IsEmpty())
	{
		return S[pointer--];
	}
	else
		return S[0];
}


template <class T>
void Stack<T>::DestroyStack()
{
	delete this->S;
	this->S = new T[0];
}

template <class T>
void Stack<T>::Push(T element)
{
	if(this->pointer+1 < this->size)
	{
		pointer++;
		this->S[pointer] = element;
	}
}

template <class T>
void Stack<T>::ClearStack()
{
	this->pointer = -1;
}

template <class T>
T Stack<T>::TopElement()
{
	if(!this->IsEmpty())
		return this->S[pointer];
	else
		return 1;
}