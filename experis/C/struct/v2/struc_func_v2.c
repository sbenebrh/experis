#include"struc_func_v2.h"
void print(personn * _arrayPersonn, int _size)
{	
	int i;

	if(!_arrayPersonn)
	{
		return SEGMENTATION_FAULT;
	}
	if(_size < 0){
		return ERR_ARRAY_SIZE;
	}
	printf("%s\t%s\t%s\t%s\n", "personn","id","age","edu");
	printf("%s\n","------------------------------" );
	for(i = 0; i < _size;i++)
	{
		printf("%d\t%d\t%d\t%d\n", i + 1, _arrayPersonn[i].id,_arrayPersonn[i].age,_arrayPersonn[i].edu);
	}
}
void swap(personn* _firstNumber, personn*  _secondNumber)
{
	personn temp = *_firstNumber;
	*_firstNumber = *_secondNumber;
	*_secondNumber = temp;
}

int BubbleUp(personn  _arr[], int _size)
{
	int i = 0;
	int isSwapped = 0;
	
	for(; i < _size; i++)
	{
		if(_arr[i].id > _arr[i+1].id)
		{
			swap( & _arr[i], & _arr[i+1]);
			isSwapped = 1;
		}
	}
	return isSwapped;
}
int checkNullArray(personn _arr[])
{
	if(_arr == NULL)
	{
		printf("the array is empty");
		return 0;
	}
	return 1;

}
void BubbleSortForStruct(personn * _arrayPersonn,int _size)
{
	int i = 0;

	if(!_arrayPersonn)
	{
		return SEGMENTATION_FAULT;
	}
	if(_size < 0){
		return ERR_ARRAY_SIZE;
	}

	checkNullArray(_arrayPersonn);

	for(; i < _size; i++)
	{
		if(IS_SWAPPED == BubbleUp(&_arrayPersonn[0],  _size-i))
		{
			break;
		}
	}
}




