#include<stdio.h>

enum status {ERR_INPUT,
				SEGMENTATION_FAULT,
				WELL};












typedef struct  AD AD;


typedef struct 
{
	float begin;
	float end;
	int room;
} meeting_t;

AD * ADCreate(int _size, int _incrementBlocks);/* done*/
meeting_t * createMeeting(float _begin, float _end, int _room);/*done*/
enum status InsertMeeting(AD * _DAptr,meeting_t * _meeting);
enum status RemoveMeeting(AD * _DAptr,meeting_t  * _removedMeeting);
meeting_t * FindMeeting(const AD * const _DAptr, float _begining);/*done*/
void ADDestroy(AD * _DAptr);/*done*/
enum status ADPrint(const AD * const _DAptr);/*done*/

