#include<stdio.h>
#include <math.h>
#include<stdlib.h>
#define ERR_CHOICE -3
#define NOT_IN_THE_ARRAY -4
#define IS_SWAPPED 1






void createRandomArray(int * _arr, int _size)
{
	int i;

	for (i = 0; i < _size; i++)
	{
		_arr[i] = rand() % 5;
	}

}

void destroyArray(int *_arr,int * size)
{
	if(_arr)
	{
		free(_arr);
		*size = 0;
	}
}

int checkNullArray(int _arr[])
{
	if(_arr == NULL)
	{
		printf("the array is empty");
		return 0;
	}
	return 1;

}

void swap(int* _firstNumber,int*  _secondNumber)
{
	int  temp = *_firstNumber;
	*_firstNumber = *_secondNumber;
	*_secondNumber = temp;
}

int BubbleUp(int  _arr[], int _size)
{
	int i = 0;
	int isSwapped = 0;
	
	for(i; i<_size;i++)
	{
		if(_arr[i] > _arr[i+1])
		{
			swap( & _arr[i], & _arr[i+1]);
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

	for(i; i < _size; i++)
	{
		if(IS_SWAPPED != BubbleUp(&_arr[0],  _size-i))
		{
			break;
		}
	}

	printf("the sorted array is : ");
	for(j;j<_size;j++)
	{
		printf("%d ",_arr[j]);
	}
	printf("\n");
}


int BinarySearch(int _array[], int _sizeOfArray, int _num)
{
	int first = 0;
	int last = _sizeOfArray -1;
	int middle ;
	checkNullArray( _array);
	

	while(first <= last)
	{
		middle = (first + last)/2;
		
		if(_num > _array[middle])
		{
			first = middle+1;
		}
		else if (_num == _array[middle] || _num == _array[last] ||  _num == _array[first])
		{
			return middle + 1 ;
		}
		else
		{
			last = middle-1;
		}
	}
	
	return 0;
}
int findNumber(int myArr[], int  sizeOfArray,int _numberToFind)
{
	
	BubbleSort(myArr, sizeOfArray);

	if (BinarySearch(myArr, sizeOfArray, _numberToFind))
	{
		return 1;
	}
	else
	{
		return NOT_IN_THE_ARRAY;
	}
}

int addNumber(int ** _arr, int * _sizeOfArray,int _number)
{

	
	*_arr = (int *)realloc(*_arr, (*_sizeOfArray+1)*sizeof(int));
	*_sizeOfArray++;

	**(_arr+*_sizeOfArray - 1) = _number;
	return 1;
	
}

void removeNumber(int * _arr, int * _size)
{	
	BubbleSort(_arr, * _size);

	*_size -= sizeof(int); 
	_arr = (int *)realloc(_arr,*_size );	
}
