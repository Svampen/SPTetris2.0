#ifndef LIST_H
#define LIST_H
#include <iostream>
#include "Node.h"
using namespace std;

template <class T>
class List
{
public:
	List(void)
	{
		first = NULL;
		nrOfElements = 0;
	}

	~List()
	{
		while(!isEmpty())
		{
			deleteElementAt(0);
		}
	}

	bool addFirst(T *data)
	{
		bool added = false;
		Node<T> *n = new Node<T>(*data);
		Node<T> *temp;
		if(first != NULL)
		{
			temp = first;
			first = n;
			n->next = temp;
			added = true;
		}
		if(first == NULL)
		{
			first = n;
			added = true;
		}
		nrOfElements++;
		return added;
	}

	bool addElementAt(int index,T *data)
	{
		Node<T> *n = new Node<T>(*data);
		Node<T> *walker = first;
		bool added = false;
		if(first != NULL && nrOfElements < index)
		{
			for(int i=0;i<nrOfElements;i++)
			{
				walker = walker->next;
			}
			walker->next = n;
			added = true;
		}
		if(first != NULL && nrOfElements >= index)
		{
			for(int i=0;i<index-1;i++)
			{
				walker = walker->next;
			}
			Node<T> *temp;
			temp = walker->next;
			walker->next = n;
			n->next = temp;
			temp = NULL;
			added = true;
		}
		walker = NULL;
		nrOfElements++;
		return added;
	}

	bool deleteElementAt(int index)
	{
		bool deleted = false;
		Node<T> *walker = first;
		if(first != NULL && nrOfElements > index)
		{
			for(int i=0;i<index-1;i++)
			{
				walker = walker->next;
			}
			if(index == 0)
			{
				first = walker->next;
				delete walker;
			}
			else
			{
				Node<T> *temp = walker->next;
				walker->next = temp->next;
				delete temp;
			}
			deleted = true;
			nrOfElements--;
		}
		walker = NULL;
		return deleted;
	}

	bool deleteElement(T* data)
	{
		bool deleted = false;
		Node<T> *walker = first;

		for(int i = 0; i < nrOfElements; i++)
		{
			if(walker->data == *data)
			{
				deleteElementAt(i);
				return true;
			}
			walker = walker->next;
		}
		return false;
	}

	T* getAt(int index)
	{
		Node<T> *walker = first;
		if(first != NULL && nrOfElements > index)
		{
			for(int i=0;i<index;i++)
			{
				walker = walker->next;
			}
			return &walker->data;
		}
		else
		{
			return NULL;
		}
	}

	bool isEmpty()
	{
		return (nrOfElements == 0);
	}

	int getSize()
	{
		return nrOfElements;
	}
	
	bool setAt(int index,T* data)
	{
		Node<T> *walker = first;
		if(first != NULL && index < nrOfElements)
		{
			for(int i=0;i<index;i++)
			{
				walker = walker->next;
			}
			walker->data = *data;
			return true;
		}
		return false;
	}

	friend ostream &operator<<(ostream &out, List<T> &list)
	{
		for (Node<T> *walker = list.first; walker != NULL; walker = walker->next)
		{			
			out << walker->data << ", ";		
		}		
		return out;	
	}
private:
	Node<T> *first;
	int nrOfElements;
};
#endif
