#include<stdlib.h>
#include"sorts.h"
#include "vector.h"
#include "ADTErr.h"
#include "stack.h"

#define IS_SWAPPED 0
#define UP 0
#define DOWN 1
#define CHECKPOINTER(X)		if(NULL == (X))	return ERR_UNINITIALIZED;
	

/*################STATIC FUNCTIONS########################*/
static int bubbleUp(Vector* _vec, int _begin,int _size, int _flag, int _flag2);
static void swapByIndex(Vector* _vec, int _index1, int _index2);
static int partition(Vector* _vec, size_t _begin, size_t _end);
static void QuickSortRec(Vector* _vec, size_t _begin, size_t _end);
static void QuickSortIter(Vector* _vec);
static int findMin(Vector* _vec, int _start, int size);
static void MergeSortRec(Vector* _vec, int* _resultArr,int _start, int _end);
static void Merge(Vector* _vec,int* _resultArr,int _start, int middle,int _end);
static void MergeSortIter(Vector* _vec, int* _resultArr);
static int min(int first, int second);
static  void shell(Vector* _vec, int _nItems);
static void CountingSortWithBase(Vector* _vec,int _maxNumber, int _divide,int _index);  
static void additionalFrequencties(int * range, int _maxNumber);
static void coyToOriginal(Vector* _vec,int* _Array,int _n);
/*########################################################*/


ADTErr BubbleSort(Vector* _vec)
{
	int i = 0;
	int nItems;
	ADTErr status;

	CHECKPOINTER(_vec);

	status = VectorItemsNum(_vec, &nItems);
	if( 0== nItems)
	{
		return ERR_EMPTY;
	}

	if(1 == nItems)
	{
		return ERR_OK;
	}
	for(i = 0; i < nItems ; i++)
	{
		if(IS_SWAPPED == bubbleUp(_vec, 0,nItems - i, UP, 0) )
		{
			break;
		}

	}
	return status;


}

/*same as bubbleSort but in one step it arrange fewer and greatest number*/
ADTErr ShakeSort(Vector* _vec)
{
	int i = 0;
	int nItems;
	ADTErr status;
	int st;

	CHECKPOINTER(_vec);

	status = VectorItemsNum(_vec, &nItems);
	if( 0== nItems)
	{
		return ERR_EMPTY;
	}

	if(1 == nItems)
	{
		return ERR_OK;
	}
	for(i ; i < nItems; i++)
	{
		if(IS_SWAPPED == bubbleUp(_vec, i,nItems - 1 - i, UP, 0) )
		{
			break;
		}
		st = bubbleUp(_vec, nItems - i ,i, DOWN, 0);
		if(IS_SWAPPED == st)
		{
			break;
		}
	}

	return ERR_OK;
}


ADTErr QuickSort(Vector* _vec, int _recOrIter)
{
	ADTErr status;
	int nItems;

	CHECKPOINTER(_vec);

	status = VectorItemsNum(_vec, &nItems);
	if( 0 == nItems)
	{
		return ERR_EMPTY;
	}

	if(1 == nItems)
	{
		return ERR_OK;
	}
	if(_recOrIter == 1)
	{
		QuickSortRec(_vec, 0, nItems);
	}
	else
	{
		QuickSortIter(_vec);
	}

	return status;
}


ADTErr InsertionSort(Vector* _vec)
{
	int size, last;

	CHECKPOINTER(_vec);

	VectorItemsNum(_vec, &size);
	if(0 == size)
	{
		return ERR_EMPTY;
	}

	last = 0;
	while(last < size)
	{
		bubbleUp(_vec, ++ last, 0, DOWN, 1);
	}
	return ERR_OK;
}




ADTErr SelectionSort(Vector* _vec)
{
	int size, i, posMin;

	CHECKPOINTER(_vec);

	VectorItemsNum(_vec, &size);
	if(0 == size)
	{
		return ERR_EMPTY;
	}

	for(i = 0; i < size - 1; ++i)
	{
		posMin = findMin(_vec, i, size);
		swapByIndex(_vec, posMin, i);
	}
	return ERR_OK;
}

ADTErr MergeSort(Vector* _vec, int _flag)
{
	int size;
	int* resultArr;

	CHECKPOINTER(_vec);

	VectorItemsNum(_vec, &size);
	if(0 == size)
	{
		return ERR_EMPTY;
	}

	resultArr = (int*) malloc(size * sizeof(int));
	CHECKPOINTER(resultArr);

	if(_flag == 1)
	{
		MergeSortRec(_vec, resultArr,0 , size - 1);
	}
	else
	{
		MergeSortIter(_vec, resultArr);
	}

	free(resultArr);
	return ERR_OK;
}

