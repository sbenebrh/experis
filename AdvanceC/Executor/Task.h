#ifndef __TASK_H__
#define __TASK_H__

#include <sys/time.h>
#include <time.h>
typedef enum Task_ResultCode {
	TASK_PAUSE = -1,
	TASK_COMPLETE,
	TASK_RESCHEDULED,
	TASK_ADD,
	TASK__NOT_INITIALIZED,
	TASK_ERR_INPUT,
	TASK_SUCCEES
} Task_Result;

typedef int(*action)(void*);

typedef struct Task Task;




/**  
 * @brief create a new task .
 *  
 * @param[in] _act - pointer to function that the user want to create
 * @param[in] _period - the period between two repetition in second;
 * @param[in] _context - the context that the user want to use it as parameter to his task
 * @return Task * - on success
 * @retval NULL on fail 
 *
 */
Task* Task_Create(action _act, size_t _period, void* _context);



Task_Result Task_SetTime(Task* _task, struct timeval _time);
Task_Result Task_GetPeriod(Task* _task, size_t* _time);
Task_Result Task_GetDueTime(Task* _task, struct timeval* _time);
/**  
 * @brief Deallocate a previously allocated Task
 * Free the Task  
 * @param[in] _task - _task to be deallocated. 
 * @return no return value
 */
void Task_Destroy(Task* _task);


/**  
 * @brief run a task .
 *  
 * @param[in] _task - task to run
 * @return Task * - on success
 * @return TASK_RESCHEDULED or TASK_PAUSE or TASK_COMPLETE or TASK_ADD
 * @retval TASK_COMPLETE on success and not have to be rescheduled 
 * @retval TASK_RESCHEDULED , if the Task should be rescheduled
 * @retval TASK_PAUSE, if the user want to be in Pause mode
 * @retval TASK_ADD, if the user want to add task on fly
 *
 */
Task_Result Task_Run(Task* _task);




#endif