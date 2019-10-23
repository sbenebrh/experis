#include<stdio.h>
#include"func.h"
#include<stdlib.h>
#include <math.h>

void createRandomArray(int * _arr, int *_size)
{
	int i;

	for (i = 0; i < *_size; i++)
	{
		_arr[i] = rand() % 5;
	}

}
void findNumber(int myArr[], int * sizeOfArray)
{
	int choosenNumber;
	BubbleSort(myArr, *sizeOfArray);

	printf("please enter a number to check in a binary search tree: ");
	scanf_s("%d", &choosenNumber);


	if (BinarySearch(myArr, *sizeOfArray, choosenNumber))
	{
		printf("your number is in the array\n");
	}
	else
	{
		printf("your number is NOT in the array\n");
	}
}

void addNumber(int * _arr, int * sizeOfArray)
{
	int addNumber;
	int lastPosition;
	lastPosition = *sizeOfArray;

	printf("enter the number you want to add: \n");
	scanf_s("%d", &addNumber);

	*sizeOfArray += ceil(1.2 * sizeof(int));
	_arr = (int *)realloc(_arr, *sizeOfArray);

	_arr[lastPosition + 1] = addNumber;
}

int main()
{
	int * myArr = NULL;
	int sizeOfArray ;
	int  menuChoice = 1;
	printf("hello! welcome\n What do you want to do? \n");
	while (menuChoice)
	{
		printf("--press 1 for create new array \n"
			"--press 2 for find number \n"
			"--press 3 to add number\n"
			"--press 4 to exit\n");
		scanf_s("%d", &menuChoice);
		switch (menuChoice)
		{
		case 0:
			return 0;
			break;
		case 1:
			free(myArr);
			printf("please enter the size of the array: ");
			scanf_s("%d", &sizeOfArray);
			myArr = (int*)malloc(sizeOfArray * sizeof(int));
			if (!myArr)
			{
				printf("error");
				return -1;

			}
			createRandomArray(myArr,&sizeOfArray);

			break;
		case 2:
			findNumber(myArr, &sizeOfArray);
			break;
		case 3:
			addNumber(myArr, &sizeOfArray);
			break;
		default:
			return ERR_CHOICE;

		}
	}

	return 0;

}




/* menu
printf("please enter the size of the array: ");
scanf("%d", &sizeOfArray);
myArr = malloc(sizeOfArray * sizeof(int));


createRandomArray(myArr, sizeOfArray);

BubbleSort(myArr, sizeOfArray);

printf("please enter a number to check in a binary search tree: ");
scanf("%d", &choosenNumber);


if(BinarySearch(myArr, sizeOfArray, choosenNumber))
{
printf("your number is in the array\n");
}
else
{
printf("your number is NOT in the array\n");
}
*/


