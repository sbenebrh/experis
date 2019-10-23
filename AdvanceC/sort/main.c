#include<stdio.h>
#include <string.h>
#include"sorts.h"
#include"vector.h"

int SortMin(const void* _a, const void* _b)
{
	return *(char*)_a > *(char*)_b;
}

int SortMax(int _a, int _b)
{
	return _a < _b;
}

int SortLastMax(int _a, int _b)
{
	return _a % 10 < _b%10;
}

int SortLastMin(int _a, int _b)
{
	return _a % 10 > _b%10;
}

int SortSumDigit(int _a, int _b)
{
	int resulta = 0;
	int resultb = 0;
	if((_a / 10) == 0)
	{
		resulta = _a;
		_a = 0;
	}
	if((_b / 10) == 0)
	{
		resultb = _b;
		_b = 0;
	}
	while(_a)
	{
		resulta += _a%10;
		_a/= 10;
	}
	while(_b)
	{
		resultb += _b%10;
		_b/=10;
		
	}

	return resulta >= resultb;
}


typedef int(*Sort)(int, int);



int main()
{

	int i;
	int arr[5] = { 6, 21, 3, 17, 9};
	char arr2[5] = {'c','a','g','b','d' };
	sort(arr2,sizeof(char), 4, SortMin);
	for(i = 0; i < 5; ++i)
	{ 
		printf("%c\t",arr2[i]);
	}
	printf("\n");
	

}