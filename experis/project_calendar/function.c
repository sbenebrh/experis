#include<stdio.h>
#include<stdlib.h>
#include <stdarg.h>
#include"function.h"

struct AD
{
	int size;
	int incrementBlocks;
	meeting_t ** arrayMeeting;
	int numOfMeeting; 
};


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
	meeting_t  *meeting = NULL;
	if(checkErrInput(_begin,0) == ERR_INPUT || checkErrInput(_end,0) == ERR_INPUT || checkErrInput(_end,_begin) || _begin > 23.99 || _end > 23.99)
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
meeting_t * FindMeeting(const AD * const _DAptr, float _begining)
{
	int i;
	if(checkSegmentationError(_DAptr) == SEGMENTATION_FAULT || checkSegmentationError(_DAptr -> arrayMeeting) == SEGMENTATION_FAULT || checkErrInput(_begining,0) == ERR_INPUT || _begining > 23.99)
	{
		return NULL;
	}
	for ( i = 0; i < _DAptr ->numOfMeeting; ++i)
	{
		if(_DAptr ->arrayMeeting[i+1]->begin < _begining)
		{
			continue;
		}
		if(_DAptr ->arrayMeeting[i]->begin == _begining)
		{
			return _DAptr ->arrayMeeting[i];
		}
	}
	return NULL;
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

	for ( i = 0; i < _DAptr -> numOfMeeting; ++i)
	{
		printf("%d\t%.2f\t%.2f\t%d\n",i+1,_DAptr->arrayMeeting[i]-> begin,_DAptr->arrayMeeting[i]-> end,_DAptr->arrayMeeting[i]-> room);
	}
	return WELL;
}
enum status InsertMeeting(AD * _DAptr,meeting_t * _meeting)
{
	
	if(checkSegmentationError(_DAptr) == SEGMENTATION_FAULT || checkSegmentationError(_meeting) == SEGMENTATION_FAULT)
	{
		return SEGMENTATION_FAULT;
	}
	_DAptr -> arrayMeeting[_DAptr -> numOfMeeting] = _meeting;
	_DAptr -> numOfMeeting += 1;
	return WELL;
}