ADTErr ShellSortByInser(Vector* _vec)
{
	int nItems;

	CHECKPOINTER(_vec);

	VectorItemsNum(_vec, &nItems);
	if(0 == nItems)
	{
		return ERR_EMPTY;
	}

	if(nItems < 2 )
	{
		return ERR_OK;
	}

	shell(_vec, nItems);


}

ADTErr CountingSort(Vector* _vec,int _maxNumber)
{
	int index = 1;
	int temp = _maxNumber;

	CHECKPOINTER(_vec);

	while(temp)
	{
		index *= 10 ;
		temp /= 10;
	}

	CountingSortWithBase(_vec, _maxNumber, 1, index);    
	return ERR_OK;     
}

ADTErr RadixSort(Vector* _vec, int _nDigits)
{
	int i;
	int divide = 1;

	CHECKPOINTER(_vec);

	for(i = 1;i <= _nDigits; i++)
	{

		CountingSortWithBase(_vec, 9,divide,10);
		divide *= 10;
	}
	return ERR_OK;
}

/*########################STATIC FUNCTIONS##############################*/

/*this bubble implementation works for both ways*/
static int bubbleUp(Vector* _vec,int _begin ,int _size, int _flag, int _flag2)
{
	int i = 0, isSwapped = 0;
	int item1, item2;

	switch(_flag)
	{
		case UP:
			for(i = _begin; i < _size ; ++i)
			{
				VectorGet(_vec, i, &item1);
				VectorGet(_vec, i + 1, &item2);

				if(item1 > item2)
				{
					VectorSet(_vec, i, item2);
					VectorSet(_vec, i + 1, item1);

					isSwapped = 1;
				}
			}
			return isSwapped;
	

	case DOWN:
		for(i = _begin - 1 ; i > _size ; --i)
		{
			VectorGet(_vec,i, &item1);
			VectorGet(_vec, i - 1, &item2);

			if(item2 > item1)
			{
				VectorSet(_vec, i, item2);
				VectorSet(_vec, i - 1, item1);

				isSwapped = 1;
			}
			else if(_flag2 == 1 && item2 < item1)
			{
				break;
			}
		}
		return isSwapped;
	}
	
}


static void QuickSortRec(Vector* _vec, size_t _begin, size_t _end)
{
	int result;
	if(_begin >= _end)
	{
		return;
	}
	result = partition(_vec,_begin, _end);

	QuickSortRec(_vec, _begin, result -1);
	QuickSortRec(_vec, result + 1, _end);
}



static int partition(Vector* _vec, size_t _begin, size_t _end)
{
	int too_big_index = _begin + 1, too_small_index = _end - 1, pivot = _begin;
	int tmpBig, tmpSmall, tmpPivot;
	pivot = _begin;

	VectorGet(_vec, _begin +1 ,&tmpBig);
	VectorGet(_vec, _end - 1, &tmpSmall);
	VectorGet(_vec, _begin  ,&tmpPivot);

	while(too_big_index < too_small_index)
	{
		while(tmpBig <= tmpPivot && too_small_index != too_big_index)
		{
			++too_big_index;
			VectorGet(_vec,too_big_index, &tmpBig);
		}

		while(tmpSmall > tmpPivot)
		{
			--too_small_index;
			VectorGet(_vec, too_small_index, &tmpSmall);
		}
			/* change element of to left side of pivot*/
		if(too_big_index < too_small_index)
		{
			swapByIndex(_vec,too_big_index, too_small_index);
			VectorGet(_vec,too_big_index, &tmpBig);
			VectorGet(_vec, too_small_index, &tmpSmall);
		}

	}
	if(pivot < too_small_index)
	{
		swapByIndex(_vec, too_small_index, pivot);
	}
	return pivot;
}



static void swapByIndex(Vector* _vec, int _index1, int _index2)
{
	int first, second;

	VectorGet(_vec, _index1, &first);
	VectorGet(_vec, _index2, &second);

	VectorSet(_vec,_index1, second);
	VectorSet(_vec, _index2, first);
}


/*using stack to know with part of array we should do partition*/
static void QuickSortIter(Vector* _vec)
{
	int low = 0;
	int size;
	int pivotLocation;
	int end;
	int start;
	Stack* newStack;

	VectorItemsNum(_vec, &size);
	size--;

	newStack = StackCreate(size, size/2);
	if(NULL == newStack)
	{
		return;
	}

	StackPush(newStack, 0);
	StackPush(newStack,size + 1);

	while(StackIsEmpty(newStack) != 1)
	{
		StackPop(newStack, &end);
		StackPop(newStack, &start);

		if(end - start <= 2)
		{
			continue;
		}
		
		 pivotLocation = partition(_vec, start, end);

		 StackPush(newStack, pivotLocation + 1);
		 StackPush(newStack, end);

		 StackPush(newStack, start);
		 StackPush(newStack, pivotLocation );
	}

	free(newStack);
}


