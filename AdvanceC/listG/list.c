#include<stdlib.h>
#include"commun.h"
#include"list.h"

#define CHECKPOINTER(X)		if(NULL == (X)) return LIST_UNINITIALIZED_ERROR;
#define CHECKNULLELEMENT(X)	if(NULL == (X)) return LIST_NULL_ELEMENT_ERROR;


/*###########STATICS DECLARATIONS###*/
static void		InitialList(List* _list);
static void 	destroyInsideElement(List* _pList,void (*_elementDestroy)(void* _item));
static void		InsertElement(Node* _left, Node* _right, Node* _node, void* _item);
static void 	remove(Node* _right, Node* _node);
static int 		IsEmptyList(const List* _list);
/*#################################*/
List* List_Create(void)
{
	List* newList = (List*) malloc(sizeof(List));
	if(newList)
	{
		InitialList(newList);
	}

	return newList;
}

void List_Destroy(List** _pList, void (*_elementDestroy)(void* _item))
{
	if(_pList)
	{
		if(*_pList)
		{
			destroyInsideElement(*_pList,(*_elementDestroy));

			free(*_pList);
			*_pList = NULL;
		}
	}
}


List_Result List_PushHead(List* _list, void* _item)
{
	Node* newNode;

	CHECKPOINTER(_list);
	CHECKNULLELEMENT(_list);

	newNode = (Node*) malloc(sizeof(Node));
	if(newNode)
	{
		InsertElement( _list->m_tail.m_previous, &(_list->m_tail),newNode, _item);
		return LIST_SUCCESS;
	}

	return LIST_ALLOCATION_ERROR;

}

List_Result List_PushTail(List* _list, void* _item)
{
	Node* newNode;

	CHECKPOINTER(_list);
	CHECKNULLELEMENT(_item);

	if (IsEmptyList(_list))
	{
		return List_PushHead(_list, _item);
	}

	newNode = (Node*) malloc(sizeof(Node));
	if(newNode)
	{
		InsertElement( _list->m_tail.m_previous, &(_list->m_tail),newNode, _item);
		return LIST_SUCCESS;
	}

	return LIST_ALLOCATION_ERROR;
}

List_Result List_PopHead(List* _list, void** _pItem)
{
	CHECKPOINTER(_list);
	CHECKNULLELEMENT(_pItem);

	if(IsEmptyList(_list) == 1)
	{
		return LIST_EMPTY_ERROR;
	}

	*_pItem = (_list -> m_head.m_next) -> m_data;

	(_list -> m_head.m_next) -> m_data = NULL;
	
	_list ->m_head.m_next -> m_next = &(_list -> m_head);
	_list -> m_head.m_next = _list -> m_head.m_next -> m_next;
	/*remove((_list -> m_head.m_next)-> m_next,  _list -> m_head.m_next);*/

	free( _list -> m_head.m_next);
	return LIST_SUCCESS;


}

List_Result List_PopTail(List* _list, void** _pItem)
{

	CHECKPOINTER(_list);
	CHECKNULLELEMENT(_pItem);

	if(IsEmptyList(_list) == 1)
	{
		return LIST_EMPTY_ERROR;
	}

	*_pItem = (_list -> m_tail.m_previous) -> m_data;
	(_list->m_tail.m_previous)->m_data = NULL;

	remove(&(_list->m_tail),  _list->m_tail.m_previous);

	free(_list->m_tail.m_previous);
	return LIST_SUCCESS;
}


size_t List_Size(const List* _list)
{
	size_t count = 0;
	Node* nextNode;
	if(NULL == _list)
	{
		return 0;
	}
	if(IsEmptyList(_list) == 1)
	{
		return 0;
	}

	nextNode = _list->m_head.m_next;

	while(nextNode != &(_list->m_tail))
	{
		count++;
		nextNode = nextNode->m_next;
	}

	return count;
}


/*#####################################################*/

static void	InitialList(List* _list)
{
	_list -> m_head.m_next = &(_list -> m_tail);
	_list -> m_tail.m_previous = &(_list -> m_head);
	_list -> m_head.m_previous = &(_list -> m_head);
	_list -> m_tail.m_next = &(_list -> m_tail);
}

static void destroyInsideElement(List* _list,void (*_elementDestroy)(void* _item))
{
	Node* tmp ;

	tmp = ((_list)->m_head).m_next;

	while(tmp != & ((_list)->m_tail) )
	{
		if (_elementDestroy)
		{
			_elementDestroy(tmp->m_data);
		}
		tmp = tmp->m_next;
		free(tmp->m_previous);
	}
}

static void InsertElement(Node* _left, Node* _right,Node* _node, void* _item)
{
	_node -> m_data =	_item;
	_node -> m_previous = _left;
	_node -> m_next = _right;
	_left -> m_next = _node;
	_right -> m_previous = _node;
}

static void remove(Node* _right, Node* _node) 
{
	_node -> m_previous -> m_next = _node -> m_next;
	_node -> m_next -> m_previous = _node -> m_previous;
	_node -> m_next	=  NULL;
	_node -> m_previous	=  NULL;
}

static int 		IsEmptyList(const List* _list)
{
	return _list->m_head.m_next == &_list->m_tail;
}


