#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__
#include <stdio.h>
typedef int(*task)(void*);

typedef enum Executor_ResultCode {
	EXECUTOR_PAUSE = -1,
	EXECUTOR_SUCCESS = 0,
	EXECUTOR_NOT_INITIALIZED,
	EXECUTOR_ALLOCATION_FAILED,
	EXECUTOR_EMPTY,
	EXECUTOR_ERR_INPUT,
	EXECUTOR_ERR_INSERT_TASK
} Executor_Result;


typedef struct Executor Executor;

/**  
 * @brief create an executor implement FCFS scheduler
 * it send to the heap function who compare between times and vector  
 * @param[in] _size - size of the initial number of tasks
 * @param[in] _blockSize - the number of task user want to increment each time there is not available slot
 * @return Executor * - on success
 * @retval NULL on fail 
 *
 */
Executor* 			Executor_Create(size_t _size, size_t _blockSize);

/**  
 * @brief Deallocate a previously allocated Destroy
 * Free everything in the executor  
 * @param[in] _executor - executor to be deallocated.  
 * @return void
 */
void 				Executor_Destroy(Executor* _executor);
/**  
 * @brief Add Task to the Executor preserving Executor property.  
 * @param[in] _executor - Executor to insert Task to.
 * @param[in] _task - task to insert. can't be null .0 not rescheduled 1 rescheduled
 * @param[in] _period - the period between two repetition in milisecond;
 * @return success or error code 
 * @retval EXECUTOR_OK  on success
 * @retval EXECUTOR_NOT_INITIALIZED  error, Executor not initilized
 * @retval EXECUTOR_REALLOCATION_FAILED error, Executor could not reallocate underlying vector 
 */
Executor_Result 	Executor_AddTask(Executor* _executor,task _act,size_t _period,void* _context);

/**  
 * @brief run the executor according to the Executor property task after task
 * could be in pause mode.  
 * @param[in] _executor - Executor to insert Task to.
 
 * @return EXECUTOR_EMPTY or EXECUTOR_PAUSE 
 * @retval EXECUTOR_EMPTY on success
 * @retval EXECUTOR_PAUSE , on pause mode
 * warning not possible to do run into run 
 **/
Executor_Result 	Executor_Run(Executor* _executor);

/**  
 * @brief Pause the executor and when the user run again the executor the period are reset
 * could be in pause mode.  
 * @param[in] _executor - Executor to insert Task to.
 * @param[in] _period - the period between two repetition in second
 * @return EXECUTOR_EMPTY or EXECUTOR_PAUSE 
 * @retval EXECUTOR_EMPTY on success
 * @retval EXECUTOR_PAUSE , on pause mode
 * warning not possible to do run into run 
 **/
Executor_Result 	Executor_Pause(Executor* _executor,size_t _period);




#endif