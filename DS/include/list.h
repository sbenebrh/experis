#ifndef _LIST_H
#define _LIST_H

struct Person
{
	int m_id;
	char m_name[128];
	int m_age;
	struct Person* m_next;
};
typedef struct Person Person;
/**
* @function: ListInsertHead
* @brief add the person to the head
* 
*
* @param * _head : pointer to the begining of the list
* @param _p : the person managed by user we want to add 
* 
*
* @return pointer to the begining of the list

* @errors: return the head if the person is not initialize
*		   
**/
Person* ListInsertHead(Person* _head, Person* _p);

/**
* @function: ListRemoveHead
* @brief remove the person at the head
* 
*
* @param * _head : pointer to the begining of the list
* @param _p : the person managed by user we want to remove 
* 
*
* @return pointer to the begining of the list

* @errors: return the NULL if the list is empty
*		   
**/
Person* ListRemoveHead(Person* _head, Person** _p);

/**
* @function: ListInsertByKey
* @brief add the person at the good position in order to get a sorted list
* 
*
* @param  _head : pointer to the begining of the list
* @param _key : the primary key of the person
* @param _p : the person managed by user we want to add 
* 
*
* @return pointer to the begining of the list

* @errors: return the head if the person is not initialize
* 		return the head if the key and the id person are different
*		   
**/
Person* ListInsertByKey(Person* _head,int _key, Person* _p);
/**
* @function: ListInsertByKeyRec
* @brief add the person at the good position in order to get a sorted list using recursion
* 
*
* @param  _head : pointer to the begining of the list
* @param _key : the primary key of the person
* @param _p : the person managed by user we want to add 
* 
*
* @return pointer to the begining of the list

* @errors: return the head if the person is not initialize
* 		return the head if the key and the id person are different
*		   
**/
Person* ListInsertByKeyRec(Person* _head,int _key, Person* _p);

/**
* @function: ListRemoveByKey
* @brief remove a specific person according to id
* 
*
* @param  _head : pointer to the begining of the list
* @param _key : the primary key of the person
* @param _p : the person managed by user we want to remove 
* 
*
* @return pointer to the begining of the list

* @errors: return the NULL if the list is empty
		return the head if the key and the id person are different
		return head if there is not such a person in the list
*		   
**/
Person* ListRemoveByKey(Person* _head,int _key, Person** _p);

/**
* @function: ListRemoveByKey
* @brief remove a specific person according to id using recursion
* 
*
* @param  _head : pointer to the begining of the list
* @param _key : the primary key of the person
* @param _p : the person managed by user we want to remove 
* 
*
* @return pointer to the begining of the list

* @errors: return the NULL if the list is empty
		return the head if the key and the id person are different
*		return head if there is not such a person in the list  
**/
Person* ListRemoveByKeyRec(Person* _head,int _key, Person** _p);
/**
* @function: PrintList
* @brief print every person of the list(id, name, age)
* 
*
* @param  _head : pointer to the begining of the list
* 
* 
*
* @return the number of person in the list

* @errors: return is empty is the list is empty
**/
int PrintList(Person* _head);

#endif
