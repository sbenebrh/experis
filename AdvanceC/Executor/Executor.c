#include <stdlib.h>
#include <time.h>
#include "Executor.h"
#include "mytime.h"
#include "vector.h"
#include "Heap.h"
#include "Task.h"
#include"zlog4c.h"

#define CHECKPOINTER if(NULL == _executor) return EXECUTOR_NOT_INITIALIZED

#define EXEC  		_executor -> m_exec
#define NTASKS		_executor -> m_nOfTask
#define TIMER 		_executor -> m_startTimer
#define VEC  		_executor -> m_vec
#define TIMER 		_executor -> m_startTimer

struct Executor
{
	Heap* m_exec;
	Vector* m_vec;/*i need it for sortheap*/
	size_t m_nOfTask;
	Timer* m_startTimer;
};

/*#####################STATIC##########################*/
static void* 					initExec(Executor* _executor,size_t _size, size_t _blockSize);
static Executor_Result 			insertTask(Executor* _executor, Task* _task);
static Executor_Result 			TranslateHeapError(Heap_Result _result);
	   int 						pauseT(void* _context);
static void 					Executor_ForEach(Executor*_executor,ActionFunction _act,void* _context);
static void						Reschedule_Task(Executor* _executor, Task* _task);
static int 						IsEmptyExecutor(Executor* _executor);
static int 						Reset_Time(void* _task, void* _timer);
static int 						checkTask(Executor* _executor,Task* _task, Task_Result _result);
/*#####################################################*/
int lessComparator(const void* _task1, const void* _task2)
{
	struct timeval temp1, temp2,res;
	size_t result;
	Task_GetDueTime((Task*) _task1, &temp1);
	Task_GetDueTime((Task*) _task2, &temp2);

	return compare(temp1, temp2);
 
}

Executor* Executor_Create(size_t _size, size_t _blockSize)
{
	Executor* newExecutor;
	newExecutor = (Executor*) calloc (1, sizeof(Executor));
	ZLOG(LOG_TRACE, "create executor");
	if(NULL == newExecutor )
	{
		return NULL;
	}
	if(NULL == initExec(newExecutor,_size, _blockSize))
	{
		free(newExecutor);
		return NULL;
	}
	return newExecutor;
}

void Executor_Destroy(Executor* _executor)
{
	Vector* destroyVec;
	if(_executor)
	{
		destroyVec = Heap_Destroy(&EXEC);
		Vector_Destroy(&destroyVec, NULL);
		free(_executor);
	}
}

Executor_Result Executor_AddTask(Executor* _executor, task _act,size_t _period,void* _context)
{
	Task* newTask;
	CHECKPOINTER;
	ZLOG(LOG_TRACE, "add task");
	if(NULL == _act)
	{
		return EXECUTOR_ERR_INPUT;
	}
	newTask = Task_Create(_act, _period, _context);
	if(NULL == newTask)
	{
		return EXECUTOR_ERR_INSERT_TASK;
	}
	return insertTask(_executor, newTask);

}
/*check if we need period parameter or just get the current time of the last task as a period*/
Executor_Result Executor_Pause(Executor* _executor,size_t _period)
{
	Task* pauseTask ;
	CHECKPOINTER;
	ZLOG(LOG_TRACE, "PAUSE");
	
	pauseTask = Task_Create(pauseT,_period, NULL);
	if(NULL == pauseTask)
	{
		return EXECUTOR_ERR_INSERT_TASK;
	}

	return insertTask(_executor, pauseTask);

}

Executor_Result Executor_Run(Executor* _executor)
{
	Task* executableTask;
	Task_Result result;
	Timer* timer;

	struct timeval dueTimeval;
	ZLOG(LOG_TRACE, "start of run");
	timer = Timer_Create();
	if(NULL == timer)
	{
		return EXECUTOR_ALLOCATION_FAILED;
	}

	TIMER = timer;
	/*for pause*/
	Executor_ForEach(_executor,Reset_Time,TIMER);
	EXEC = Heap_Build(Heap_Destroy(&EXEC), lessComparator);

	while(1)
	{
		if(IsEmptyExecutor(_executor))
		{
			Timer_Destroy(TIMER);
			return EXECUTOR_EMPTY;
		}

		executableTask = (Task*) Heap_Extract(EXEC);

		Task_GetDueTime(executableTask, &dueTimeval);
		waitTime(TIMER,dueTimeval);

		result = Task_Run(executableTask);
		NTASKS--;

		if(checkTask(_executor,executableTask, result) == EXECUTOR_PAUSE)
		{
			return EXECUTOR_PAUSE;
		}
	}
}
/*#####################STATIC FUNC#################*/
static void* initExec(Executor* _executor, size_t _size, size_t _blockSize)
{
	Heap* newHeap;
	Vector* newVector;

	newVector = Vector_Create(_size, _blockSize);
	if(NULL == newVector)
	{
		return NULL;
	}
	newHeap = Heap_Build(newVector, lessComparator);
	if(NULL == newHeap)
	{
		Vector_Destroy(&newVector, NULL);
		return NULL;
	}
	EXEC = newHeap;
	VEC = newVector;

	return (void*)_executor;
}


static Executor_Result insertTask(Executor* _executor, Task* _task)
{
	NTASKS++;
	return TranslateHeapError(Heap_Insert(EXEC, (void*)_task));
}

static Executor_Result 	TranslateHeapError(Heap_Result _result)
{
	switch(_result)
	{
		case HEAP_SUCCESS:
			return EXECUTOR_SUCCESS;

		case HEAP_NOT_INITIALIZED:
			return EXECUTOR_NOT_INITIALIZED;

		case HEAP_REALLOCATION_FAILED:
			return EXECUTOR_ERR_INSERT_TASK;
	}
}

int pauseT(void* _context)
{
	return EXECUTOR_PAUSE;
}

static void Executor_ForEach(Executor* _executor,ActionFunction _act,void* _context)
{
	Heap_ForEach(EXEC, _act, _context);
}

static void	Reschedule_Task(Executor* _executor, Task* _task)
{
	Reset_Time(_task, TIMER);
	insertTask(_executor,_task);
}

static int IsEmptyExecutor(Executor* _executor)
{
	return !NTASKS;
}

static int Reset_Time(void* _task, void* _timer)
{
	size_t period;
	struct timeval time;
	struct timeval ts;


	Task_GetPeriod((Task*) _task, &period);
	ts = transformToTimeval(period);
	time = Time_Set((Timer*) _timer, ts);
	Task_SetTime((Task*)_task, time);

	return 1;

}

static int checkTask(Executor* _executor,Task* _task, Task_Result _result)
{
	switch(_result)
	{
		case TASK_COMPLETE:
			Task_Destroy(_task);
			return 1;

		case TASK_RESCHEDULED:
			Reschedule_Task(_executor, _task);
			return 1;

		case TASK_PAUSE:
			Timer_Destroy(TIMER);
			Task_Destroy(_task);
			return EXECUTOR_PAUSE;
	}
}