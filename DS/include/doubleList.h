#ifndef _DOUBLE_LINKED_LIST_H
#define _DOUBLE_LINKED_LIST_H
#include"ADTErr.h"


typedef struct List List;

List* ListCreate();
void ListDestroy(List* _list);

ADTErr ListPushHead(List* _list, int _data);
ADTErr ListPushTail(List* _list, int _data);

ADTErr ListPopHead(List* _list, int* _data);
ADTErr ListPopTail(List* _list, int* _data);

size_t ListCountItems(List* _list);
int ListIsEmpty(List* _list);

void ListPrint(List* _list);
#endif