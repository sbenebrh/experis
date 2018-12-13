#include"struct_funcs_v3.h"


enum DAStatus checkSegmentationError(void * _arr)
{
	if(!_arr)
	{
		return SEGMENTATION_FAULT;
	}
	return WELL;
}

enum DAStatus checkEmptyArray(int _number)
{
	if(!_number)
	{
		return EMPTY_ARRAY; 
	}
	return WELL;
}
enum DAStatus checkInputError(int _data, int _limit)
{
	if(_data < _limit)
	{
		return  ERR_INPUT;
	}
	return WELL;
}

 void initializeStruct(DA * Createptr,int _size,int _incrementBlockSize)
{
	Createptr -> size = _size;
	Createptr -> incDblockSize = _incrementBlockSize;
	Createptr -> numOfElement = 0;
	Createptr -> arrData = (int*) malloc(_size * sizeof(int));
}

enum DAStatus print(DA * _Daptr)
{
	int i;

	if(checkSegmentationError(_Daptr) ==  SEGMENTATION_FAULT) {return SEGMENTATION_FAULT;}
	if(checkSegmentationError(_Daptr -> arrData) ==  SEGMENTATION_FAULT) {return SEGMENTATION_FAULT;}
	
	for(i = 0; i < _Daptr -> numOfElement; i++)
	{
		printf("%d\t", _Daptr -> arrData[i]);
	}
	printf("\n");
	return WELL;
		
}


void Ddestroy(DA * _Daptr)
{
	if(! _Daptr)
		{
			if(! _Daptr->arrData)
			{
				free(_Daptr->arrData);
			}
			free(_Daptr);
		}
}

enum DAStatus Dremove(DA * _Daptr, int * _data)
{
	if(checkSegmentationError(_Daptr) ==  SEGMENTATION_FAULT) {return SEGMENTATION_FAULT;}
	if(checkSegmentationError(_Daptr -> arrData) ==  SEGMENTATION_FAULT) {return SEGMENTATION_FAULT;}
	if(checkEmptyArray(_Daptr ->numOfElement) == EMPTY_ARRAY) {return EMPTY_ARRAY;}

	*_data = _Daptr->arrData[_Daptr -> numOfElement-1];
	_Daptr -> numOfElement -= 1;

	return WELL;
}

DA * Dcreate(int _size, int _incrementBlockSize)
{
	DA * Createptr = NULL;

	if(checkInputError(_size,0) == ERR_INPUT){ return NULL;}
	if(checkInputError(_incrementBlockSize,0) == ERR_INPUT){  return NULL;}
	if((checkInputError(_size, 1) == ERR_INPUT) && (checkInputError(_incrementBlockSize, 1)==ERR_INPUT))
	{
		free(Createptr);
		return NULL;
	}

	Createptr = (DA*) malloc(sizeof(DA));

	if(checkSegmentationError(Createptr) == SEGMENTATION_FAULT) {return NULL;}
	
	initializeStruct(Createptr, _size,_incrementBlockSize);

	if(checkSegmentationError(Createptr -> arrData) == SEGMENTATION_FAULT){free(Createptr);return NULL;};
	
	return Createptr;
}

enum DAStatus Dadd(DA * _Daptr, int _data)
{	
	int * temp = NULL;

	if(checkSegmentationError(_Daptr) ==  SEGMENTATION_FAULT) {free(temp);return SEGMENTATION_FAULT;}
	if(checkSegmentationError(_Daptr -> arrData) ==  SEGMENTATION_FAULT) {free(temp);return SEGMENTATION_FAULT;}

	if(_Daptr -> size == _Daptr ->numOfElement && _Daptr -> incDblockSize > 0)
	{
		temp = realloc(_Daptr -> arrData, (_Daptr -> size + _Daptr -> incDblockSize) * sizeof(int));
		
		if(checkSegmentationError(temp) != SEGMENTATION_FAULT)
		{
			_Daptr -> arrData = temp;
			_Daptr -> size += _Daptr ->incDblockSize;
		}
		else
			return SEGMENTATION_FAULT;
	}
	else if(_Daptr -> size == _Daptr ->numOfElement && _Daptr -> incDblockSize == 0)
	{
		return NOT_ENOUGH_BLOCKS;
	}

	_Daptr ->arrData[_Daptr -> numOfElement] = _data;
	_Daptr -> numOfElement += 1;

	return WELL;
}

enum DAStatus Dfind(DA * _Daptr, int _data)
{
	int i;
	if(checkSegmentationError(_Daptr) ==  SEGMENTATION_FAULT) {return SEGMENTATION_FAULT;}
	if(checkSegmentationError(_Daptr -> arrData) ==  SEGMENTATION_FAULT) {return SEGMENTATION_FAULT;}


	if(_Daptr -> arrData[0] > _data || _Daptr -> arrData[_Daptr -> numOfElement-1] < _data  )
		return NOT_IN_THE_ARRAY;
	for(i = 0; i < _Daptr -> numOfElement ; i++)
	{
		if(_data == _Daptr ->arrData[i])
			return WELL;
	}
	return NOT_IN_THE_ARRAY;

}

