#include<stdlib.h>
#include"list_itr.h"
#include"list.h"
#include"commun.h"

#define CHECKNULLPOINTER(X)		if(NULL == (X)) return NULL;

/*##################STATICS###############*/
/*static int IsAtTail(ListItr _itr);*/
static int NextIsAtHead(ListItr _itr);
static int IsEmpty(ListItr _itr);
/*#########################################*/

static void RemoveNode(Node* _right, Node* _nodeToRemove);
ListItr ListItr_Begin(const List* _list)
{
	CHECKNULLPOINTER(_list);
	return _list -> m_head.m_next;
}

ListItr ListItr_End(const List* _list)
{
	CHECKNULLPOINTER(_list)

	return (ListItr) (&(_list -> m_tail));
}

int ListItr_Equals(const ListItr _a, const ListItr _b)
{
	if(NULL == _a  || NULL == _b)
	{
		return 0;
	}

	return _a == _b;
}

ListItr ListItr_Next(ListItr _itr)
{
	CHECKNULLPOINTER(_itr);

	_itr = (ListItr)((Node*)_itr) -> m_next;
	return _itr ;
}

ListItr ListItr_Prev(ListItr _itr)
{
	return (_itr &&  ((Node*)_itr)->m_previous->m_previous ) ? (ListItr)((Node*)_itr)->m_previous : _itr;
}

void* ListItr_Get(ListItr _itr)
{
	CHECKNULLPOINTER(_itr)

	if((ListItr)((Node*)_itr)-> m_next != _itr && (ListItr)((Node*)_itr) -> m_previous != _itr)
	{
		return (ListItr)((Node*)_itr) -> m_data;
	}
	return NULL;
}

void* ListItr_Set(ListItr _itr, void* _element)
{
	void* temp;
	CHECKNULLPOINTER(_itr);
	CHECKNULLPOINTER(_element);

	if((ListItr)((Node*)_itr) -> m_next != _itr && (ListItr)((Node*)_itr) -> m_previous != _itr)
	{
		temp = (ListItr)((Node*)_itr) -> m_data;
		((Node*)_itr) -> m_data = _element;
		return temp;
	}
	return NULL;

}

ListItr ListItr_InsertBefore(ListItr _itr, void* _element)
{
	Node* newNode;
	CHECKNULLPOINTER(_itr);
	CHECKNULLPOINTER(_element);

	newNode = (Node*) malloc(sizeof(Node));
	if(newNode)
	{
		newNode -> m_data = _element;
		((Node*)_itr)-> m_previous -> m_next = newNode;
		newNode -> m_previous = ((Node*)_itr) -> m_previous;
		((Node*)_itr)-> m_previous = newNode;
		((Node*)_itr)-> m_previous -> m_next = _itr;
		return (ListItr)((Node*)_itr)-> m_previous;
	}
	return NULL;
}

void* ListItr_Remove(ListItr _itr)
{
	void* dataRemoved; 

	if (!_itr || IsEmpty(_itr))
	{
		return NULL;
	}
	
	dataRemoved = ((Node*)_itr)->m_data ;
	RemoveNode((Node*)ListItr_Next(_itr),  (Node*)_itr);

	return dataRemoved;

}


static void RemoveNode(Node* _right, Node* _nodeToRemove) 
{
	_nodeToRemove -> m_previous -> m_next = _nodeToRemove -> m_next;
	_nodeToRemove -> m_next -> m_previous = _nodeToRemove -> m_previous;
	_nodeToRemove -> m_next	=  NULL;
	_nodeToRemove -> m_previous	=  NULL;
	free(_nodeToRemove);
}


/*static int IsAtTail(ListItr _itr)
{
	return ListItr_Equals((ListItr)((Node*)_itr) -> m_next, (ListItr)((Node*)_itr) -> m_next -> m_next);
}*/

static int NextIsAtHead(ListItr _itr)
{
	return ListItr_Equals((ListItr)((Node*)_itr) -> m_previous, (ListItr)((Node*)_itr) -> m_previous -> m_previous);
}

static int IsEmpty(ListItr _itr)
{
	return ListItr_Equals(_itr , (ListItr)((Node*)_itr) ->m_next);
}
