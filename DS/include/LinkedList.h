#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H
#include"ADTErr.h"

typedef struct LinkedList LinkedList;
LinkedList* ListCreate();
void ListDestroy(LinkedList* _list);
ADTErr ListEnqueue(LinkedList* _list, int _item);
ADTErr ListDequeue(LinkedList* _list, int* _item);
int ListIsEmpty(LinkedList* _list);

















#endif /*_LINKEDLIST_H*/
