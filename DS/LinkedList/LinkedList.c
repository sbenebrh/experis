#include<stdio.h>
#include<stdlib.h>
#include"LinkedList.h"
#include"ADTErr.h"

#define HEAD(X)  ((X) -> m_head)
#define TAIL(X)  ((X) -> m_tail)
#define NEXT(X)	 ((X) -> m_node)

typedef struct Node
{
	int 		    m_value;
	struct Node* 	m_node;
}Node;

struct LinkedList
{
	Node*		  m_head;
	Node* 		  m_tail;
};

Node * createNode(int _data){
  Node * newNode = malloc(sizeof(Node));
  if (!newNode) {
    return NULL;
  }
  newNode->m_value = _data;
  newNode->m_node = NULL;
  return newNode;
}

LinkedList* ListCreate()
{
	LinkedList* newList = (LinkedList*) malloc(sizeof(LinkedList));
	if(newList) 
	{
		HEAD(newList) = NULL;
		TAIL(newList) =NULL;
	}
	return newList;
}

void ListDestroy(LinkedList* _list)
{
	while(HEAD(_list) != TAIL(_list))
		{
			ListDequeue(_list, NULL);
		}
	free(_list);
}
		
	
ADTErr ListEnqueue(LinkedList* _list, int _item)
{
	ADTErr status = ERR_OK;
	Node* current = NULL;
	if(_list)
	{
		if(HEAD(_list) == NULL)
		{ 
			HEAD(_list) = createNode(_item);
			TAIL(_list) = HEAD(_list);
		}
		else
		{
			current = TAIL(_list);
			NEXT(current) = createNode(_item);
			if(NEXT(current))
				TAIL(_list) = NEXT(current);
			else status = ERR_ALLOCATION;
		}
	}
	else status = ERR_ALLOCATION;
	
	return status;
}	


ADTErr ListDequeue(LinkedList* _list, int* _item)
{
	Node* next;
	ADTErr status = ERR_OK;
	if(_list)
	{
		if(HEAD(_list))
		{
			*_item = NEXT(HEAD(_list)) -> m_value;
			next = NEXT(NEXT(HEAD(_list)));
			free(NEXT(HEAD(_list)));
			NEXT(HEAD(_list)) = next;
		}
		else status = ERR_ALLOCATION;
		
	}
	else status = ERR_ALLOCATION;
	
	return status;
}	

int ListIsEmpty(LinkedList* _list)
{


	 if(_list)
	 	return !HEAD(_list);
	 return -1;
	 
}
