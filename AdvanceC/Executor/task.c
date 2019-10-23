#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "Task.h"
#include "mytime.h"
#include"zlog4c.h"

#define CHECKNULLPOINTER(X) if((X)== NULL) return NULL
#define CHECKPOINTER 		if(NULL == _task) TASK__NOT_INITIALIZED
#define CHECKINPUT			if(NULL == _task) TASK_ERR_INPUT

#define PERIOD 				_task -> m_period
#define ACT    				_task -> m_act
#define	CONTEXT 			_task -> m_context
#define DUETIME				_task -> m_dueTime

struct Task
{
	size_t 				m_period;
	action 				m_act;
	void* 				m_context;
	struct timeval		m_dueTime;
};

/*############STATIC DEC##################*/
void 		initialiseTask(Task* _task, action _act, size_t _period, void* _context);
/*##########################################*/
Task* Task_Create(action _act, size_t _period, void* _context)
{
	Task* newTask;
	ZLOG(LOG_TRACE, "create task");
	newTask = (Task*) malloc(sizeof(Task));
	CHECKNULLPOINTER(newTask);

	initialiseTask(newTask, _act, _period, _context);

	return newTask;
}

void Task_Destroy(Task* _task)
{
	if(_task)
	{
		ZLOG(LOG_TRACE, "destroy task");
		free(_task);
	}
}

Task_Result Task_GetPeriod(Task* _task, size_t* _time)
{
	CHECKPOINTER;
	CHECKINPUT;

	*_time = PERIOD;
	return TASK_SUCCEES;

}

Task_Result Task_GetDueTime(Task* _task, struct timeval* _Duetime)
{
	CHECKPOINTER;
	CHECKINPUT;

	*_Duetime = DUETIME;
	return TASK_SUCCEES;
}

Task_Result Task_SetTime(Task* _task, struct timeval _time)
{
	CHECKPOINTER;
	DUETIME = _time;
	return TASK_SUCCEES;
}

Task_Result Task_Run(Task* _task)
{
	CHECKPOINTER;
	ZLOG(LOG_TRACE, "run task");
	return ACT(CONTEXT);
}

/*#######################STATIC########################*/
void initialiseTask(Task* _task, action _act, size_t _period, void* _context)
{
	struct  timeval ts;
	ts = transformToTimeval(_period);
	PERIOD = _period;
	ACT = _act;
	CONTEXT = _context;

	
	DUETIME = ts;
}
