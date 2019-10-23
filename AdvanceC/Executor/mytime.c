#define _BSD_SOURCE
#include "mytime.h"
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>


#define _POSIX_C_SOURCE 200809L

struct Timer
{
	struct timeval m_time;
};

/*############STATIC DEC#################3*/
static struct timeval GetStartTime();
/*########################################*/

Timer* Timer_Create()
{

	Timer* newTimer = (Timer*) malloc(sizeof(Timer));
	newTimer -> m_time = GetStartTime();
	return newTimer;
}
void Timer_Destroy(Timer* _timer)
{
	if(_timer)
	{
		free(_timer);
	}
	
}
void waitTime(Timer* _timer, timeval _time)
{
	timeval sleeptime,temp;

	timersub( &_time,&_timer-> m_time, &sleeptime);
	usleep(sleeptime.tv_sec*1000000 + sleeptime.tv_usec );
	_timer -> m_time = Time_Set(_timer, sleeptime);
}



timeval Time_Set(Timer* _timer,timeval _time)
{
	timeval ts;
	timeradd(&(_timer -> m_time), &_time, &ts);
	return ts;
}


timeval transformToTimeval(size_t period)
{
	timeval ts;
	ts.tv_sec = period;
	ts.tv_usec = 0;
	return ts;
}

size_t transforrnTimevalToint(timeval _t)
{
	size_t result ;
	result = _t.tv_sec*1000+ _t.tv_usec;
	return result;
}

int compare(timeval timer1, timeval timer2)
{
	int result;
	timeval res;
	if(timer1.tv_sec > timer2.tv_sec)
	{
		return 1;
	}
	else if((timer1.tv_sec == timer2.tv_sec) && timer1.tv_usec <= timer2.tv_usec)
	{
		return 1;
	}
	return 0;
}
/***********************************************************************************************************************/

static timeval GetStartTime()
{
	timeval ts;
    gettimeofday(&ts,NULL);
	return ts;
}