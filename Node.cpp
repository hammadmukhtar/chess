/*
	For details, visit www.hammadmukhtar.com
*/

#include <iostream>
#include "Node.h"

template<class T>
Node<T>::Node()
{
	this->next = NULL;
}

template<class T> 
Node<T>::Node(T element, Node* next)
{
	this->element = element;
	this->next = next;
}

template<class T> 
T Node<T>::getElement()
{
	return this->element;
}

template<class T> 
void Node<T>::setElement(T element)
{
	this->element = element;
}


 template<class T> 
void Node<T>::setNext(Node* next)
{
	this->next = next;
}