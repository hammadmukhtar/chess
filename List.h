/*
	For details, visit www.hammadmukhtar.com
*/

#ifndef LIST_H
#define LIST_H

#include "Node.h"


template <class T> 
class List
{
public:
	Node<T> *head;
	Node<T> *tail;

public:
	List();
	//List(List & l);
	void addToHead(T);
	void addToTail(T);
	T deleteFromHead();
	T deleteFromTail();
	void deleteAll()
	{
		while(this->head != NULL)
		{
			deleteFromHead();
		}
	}
	
	~List();
};


#endif