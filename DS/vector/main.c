#include"vector.h"

int main()
{
	enum ADTerr status;
	int size;
	int increase;
	int item;
	int menuChoice = 1;
	int flag = 0;
	Vector* controler = NULL;


	printf("%s\n","MENU" );
	printf("%s\n","-----------------------" );

	while(menuChoice)
	{	

		printf("--press 1 for create new empty Vector \n"
			"--press 2 for destroy array \n"	
			"--press 3 to add number\n"
			"--press 4 for remove last number \n"
			"-- press 5 to print vector\n"
			"--press 0 to exit\n");

		scanf("%d", &menuChoice);

		switch (menuChoice)
		{
			case 0 :
				VectorDestroy(controler);
				return 0;

			case 1 :
				if(!flag)
				{
					printf("%s\n","what is the size of your array: ");
					scanf("%d",&size);
					printf("%s\n","what is the increase block of your array: ");
					scanf("%d",&increase);
					controler = VectorCreate(size, increase);
					flag = 1;
					if(controler == NULL ){ printf("error Dcreate Function\n");return -1;}
				}
				else 
					printf("%s\n","delete the existing vector first" );
				break;

				case 2 :
					VectorDestroy(controler);
					flag = 0;
					break;

				case 3:
					printf("what number you want to add? \n");
					scanf("%d", &item);
				
					
					status = VectorAdd(controler, item);
					if(status != ERR_WELL ){printf( "ERROR add Function\n");return -1;}
					
					break;

				case 4:
					status = VectorDelete(controler,&item);
					if(status == ERR_WELL)
						printf("we have remove :%d\n",item);
					else	
						printf("%s\n","error Dremove Function" );
					break;

				case 5:
					VectorPrint(controler);
					break;

				default:
					break;


		}
	}


	return 0 ;
}