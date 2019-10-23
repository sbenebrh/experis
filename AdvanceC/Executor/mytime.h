#ifndef __MYTIME_H__
#define __MYTIME_H__
#include<stdio.h>
#include <sys/time.h>
#include <time.h>
/*adjust parameters*/

typedef struct Timer Timer;
typedef struct timeval timeval;



int(*lessComparatorTFunc)(timeval time1,timeval time2);


/**  
 * @brief create a timer and start it
 * @return Timer* - on success
 * @retval NULL on fail 
 *
 */
Timer* Timer_Create();


/**  
 * @brief wait time from the current time to the next task time.  
 * @param[in] _timer - the timer .
 * @param[in] _duetime - the time of the next task
 */
void waitTime(Timer* _timer, timeval _duetime);

/**  
 * @brief return timer + time to add.  
 * @param[in] _timer - the timer.
 * @param[in] _time - the time to add
 * @return a timeval of the new time  
 */
timeval Time_Set(Timer* _timer, timeval _time);

/**  
 * @brief transform interval to int in milisecond.  
 * @param[in] _t - the timeval to convert
 *
 * @return the transformation of the timeval
 */
size_t transforrnTimevalToint(timeval _t);

/**  
 * @brief transform int to timeval.  
 * @param[in] period - the int in second to convert
 *
 * @return the transformation of the timeval
 */
timeval transformToTimeval(size_t period);
/**  
 * @brief Deallocate a previously allocated Destroy
 * Free everything in the timer  
 * @param[in] _timer - timer to be deallocated.  
 * @return void
 */
void destroy_Timer(Timer* _timer);

int compare(timeval timer1, timeval timer2);

#endif