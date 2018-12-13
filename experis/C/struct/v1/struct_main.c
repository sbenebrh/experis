#include"struct_funcs.h"

int main()
{
	int * DArrayPtr = NULL;
	int DSize = 10;
	int DNumOfElement;
	int increaseBlock = 10;
	int menuChoice = 1;
	int status;
	int data;
	
	
	printf("welcome what do you want to do? \n");
	while(menuChoice)
	{
		printf("\n============================================ \n"
			"--press 1 for create new empty array \n"
			"--press 2 for destroy array \n"	
			"--press 3 to add number\n"
			"--press 4 for remove number \n"
			"--press 0 to exit\n"
			"============================================ \n");
		scanf("%d", &menuChoice);
		switch (menuChoice)
		{
			case 0 :
				free(DArrayPtr);
				return 0;
			case 1 :
				if(! (DArrayPtr = Dcreate(DSize, & DNumOfElement)))
				{
					return SEGMENTATION_FAULT;
				}
				break;

			case 2 :
				Ddestroy(DArrayPtr);
				DArrayPtr = NULL;
				break;

			case 3:
				printf("what number you want to add? \n");
				scanf("%d", &data);
		
				
				status = Dadd(& DArrayPtr, data, & DSize, & DNumOfElement, increaseBlock);
				if(status == SEGMENTATION_FAULT)
				{
					return SEGMENTATION_FAULT;
				}
				else if(status == ERR_INPUT)
				{
					return ERR_INPUT;
				}
				else if(status == ERR_INCREASE)
				{
					return ERR_INCREASE;
				}

				print(DArrayPtr, DNumOfElement);
				break;
			case 4:
				
				if (! (status = Dremove(DArrayPtr, &data, DSize, &DNumOfElement)))
				{
					return SEGMENTATION_FAULT;
				}
				else if(status == ERR_UNDERFLOW)
				{
					return ERR_UNDERFLOW;
				}
				printf("we have just deleted %d \n",data);
				print(DArrayPtr, DNumOfElement);

		}
	}
	return 0;
}	
