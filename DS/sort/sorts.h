#ifndef __SORTS_H__
#define __SORTS_H__
#include "vector.h"
#include "ADTErr.h"

ADTErr BubbleSort(Vector* _vec);
ADTErr ShakeSort(Vector* _vec);
ADTErr QuickSort(Vector* _vec, int _flag);
ADTErr InsertionSort(Vector* _vec);
ADTErr SelectionSort(Vector* _vec);
ADTErr MergeSort(Vector* _vec, int _flag);
ADTErr ShellSortByInser(Vector* _vec);

ADTErr CountingSort(Vector* _vec, int _maxNumber);
ADTErr RadixSort(Vector* _vec, int _nDigits);

#endif /*__SORTS_H__*/