static int findMin(Vector* _vec, int _start, int size)
{
	int i ;
	int min;
	int index = _start;
	int temp;
	VectorGet(_vec, _start, &min);
	for(i = _start; i < size ; i++)
	{
		VectorGet(_vec, i, &temp);
		if(temp < min)
		{
			min = temp;
			index = i;
		}
	}
	return index;
}

static void MergeSortRec(Vector* _vec, int* _resultArr,int _start, int _end)
{
	int middle, size;
	if(_start >= _end)
	{
		return;
	}
	middle = (_start + _end)/ 2;

	MergeSortRec(_vec, _resultArr, _start, middle);
	MergeSortRec(_vec, _resultArr, middle + 1, _end);

	Merge(_vec, _resultArr, _start,  middle, _end);

}

static void Merge(Vector* _vec,int* _resultArr,int _start, int _middle,int _end)
{
	int i , j, k = _start;
	int first, second;
	int n1 = _middle - _start + 1 ;
	int n2 = _end - _middle ;
	i = 0;
	j = 0;
	while(i < n1 && j < n2)
	{
		VectorGet(_vec, i+ _start, &first);
		VectorGet(_vec, _middle + j + 1, &second);
		if(first<= second)
		{
			_resultArr[k] = first;
			++i;
		}
		else
		{
			_resultArr[k] = second;
			++j;
		}
		k++;
	}
	while(i < n1)
	{
		VectorGet(_vec, i+ _start, &first);
		_resultArr[k] = first;
		i++;
		k++;
	}

	while(j < n2)
	{
		VectorGet(_vec, _middle + j + 1, &second);
		_resultArr[k] = second;
		j++;
		k++;
	}

	for(i = _start; i <= _end; ++i)
	{
		VectorSet(_vec, i,_resultArr[i]);
	}
}


static void MergeSortIter(Vector* _vec, int* _resultArr)
{
	int curr_size, mid;
	int left_start, right_end;
	int nItems;

	VectorItemsNum(_vec, &nItems);

	for (curr_size = 1; curr_size <= nItems - 1; curr_size *= 2)
	{
		for(left_start = 0; left_start < nItems - 1; left_start += 2 * curr_size)
		{
			right_end = min(left_start + 2 * curr_size - 1, nItems-1);
			mid = (left_start + right_end)/2;

			Merge(_vec, _resultArr, left_start, mid, right_end);
		}
	}
}

static int min(int first, int second)
{
	return first < second ? first:second;
}


static void shell(Vector* _vec, int _nItems)
{
	int gap = _nItems / 2;
	int i, num1, num2, j;

	while(gap > 0)
	{
		i = gap;
		while (i < _nItems)
		{
			j = i;
			while(j >= gap )
			{
				VectorGet(_vec, j, &num1);
				VectorGet(_vec, j - gap, &num2);

				if(num1 <= num2)
				{
					swapByIndex(_vec, j, j - gap);
					j = j - gap;
				}
				else
				{
					break;
				}
			}
			i++;
		}

		gap /= 2; 
	}
}


static void CountingSortWithBase(Vector* _vec,int _maxNumber, int _divide,int _index)
{
	int n, i, num, tempNum;
	int * tempArray;

	int* range = (int*) calloc(_maxNumber + 1, sizeof(int));
	CHECKPOINTER(range);

	VectorItemsNum(_vec, &n);

	tempArray = (int*) malloc(n * sizeof(int));
	if(NULL == tempArray)
	{
		free(range);
		return;
	}

	for(i = 0; i < n; i++)
	{
		VectorGet(_vec, i, &num);
		num = (num / _divide) % _index;
		range[num]++;
	}

	additionalFrequencties(range, _maxNumber);

	for(i = n - 1; i >= 0; --i)
	{
		VectorGet(_vec, i, &num);
		tempNum = (num / _divide) % _index;
		tempArray[ range[tempNum] - 1] = num;
		range[tempNum]--;
	}

	coyToOriginal(_vec, tempArray, n);

}
static void additionalFrequencties(int * range, int _maxNumber)
{
	int i;
	for ( i = 1; i < _maxNumber + 1; ++i)
	{
		range[i] += range[i - 1];
	}
}

static void coyToOriginal(Vector* _vec,int* _Array,int _n)
{
	int i;
	for(i = 0; i < _n;i++)
	{
		VectorSet(_vec, i, _Array[i]);
	}
}
