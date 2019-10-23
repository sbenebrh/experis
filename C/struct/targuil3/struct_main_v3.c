#include"struct_funcs_v3.h"

int main()
{
	enum DAStatus status;
	int size;
	int numberIncreaseBlocks;
	int data;
	int menuChoice = 1;
	DA * controler = NULL;

	printf("%s\n","MENU" );
	printf("%s\n","-----------------------" );

	while(menuChoice)
	{	

		printf("--press 1 for create new empty array \n"
			"--press 2 for destroy array \n"	
			"--press 3 to add number\n"
			"--press 4 for remove last number \n"
			"--press 0 to exit\n");

		scanf("%d", &menuChoice);
		switch (menuChoice)
		{
			case 0 :
				Ddestroy(controler);
				return 0;
				
			case 1 :
				printf("%s\n","what is the size of your array: ");
				scanf("%d",&size);
				printf("%s\n","what is the increase block of your array: ");
				scanf("%d",&numberIncreaseBlocks);
				controler = Dcreate(size, numberIncreaseBlocks);
				if(controler == NULL || NULL == controler){ printf("error Dcreate Function\n");return -1;}
				break;
			case 2 :
				Ddestroy(controler);
				break;
			case 3:
				printf("what number you want to add? \n");
				scanf("%d", &data);
			
				
				status = Dadd(controler, data);
				if(status != WELL ){printf( "ERROR Dadd Function\n");return -1;}
				
				print(controler);
				break;
			case 4:
				status = Dremove(controler,&data);
				if(status == WELL)
					printf("we have remove :%d\n",data);
				else	
					printf("%s\n","error Dremove Function" );
				break;
			case 5:

				printf("what number you want to find? \n");
				scanf("%d", &data);
			
				if((status = Dfind(controler, data)) == WELL)
					printf("%s\n","your number is in the array" );
				else
					printf("%s\n","your number is not the array" );
				break;
				}

	}



	return 0;
}
