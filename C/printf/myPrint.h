#ifndef _MYPRINT_H
#define _MYPRINT_H
/*
* @brief print at the stdout the string according to format

* @param _strFormat: the formated string 
* @param ...: unknow numbers of parameters
				it could be string, float, int type
				
* @return :the size of the returned string
			if the first param is null return -1;
**/
int MyPrintf(const char* _strFormat, ...);

#endif