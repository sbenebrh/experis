#include <unistd.h>
#include "myMalloc.h"

typedef struct  Header
{
	unsigned int m_flag :1;
	unsigned int m_size: 7;
}Header;



void* meminit(void* _mem, size_t _size)
{
	Header *startHeader = (Header*)_mem, *endHeader = (Header*)_mem + _size ;
	startHeader -> m_flag = 0;
	startHeader -> m_size = _size;...
	
}

void* memalloc(void* _bufStart, size_t _size)
{
	int oldsize = *_bufStart; 
	*(int*)_bufStart = _size | 0x80; 
	if (_size < oldsize)
	{
		*(_bufStart+_size) = oldsize - _size; 
	}
	return _bufStart + _size;	
}
void memfree(void* _buff)
{
	*(int*)_buff = *(int*)_buff & ~0x80; 
	next = _buff + *_buff; 
	if ((*(int*)next & 0x80) == 0)
	{
		*(int*)_buff = *(int*)_buff + *(int*)next;
	}
	
}

