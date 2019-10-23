#ifndef __MYMALLOC_H__
#define __MYMALLOC_H__
/** 
 *  @file myMalloc.c
 *  @brief allocation framework 
 *	
 *  @details  implicit free list using first fit implementation
 *  
 *  @author samuel ben ibgui  (benebrhi@gmail.com)
 * 
 *  @bug No known bugs.
 */

void* meminit(void* _mem, size_t _size);
void* memalloc(void* _bufStart, size_t _size);
void memfree(void* _buff);

#endif