//Created BY Stefan Hagdahl
#ifndef NODE_H
#define NODE_H
template<class T>
class Node
{
public:
	Node();
	Node(T& data)
	{
		this->data = data;
		next = NULL;
	}
	~Node()
	{
	}

	Node<T> *next;
	T data;
};
#endif