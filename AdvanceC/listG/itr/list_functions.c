#include"list_functions.h"
#include"list_itr.h"
#include"../list.h"

#define CHECKNULLPOINTER(X)		if(NULL == (X)) return NULL;
#define CHECKPOINTER(X)			if(NULL == (X)) return 0;
#define FALSE	0
#define TRUE	!FALSE

ListItr ListItr_FindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	CHECKNULLPOINTER(_begin);
	CHECKNULLPOINTER(_end);
	if(_predicate != NULL)
	{
		while(_begin != _end )
		{
			if(_predicate(_begin, _context) != 0)
			{
				return _begin;
			}
			_begin = ListItr_Next(_begin);
		}
		return _begin;
	}
	return _end;
}

size_t ListItr_CountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	size_t count = 0;
	CHECKPOINTER(_begin);
	CHECKPOINTER(_end);

	if(_predicate != NULL)
	{
		while(_begin != _end)
		{
			if(_predicate(_begin, _context) != 0)
			{
				count++;
			}
			_begin = ListItr_Next(_begin);
		}
	}
	return count;
}

ListItr ListItr_ForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context)
{
	if(NULL == _begin || _end == NULL)
	{
		return NULL;
	}

	if(_action != NULL)
	{
		while(_begin != _end)
		{
			if(_action(_begin, _context) == 0)
			{
				break;
			}
			_begin = ListItr_Next(_begin);
		}
		return _begin;
	}
	return _end;
	
}

List* ListItr_Cut(ListItr _begin, ListItr _end)
{
	List* cutList = NULL;
	ListItr tail;
	CHECKNULLPOINTER(_begin);
	CHECKNULLPOINTER(_end);

	cutList = List_Create();
	if(NULL == cutList)
	{
		return cutList;
	}
	tail = ListItr_End(cutList);
	while(_begin !=_end)
	{
		_begin = ListItr_Next(_begin);
		ListItr_InsertBefore(tail, ListItr_Remove(ListItr_Prev(_begin)));

	}

	return cutList;
}


/*########################STATIC##########*/


/*TODO create unique fonction for every one*/