
/*
 * string.h
 * framework for string
 * Version: 1.0
 * creation: 09/01/2019
 * last change: 09/01/201
 *      Author: samuel ben ibgui   
 * 	    benebrhi@gmail.com
*/

#ifndef __STRING_H__
#define __STRING_H__

#include<stddef.h>
/** 
 * @function: StrLen	
 * @brief: return the length of the string O(n)
 * 
 * @param _str : the string
 *
 * @return the lenght or if we have non initialized string return 0
**/
size_t StrLen(const char* _str);
size_t StrLenRec(const char* _str);

/** 
 * @function: StrCompare	
 * @brief: compare the two strings according to ascii value O(n)
 * 
 * @param _s1 : the first string
 * @param _s2 : the second string
 *
 * @return the difference between the two string
 *		if lenght(s1) > lenght(s2) return 1
 		if lenght(s1) < lenght(s2) return -1
**/
int StrCompare(const char* _s1, const char* _s2);
int StrCompareRec(const char* _s1, const char * _s2);

/** 
 * @function: StrCopy	
 * @brief: copy the string of the source to the destination
 * 
 * @param _destination : the destination
 * @param _source : the source
 *
 * @return the destination
**/
char* StrCopy(char* _destination, const char* _source);
char* StrCopyRec(char* _destination, const char* _source);

/** 
 * @function: StrCopy	
 * @brief: copy the  N first character of source to the destination 
 * 
 * @param _destination : the destination
 * @param _source : the source
 *
 * @return the destination
**/
char* StrNCopy(char* _destination, const char* _source, size_t _num);
char* StrNCopyRec(char* _destination, const char* _source, size_t _num);

/** 
 * @function: StrConcat	
 * @brief: copy the  source to the end of destination 
 * 
 * @param _destination : the destination
 * @param _source : the source
 *
 * @return the destination
**/
char* StrConcat(char* _destination, const char* _source);
/*
 * @function: StrSubString	
 * @brief: search the first occurence of the search to _str
 * 
 * @param _str : the source
 * @param _search : the string to search
 *
 * Returns a pointer to the first occurrence of str2 in str1, 
		or a null pointer if str2 is not part of str1
*/
char* StrSubString(const char* _str, const char* _search);



#endif