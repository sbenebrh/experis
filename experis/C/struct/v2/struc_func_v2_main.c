#include"struc_func_v2.h"

int main()
{
	personn identity[5] = {{127,21,1},{126,22,2},{125,20,3},{124,25,4},{123,22,5}};
	print(identity, 5);

	printf("\nthe sorted array of struct: \n\n" );
	BubbleSortForStruct(identity,5);
	print(identity, 5);
	
	return 0;
}