#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include<time.h>
#include<stdarg.h>
#include"zlog4c.h"

typedef struct Config
{
	char m_level[128];
	char m_logfile[128];
}Config;

static Config* newConfig;
 FILE* file;
/*############STATIC######################*/
static void 		readData(FILE* _file, Config* _config);
static void 		copyToStruct(FILE* _file, char* log);
static void 		closeFile(void);
static LOG_LEVEL 	LevelConverter(char * _logLevel);
static void			printDate(void);
static void 		printProcess(int _id);
static void			printThread(long _id);
static void 		printLevel(LOG_LEVEL _level);
static void 		printDetails(const char* _sourceName,const char*  _funcName,int _line);
static char			LogToChar(LOG_LEVEL _log);
/*########################################*/
void zlog_init(char * _configurationFileName)
{
	file = fopen(_configurationFileName, "r");
	if( NULL == file)
	{
		return;
	}
	newConfig =(Config*) malloc(sizeof(Config));
	readData(file,newConfig);

	fclose(file);

	file = fopen(newConfig -> m_logfile, "w");

	atexit(closeFile);
}

static void readData(FILE* _file, Config* _config)
{
	copyToStruct(_file, _config -> m_level);	
	copyToStruct(_file, _config -> m_logfile);	

}

static void copyToStruct(FILE* _file, char* _log)
{
	char delim = '=';
	char line[128];
	char* position,*posEndl;
	char endl = '\n';

	fgets(line,128, _file);
	position = strchr(line, delim);
	/*remove \n */
	posEndl = strchr(line,endl);
	*posEndl = '\0';

	position +=2;
	strcpy(_log, position);
}

static void closeFile(void)
{
	fclose(file);
	free(newConfig);
}

static LOG_LEVEL LevelConverter(char * _logLevel)
{
	switch(_logLevel[0])
	{
		case 'T':
			return LOG_TRACE;
		case 'D':
			return LOG_DEBUG;
		case 'I':
			return LOG_INFO;
		case 'W':
			return LOG_WARNING;
		case 'E':
			return LOG_ERROR;
		case 'C':
			return LOG_CRITICAL;
		case 'S':
			return LOG_SEVERE;
		case 'F':
			return LOG_FATAL;
		case 'N':
			return LOG_NONE;
	}
	return LOG_TRACE;
}

void LogFunc(LOG_LEVEL _level,const char* _sourceName,const char* _funcName, int _line , int _process, long _thread, ...)
{
	va_list args;
	va_start(args, _thread);
	char message[64];
	if(_level >= LevelConverter(newConfig -> m_level))
	{
		printDate();

		printProcess(_process);

		printThread(_thread);

		printLevel(_level);
/*#ifdef NDEBUG*/
		printDetails(_sourceName, _funcName, _line);
/*#endif*/
		strcpy(message,va_arg(args, char*));
		vfprintf(file, message,args );
		fprintf(file, "\n");

	}
	va_end(args);
	fflush(file);
}

static void	printDate(void)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	fprintf(file,"%d-%d-%d %d:%d:%d ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

static void printProcess(int _id)
{
	fprintf(file, "%d ",_id );
}
static void printThread(long _id)
{
	fprintf(file, "%ld ",_id );
}
static void printLevel(LOG_LEVEL _level)
{
	fprintf(file, "%c ",LogToChar(_level));
}
static void printDetails(const char* _sourceName,const char*  _funcName,int _line)
{
	fprintf(file, "%s@%s:%d ", _sourceName, _funcName,_line);
}


static char	LogToChar(LOG_LEVEL _log)
{
	switch(_log)
	{
		case LOG_TRACE:
			return 'T';
		case LOG_DEBUG:
			return 'D';
		case LOG_INFO:
			return 'I';
		case LOG_WARNING:
			return 'W';
		case LOG_ERROR:
			return 'E';
		case LOG_CRITICAL:
			return 'C';
		case LOG_SEVERE:
			return 'S';
		case LOG_FATAL:
			return 'F';
		case LOG_NONE:
			return 'N';
	}
return 'T';
}
