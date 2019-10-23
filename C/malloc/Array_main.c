#include<stdio.h>
#include"Array_funcs.h"
#include<stdlib.h>


#define ERR_CHOICE -3
#define NOT_IN_THE_ARRAY -4
#define IS_SWAPPED 1




int main()
{
	int * myArr = NULL;
	int sizeOfArray ;
	int  menuChoice = 1;
	int result;
	int addedNumber, status;
	int choosenNumber;

	printf("hello! welcome\n What do you want to do? \n");
	while (menuChoice)
	{
		printf("--press 1 for create new array \n"
			"--press 2 for destroy array \n"
			"--press 3 for find number \n"	
			"--press 4 to add number\n"
			"--press 5 for remove last number \n"
			"--press 6 to exit\n");
		scanf("%d", &menuChoice);
		switch (menuChoice)
		{
		case 6:
			return 0;
			break;
		case 1:
			printf("please enter the size of the array: ");
			scanf("%d", &sizeOfArray);
			myArr = (int*)malloc(sizeOfArray * sizeof(int));
			if (!myArr)
			{
				printf("error");
				return -1;

			}
			createRandomArray(myArr,sizeOfArray);

			break;
		case 2:
			destroyArray(myArr,&sizeOfArray);
			break;
		case 3:
			printf("please enter a number to check in a binary search tree: ");
			scanf("%d", &choosenNumber);

			result = findNumber(myArr, sizeOfArray,choosenNumber);
			if(result == NOT_IN_THE_ARRAY)
				{printf("not in the array");}
			else
				{printf("in the array");}
			break;
		case 4:
			printf("enter the number you want to add: \n");
			scanf("%d", &addedNumber);
			status = addNumber(&myArr, &sizeOfArray, addedNumber);
			break;
		case 5:
			removeNumber(myArr,&sizeOfArray);
			break;
		
		default:
			return ERR_CHOICE;

		}
	}

	return 0;

}
