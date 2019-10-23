#include<stdio.h>
#include"list.h"
enum status
{
	NOT_FOUND_INSERT_TO_BEGIN,
	FOUND,
	NOT_FOUND_INSERT_TO_PLACE,
	FOUND_REMOVE_BEGIN,
	FOUND_REMOVE_TO_PLACE,
	NOT_FOUND,
	REMOVE_LAST

};
/*TODO add everywhere check function on pointers
change recursion to do it more efficient*/
Person* FindPlaceToInsert(Person* _head, int _key, int* _status)
{
	
	if (NULL == _head || _head -> m_id >_key)
	{
		*_status=NOT_FOUND_INSERT_TO_BEGIN;
		return _head;
	}

	
	while( NULL != _head -> m_next && _head -> m_next -> m_id <=_key){
		_head =_head -> m_next;
	}

	if (_head->m_id == _key)
	{
		*_status= FOUND;
		return _head;
	}

	*_status= NOT_FOUND_INSERT_TO_PLACE;
	return _head;
}


Person* ListInsertHead(Person* _head, Person* _p)
{
if ( NULL == _p )
	{
		return _head;
	}
	_p -> m_next =_head -> m_next;
	_head -> m_next= _p;

	return _head;
}

Person* ListInsertByKey(Person* _head,int _key, Person* _p)
{

	Person* tmp;
	int status;
	
	if (_key != _p->m_id ||  NULL == _p)
	{
		return _head;
	}


	tmp=FindPlaceToInsert(_head,_key,&status);

	if (status == FOUND)  
	{
		return _head; 
	}

	if (status == NOT_FOUND_INSERT_TO_BEGIN)
	{
		return ListInsertHead(_head, _p);
	}

	
	_p -> m_next = tmp -> m_next;
	tmp -> m_next =_p;

	return _head;
}

Person* ListInsertByKeyRec(Person* _head,int _key, Person* _p)
	
if ( _key == _head->m_id || _key<=0) 
	{
		return _head;
	}
	
	if (NULL == _head->m_next || _head->m_next->m_id>_key)
	{
		_p->m_next=_head->m_next;
		_head->m_next=_p;
	}
	else
	{
		_head -> m_next = ListInsertByKeyRec(_head->m_next,_key,_p);
	}
 	 
 	 return _head;
	
}

Person* ListRemoveHead(Person* _head, Person** _p)
{
	if(_head || _p)
	{
		*_p = _head -> m_next;
		_head -> m_next = _head -> m_next -> m_next;
	}
	return _head;
}

Person* FindPlaceToRemove(Person* _head, int _key,int* _status)
{
	if (_head->m_id == _key)
	{
		*_status = FOUND_REMOVE_BEGIN;
		return _head;
	}

	while(_head -> m_next != NULL && _head -> m_next -> m_id != _key){
		_head = _head -> m_next;
	}

	if(_head->m_next != NULL ){
		*_status = FOUND_REMOVE_TO_PLACE;
		return _head;
	}
	if(_head -> m_next == NULL && _head -> m_id == _key)
	{
		*_status = REMOVE_LAST;
		return _head;
	}
	*_status = NOT_FOUND;
	return _head;
}

Person* ListRemoveByKey(Person* _head,int _key, Person** _p)
{
	
	Person* removedPerson;
	int status;

	if (NULL == _head )
	{
		return _head;
	}

	removedPerson = FindPlaceToRemove(_head,_key,&status);

	if (status == FOUND_REMOVE_BEGIN)
	{
		return ListRemoveHead(_head,_p);
	}
	
	if(status == FOUND_REMOVE_TO_PLACE && tmp -> m_next != NULL){

		*_p = tmp -> m_next;
		tmp -> m_next = tmp -> m_next -> m_next;
	}
	else if (status == REMOVE_LAST)
	{
		*_p = tmp;
		tmp  = NULL;
	}


	return _head;

}

Person* ListRemoveByKeyRec(Person* _head,int _key, Person* *_p)
{
	if(!_head)
	{
		return NULL;
	}
	if(_head -> m_id == _key)
	{
		*_p = _head;
		_head = _head -> m_next;
		return _head;
	}
	_head ->m_next = ListRemoveByKeyRec(_head -> m_next, _key, _p);
	return _head;

}
int PrintList(Person* _head)
{
	int count=0;  
	Person* tmp;
	if (NULL == _head)
	{
		printf("\n\nthe list is empty\n");
		return count;
	}
	printf("\n\n\nPERSONS:\n\n");
	for ( tmp=_head -> m_next ; tmp != NULL ; tmp=tmp->m_next)
	{
		printf("id: %d\nname: %s\nage: %d\n\n\n",tmp->m_id,tmp->m_name,tmp->m_age);
		count++;
	}
 
	return count;
}
		
void FlipList(Person* _head)
{
	Person* pers;
	if(!_head || ! _head -> m_next)
	{
		return _head;
	}
	pers = FlipList(_head -> m_next);

	_head -> m_next -> m_next = _head;
	_head -> m_next = NULL;

	return pers;
}