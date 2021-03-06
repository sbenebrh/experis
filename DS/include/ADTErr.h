#ifndef _ADTERR_H
#define _ADTERR_H


typedef enum  ADTErr
{	
	ERR_OK,
	ERR_UNDERFLOW,
	ERR_UNINITIALIZED,
	ERR_WELL,
	ERR_OVERFLOW,
	ERR_NO_ORIGINAL_POINTER,
	ERR_INPUT = -10,
	ERR_ALLOCATION = 6,
	ERR_REALLOCATION,
	ERR_OVER_MAX_BLOCKS,
	ERR_SEGMENTATION,
	ERR_NOT_IN_VECTOR,
	NOT_INITIALIZED,
	NOT_ORIGINAL_STACK,
	EMPTY_STACK,
	ERR_NOT_EMPTY,
	ERR_ADD_MISS,
	ERR_EMPTY,
	ERR_NOT_FOUND
}ADTErr;


typedef enum statusErr {
	SUCCEED,
	FAIL,
	ERROR
}TestResult;

#endif /* _ADTERR_H*/
