#include<stdio.h>
#include<stdlib.h>
#include"bits.h"

typedef int (* bitFunc)( bitMap*, size_t);

int operateBitFunc(bitFunc f ,bitMap * _bm, size_t _numOfFeature)
{
	return f(_bm, _numOfFeature);
}
int main()
{
	bitFunc arr[3] = { bitOn, bitOf, bitOnOf};
	bitMap* myBitMap;
	int menuChoice = 1, numberOfFeatures;
	int status;
	char * result;

	printf(" Welcome what do you want to do\n");

		while(menuChoice)
	{
		printf("--press 1 for create array of features\n"
		       "--press 2 to fix a features on\n"
		       "--press 3 to fix a features of\n"
		       "--press 4 to check a status of specific features\n"
		       "-- press 5 to print \n"
		       "--press 0 to exit\n");
		scanf("%d", &menuChoice);

		switch(menuChoice)
		{
			case 0: 
				destroyBM(myBitMap);
				return 0;
			case 1:
				printf("%s\n","please enter number of features" );
				scanf("%d", &numberOfFeatures);

				myBitMap = createBM(numberOfFeatures);
				if(myBitMap)
				{
					printf("%s\n", "operation Done!");
				}
				else 
				{
					return -1;
				}
				break;

			case 2:
			case 3:
			case 4:
				printf("%s\n","please enter the pos of features you want" );
				scanf("%d", &numberOfFeatures);

				status = operateBitFunc(arr[menuChoice - 2], myBitMap, numberOfFeatures);
				if(status < 0)
				{
					return -1;
				}

				break;

			case 5:
				result = malloc(numberOfFeatures * sizeof(char));
				BitMapPrint(myBitMap,&result);
				printf("%s\n",result );
				
		}
	}



}

