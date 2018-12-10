#include<stdio.h>
#include<stdlib.h>
#include"function.h"


struct AD
{
	int size;
	int incrementBlocks;
	meeting_t ** arrayMeeting;
	int numOfMeeting; 
};


enum status checkNullArray(meeting_t * _arr[])
{
	if(_arr == NULL)
	{
		return SEGMENTATION_FAULT;
	}
	return WELL;
}

void swap(meeting_t** _firstMeeting, meeting_t**  _secondmeeting)
{
	meeting_t * temp = *_firstMeeting;
	*_firstMeeting = *_secondmeeting;
	*_secondmeeting = temp;
}

int BubbleUp(meeting_t *  _arr[], int _size)
{
	int i = 0;
	int isSwapped = 0;
	
	for(; i < _size; i++)
	{
		if(_arr[i] -> begin > _arr[i+1] -> begin)
		{
			swap( & _arr[i], & _arr[i+1]);
			isSwapped = 1;
		}
	}
	return isSwapped;
}



void sortMeeting(AD * _DAptr)
{
	int i = 0;

	if(!_DAptr)
	{
		return ;
	}

	if((_DAptr -> numOfMeeting) <= 0){
		return ;
	}

	checkNullArray(_DAptr -> arrayMeeting);

	for(; i < _DAptr -> numOfMeeting; i++)
	{
		if(IS_SWAPPED == BubbleUp(&(_DAptr -> arrayMeeting[0]),  (_DAptr -> numOfMeeting -1)-i))
		{
			break;
		}
	}
	
}
int checkErrInput(int _var,int _limit)
{
	
	if(_var < _limit)
	{
		return ERR_INPUT;
	}
	return WELL;
}

int checkSegmentationError(const void * const _ptr)
{
	if(!_ptr)
	{
		return SEGMENTATION_FAULT;
	}
	return WELL;
}
void initializeStruct(AD * _ptr,int _size,int _incrementBlocks)
{
	_ptr -> size = _size;
	_ptr-> incrementBlocks = _incrementBlocks;
	_ptr -> numOfMeeting = 0;
	_ptr -> arrayMeeting = (meeting_t**) malloc(_size * sizeof(meeting_t*));
}

meeting_t * createMeeting(float _begin, float _end, int _room)
{
	meeting_t  * meeting = NULL;
	if(checkErrInput(_begin,0) == ERR_INPUT || checkErrInput(_end,0) == ERR_INPUT || checkErrInput(_end,_begin) == ERR_INPUT || _begin > 23.99 || _end > 23.99)
	{
		return NULL;
	}
	meeting = (meeting_t *) malloc(sizeof(meeting_t));
	if(checkSegmentationError(meeting) == SEGMENTATION_FAULT)
	{
		return NULL;
	}

	meeting ->begin = _begin;
	meeting -> end = _end;
	meeting ->room = _room;

	return meeting;
}

AD * ADCreate(int _size, int _incrementBlocks)
{
	AD * ADptr = NULL;
	if(checkErrInput(_size,0) == ERR_INPUT || checkErrInput(_incrementBlocks,0) == ERR_INPUT ||(checkErrInput(_size,1) == ERR_INPUT && checkErrInput(_incrementBlocks,1) == ERR_INPUT ))
	{
		return NULL;
	}
	ADptr = (AD*) malloc(_size * sizeof(AD));
	if(checkSegmentationError((void *)ADptr) == SEGMENTATION_FAULT)
	{
	 	return NULL;
	}

	initializeStruct(ADptr, _size,_incrementBlocks);

	if(checkSegmentationError((void *)ADptr->arrayMeeting) == SEGMENTATION_FAULT)
	{
		free(ADptr);
		return NULL;
	}
	return ADptr;

}

enum status RemoveMeeting(AD * _DAptr, meeting_t* *_removedMeeting, float _begining)
{	
	int indexFindedMeeting;
	int c;

	if(checkSegmentationError(_DAptr) == SEGMENTATION_FAULT )
	{
		return SEGMENTATION_FAULT;
	}
	if(checkErrInput(_begining,0) == ERR_INPUT || _begining > 23.99)
	{
		return ERR_INPUT;
	}

	indexFindedMeeting = FindMeeting(_DAptr, _begining, _removedMeeting);
	if(0 < indexFindedMeeting)
	{
		return UNKNOWN_MEETING;
	}
	*_removedMeeting = _DAptr -> arrayMeeting[indexFindedMeeting];

