/*
	For details, visit www.hammadmukhtar.com
*/

#ifndef STACK_H
#define STACK_H

template <class T>
class Stack
{
private:
	int pointer;
	T * S;
	int size;

public:
	Stack(int s);
	void CreateStack();
	void DestroyStack();
	~Stack();
	T Pop();
	void Push(T element);
	bool IsEmpty();
	void ClearStack();
	T TopElement();

};
#endif