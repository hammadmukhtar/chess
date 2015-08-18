/*
	For details, visit www.hammadmukhtar.com
*/

#ifndef NODE_H
#define NODE_H


template <class T>
class Node
{
public:
//	friend class List;
	T element;
	Node<T> * next;

public:
	Node();
	Node(T  element, Node* next = NULL);

    T getElement();
	void setElement(T element);
	void setNext(Node* next);
};


#endif