#include<stdio.h>
#include"func.h"
#define IS_SWAPPED 1

int checkNullArray(int _arr[])
{
	if (_arr == NULL)
	{
		printf("the array is empty");
		return 0;
	}
	return 1;

}

void swap(int* _firstNumber, int*  _secondNumber)
{
	int  temp = *_firstNumber;
	*_firstNumber = *_secondNumber;
	*_secondNumber = temp;
}

int BubbleUp(int  _arr[], int _size)
{
	int i = 0;
	int isSwapped = 0;

	for (i; i<_size; i++)
	{
		if (_arr[i] > _arr[i + 1])
		{
			swap(&_arr[i], &_arr[i + 1]);
			isSwapped = 1;
		}
	}
	return isSwapped;
}

void BubbleSort(int _arr[], int _size)
{
	int i = 0;
	int j = 0;


	checkNullArray(_arr);

	for (i; i < _size; i++)
	{
		if (IS_SWAPPED != BubbleUp(&_arr[0], _size - i))
		{
			break;
		}
	}
}


int BinarySearch(int _array[], int _sizeOfArray, int _num)
{
	int first = 0;
	int last = _sizeOfArray - 1;
	int middle;
	checkNullArray(_array);


	while (first <= last)
	{
		middle = (first + last) / 2;

		if (_num > _array[middle])
		{
			first = middle + 1;
		}
		else if (_num == _array[middle] || _num == _array[last] || _num == _array[first])
		{
			return middle + 1;
		}
		else
		{
			last = middle - 1;
		}
	}

	return 0;
}