	for(c = indexFindedMeeting ; c < _DAptr -> numOfMeeting -1; c++)
	{
		_DAptr -> arrayMeeting[c] = _DAptr -> arrayMeeting[c + 1];
	}
	_DAptr ->numOfMeeting -= 1;


	return WELL;
}

int FindMeeting(const AD * const _DAptr, float _begining, meeting_t* *_findedMeeting)
{
	
	int i;

	if(checkSegmentationError(_DAptr) == SEGMENTATION_FAULT || checkSegmentationError(_DAptr -> arrayMeeting) == SEGMENTATION_FAULT || checkErrInput(_begining,0) == ERR_INPUT || _begining > 23.99)
	{
		return SEGMENTATION_FAULT;
	}
	for ( i = 0; i < _DAptr ->numOfMeeting; i++)
	{
		
		if(_DAptr ->arrayMeeting[i]->begin == _begining)
		{
			*_findedMeeting = _DAptr ->arrayMeeting[i];
			return i;
		}
	}
	return -1;
}


void ADDestroy(AD * _DAptr)
{
	int i;
	/*enum status stat;*/
	if(!_DAptr)
	{
		if(!(_DAptr -> arrayMeeting))
		{
			for (i = 0; i < _DAptr -> numOfMeeting; ++i)
			{
				/*TODO stat = RemoveMeeting(_DAptr);*/
			}
			free(_DAptr -> arrayMeeting);
		}
		free(_DAptr);
	}
}

enum status ADPrint(const AD * const _DAptr)
{
	int i;
	if(checkSegmentationError((void *) _DAptr) == SEGMENTATION_FAULT)
	{
	 return SEGMENTATION_FAULT;
	}
	printf("%s\t%s\t%s\t%s\t\n","number:","start", "end", "room" );
	printf("%s\n","-----------------------------------" );

	for ( i = 0; i < _DAptr -> numOfMeeting; i++)
	{
		printf("%d\t%.2f\t%.2f\t%d\n",i+1,_DAptr->arrayMeeting[i]-> begin,_DAptr->arrayMeeting[i]-> end,_DAptr->arrayMeeting[i]-> room);
	}
	printf("\n" );
	return WELL;
}


enum status checkOverLoadingMeeting(AD * _DAptr, const meeting_t * const _meeting)
{
	int i;
	for(i  = 0; i < _DAptr -> numOfMeeting; i++)
	{
		if((_DAptr -> arrayMeeting[i] -> begin < _meeting -> begin && _DAptr -> arrayMeeting[i] -> end > _meeting ->begin ) || (_DAptr -> arrayMeeting[i] -> begin > _meeting -> begin && _DAptr -> arrayMeeting[i] -> begin < _meeting -> end) || (_DAptr -> arrayMeeting[i] -> end > _meeting -> begin && _DAptr -> arrayMeeting[i] -> end < _meeting -> end))
		{
			return ERR_OVERLOADING_MEETING;
		}
	}
	return WELL;
}


enum status InsertMeeting(AD * _DAptr,meeting_t * _meeting)
{
	enum status status;
	meeting_t ** temp = NULL;
	
	if(checkSegmentationError(_DAptr) == SEGMENTATION_FAULT || checkSegmentationError(_meeting) == SEGMENTATION_FAULT)
	{
		return SEGMENTATION_FAULT;
	}
	if(_DAptr -> size == _DAptr -> numOfMeeting && _DAptr -> incrementBlocks == 0)
		return NOT_ENOUGH_SPACE	;


	status = checkOverLoadingMeeting(_DAptr,_meeting);
	if(status != WELL)
		return ERR_OVERLOADING_MEETING;

	if(_DAptr -> size == _DAptr -> numOfMeeting && _DAptr -> incrementBlocks > 0)
	{
		temp = (meeting_t**) realloc(_DAptr -> arrayMeeting,(_DAptr -> size + _DAptr -> incrementBlocks)* sizeof(meeting_t **));
		if(temp)
		{
			_DAptr -> arrayMeeting = temp;
			_DAptr -> size += _DAptr -> incrementBlocks;

		}
		else
		{
			return ERR_REALLOCATION;
		}

	}
	_DAptr -> arrayMeeting[_DAptr -> numOfMeeting] = _meeting;
	_DAptr -> numOfMeeting += 1;
	if(_DAptr -> numOfMeeting > 1)
	{
		sortMeeting(_DAptr);
	}
	return WELL;
}
