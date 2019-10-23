#ifndef __SORTS_H__
#define __SORTS_H__
#include "vector.h"
#include "ADTErr.h"

ADTErr BubbleSort(Vector* _vec,int (*f)(int,int));
int sort(void* _elements, size_t _elementSize, size_t _size, int(*_less)(const void*, const void*));
#endif /*__SORTS_H__*/
