#ifndef __LOG_H__
#define __LOG_H__

#include <pthread.h> 
#include <stdio.h>
#include <unistd.h> 
extern FILE* file;

typedef enum LOG_LEVEL
{
	LOG_TRACE,
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR,
	LOG_CRITICAL,
	LOG_SEVERE,
	LOG_FATAL,
	LOG_NONE
}LOG_LEVEL;


void LogFunc(LOG_LEVEL _level,const char* _sourceName,const char* _funcName, int _line , int _process, long _thread,...);
#define ZLOG(X,...)	do{LogFunc((X),__FILE__,__func__,__LINE__,getpid(),pthread_self(),__VA_ARGS__) ;}while(0)

void zlog_init(char * _configurationFileName);

#endif
