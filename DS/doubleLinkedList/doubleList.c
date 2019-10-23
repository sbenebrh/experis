#include<stdio.h>
#include<stdlib.h>
#include"doubleList.h"
#include"ADTErr.h"

typedef struct Node
{
	int 			m_data;
	struct Node* 	m_next;
	struct Node* 	m_previous;
	
}Node;

struct List
{
	Node 			m_head;
	Node 			m_tail;
};

List* ListCreate()
{
	List* newList = (List*) malloc(sizeof(List));
	if(newList)
	{
		newList -> m_head.m_next =	&(newList->m_tail);
		newList -> m_tail.m_previous =	&(newList->m_head);
		newList -> m_head.m_previous =	NULL;
		newList -> m_tail.m_next =	NULL;
	}

	return newList;
}

void ListDestroy(List* _list)
{
	if(!_list)
	{
		return ;
	}
	
	while(_list->m_head.m_next != &_list->m_tail)
	{
		ListPopHead(_list, NULL);/*better to do free without use this function*/
	}
	free(_list);
}

ADTErr ListPushHead(List* _list, int _data)
{
	Node* newNode;

	if(! _list)
	{
		return ERR_UNINITIALIZED;
	}

	newNode = (Node*) malloc(sizeof(Node));
	if(newNode)
	{
		newNode->m_data =	_data;

		newNode->m_next =	_list->m_head.m_next;
		newNode->m_previous =	&_list->m_head;
		_list->m_head.m_next->m_previous =	newNode;
		_list->m_head.m_next =	newNode;


		return ERR_OK;
	}
	return ERR_ALLOCATION;

}

ADTErr ListPushTail(List* _list, int _data)
{
	Node* newNode;

	if(! _list)
	{
		return ERR_UNINITIALIZED;
	}

	if (_list->m_head.m_next == &_list->m_tail)
	{
		return ListPushHead(_list, _data);
	}

	newNode = (Node*) malloc(sizeof(Node));
	if(newNode)
	{
		newNode->m_data = _data;

		newNode -> m_next =	&(_list -> m_tail);
		newNode -> m_previous =	_list -> m_tail.m_previous;
		_list -> m_tail.m_previous -> m_next = newNode;
		_list -> m_tail.m_previous = newNode;

		return ERR_OK;
	}
	return ERR_ALLOCATION;
}

ADTErr ListPopHead(List* _list, int* _data)
{
	Node* removeNode;
	if(! _list)
	{
		return  ERR_UNINITIALIZED;
	}
	if( _list->m_head.m_next == &(_list->m_tail))
	{
		return ERR_UNDERFLOW;
	}

	 removeNode = _list -> m_head.m_next;
	 if(_data != NULL)
	{
		*_data = _list->m_head.m_next->m_data;
	}
	_list -> m_head.m_next -> m_next -> m_previous = &(_list -> m_head);
	_list -> m_head.m_next = _list -> m_head.m_next -> m_next;

	free(removeNode);
	return ERR_OK;

}

ADTErr ListPopTail(List* _list, int* _data)
{
	Node* removeNode;
	if(! _list)
	{
		return ERR_UNINITIALIZED;
	}
	if( _list->m_head.m_next == &(_list->m_tail))
	{
		return ERR_UNDERFLOW;
	}
	if (_list->m_head.m_next == &_list->m_tail)
	{
		return ListPopHead(_list, _data);
	}

	removeNode = _list -> m_tail.m_previous;
	if(_data != NULL)
	{
		*_data = _list -> m_tail.m_previous -> m_data;
	}
	_list->m_tail.m_previous->m_next = &_list->m_tail;
	_list->m_tail.m_previous = _list->m_tail.m_previous->m_previous;
	free(removeNode);
	return ERR_OK;

}

size_t	ListCountItems(List* _list)
{
	size_t count=0;
	Node* nextNode= _list->m_head.m_next;

	if (!_list)
	{
		return 0;
	}
	while(nextNode != &(_list->m_tail))
	{
		count++;
		nextNode = nextNode->m_next;
	}

	return count;
}

int 	ListIsEmpty(List* _list)
{ 
	if (!_list)
	{
		return 0;
	}
	return _list->m_head.m_next == &_list->m_tail;
}

void 	ListPrint(List* _list)
{
	Node* nextNode =_list->m_head.m_next;
	
	if (!_list)
	{
		return ;
	}
	
	while(nextNode != &_list->m_tail)
	{
		printf("%d  ", nextNode -> m_data);
		nextNode = nextNode->m_next;
	}
	printf("\n");
	
	

}