#ifndef __LIST_ITER_COMMUN_H__
#define __LIST_ITER_COMMUN_H__


typedef struct Node
{
	void* 			m_data;
	struct Node* 	m_next;
	struct Node* 	m_previous;
	
}Node;

struct List
{
	Node 			m_head;
	Node 			m_tail;
};

#endif