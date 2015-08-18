/*
	For details, visit www.hammadmukhtar.com
*/

#include <iostream>
#include "List.h"
#include "Node.h"
#include "Node.cpp"

using namespace std;

template <class T> 
List<T>::List()
{
	this->head = this->tail = NULL;
}

//template <class T> 
//List<T>::List(List & l)
//{
//	for(Node<T> * temp = this->head ; temp->next != NULL ; temp = temp->next)
//	{
//		l.addToTail(temp->element);
//	}
//}
template <class T> 
void  List<T>::addToHead(T element)
{
	this->head = new Node<T>(element,this->head);
	if(this->tail == NULL)
		this->tail = this->head;
}

template <class T>  
void List<T>::addToTail(T element)
{
	if(this->head == NULL)
		this->head = this->tail = new Node<T>(element);
	else
	{
		this->tail->next = new Node<T>(element);
		this->tail = this->tail->next;
	}
}

template <class T>  
T List<T>::deleteFromHead()
{
	T key = this->head->element;
	Node<T> * temp = head;
	if(this->head == this->tail)
		this->head = this->tail = NULL;
	else
		this->head = this->head->next;

	delete temp;
	return key;
}

template <class T>  
T List<T>::deleteFromTail()
{
	T key;
	if(this->head == this->tail)
	{
		key = this->tail->element;
		delete this->tail;
		this->tail = this->head = NULL;
	}
	else
	{
		Node<T> * temp ;
		for(temp = this->head ; temp->next != this->tail ; temp = temp->next){}

		key = this->tail->element;
		delete this->tail;
		this->tail = temp;
		this->tail->next = NULL;
	}
	return key;
}


template <class T> 
List<T>::~List()
{
	/*Node<T> * temp;
	for(temp = this->head ; temp->next != NULL ;temp = temp->next)
	{
		this->deleteFromTail();
	}	*/
}

