#include<stdio.h>
#include"queue.h"
#include"ADTErr.h"
#include<math.h>


void PrintResult(char* _testName, TestResult _result, ADTErr _stat)
{
	if(_stat != ERR_OK) printf("%s %s \n","test error of the", _testName );
	printf("%s\t%s\n",_testName, (_result == SUCCEED)? "succed": "failed" );
}

TestResult TestQueueCreate1(ADTErr* _status)
{
	Queue* Queue;
	
	TestResult  result = FAIL;
	Queue = QueueCreate(5);
	if (Queue )
	{	
		QueueDestroy(Queue);
		Queue = QueueCreate(0);
		if(!Queue)
		{
			
			Queue = QueueCreate(6);
		
			if (Queue)
			{
				result = SUCCEED;
				*_status = ERR_OK; 
				QueueDestroy(Queue);
			}
		}
		
	}
	return result;
		
}

TestResult TestQueueCreate2(ADTErr* _status)/*check the boundary of the system*/
{
		Queue* queue = QueueCreate(pow(2,12000));
		*_status = ERR_OK;

		return queue == NULL ? SUCCEED:FAIL ;
}


TestResult TestQueueCreate3(ADTErr* _status)/*check if the created Queue is able to contain element*/
{
	int topnumber;
	Queue* queue = QueueCreate(5);
	*_status = QueueInsert(queue, 10);
	*_status |= QueueInsert(queue, 13);
	*_status |= QueueRemove(queue, &topnumber);
	QueueDestroy(queue);
	if(*_status)
	{
		if(topnumber != 10)
		return FAIL;
}
	return *_status != ERR_OK ? ERROR: SUCCEED;

}

/*check when i destroy a Queue twice it doesn t work*/
TestResult TestQueueDestroy1(ADTErr* _status)
{
	Queue * queue = QueueCreate(9);
	QueueDestroy(queue);
	QueueDestroy(queue);

	*_status = ERR_OK;
	return SUCCEED;
}

TestResult TestQueueDestroy2(ADTErr* _status)
{
	Queue * queue = QueueCreate(9);
	QueueDestroy(queue);
	if(IsEmpty(queue) == 1)
		*_status = ERR_OK;
	return SUCCEED;
}

TestResult TestQueueDestroy3(ADTErr* _status)
{
	Queue* queue1 = QueueCreate(9);
	Queue* queue2 = QueueCreate(5);

	QueueDestroy(queue1);
	if(queue2 && !queue1)
		*_status = ERR_OK;
	return SUCCEED;
}

TestResult TestQueueInsert1(ADTErr* _status)
{
	
	Queue * queue = QueueCreate(1);

	 *_status = QueueInsert(queue, 10);
	 *_status |= QueueInsert(queue, 11);
	 
	 QueueDestroy(queue);
	 if(*_status != ERR_OK) return  SUCCEED ;
	 else return FAIL;

}

TestResult TestQueueInsert2(ADTErr* _status)
{
	
	Queue * queue = QueueCreate(1);

	 *_status = QueueInsert(queue, 10);
	 *_status |= QueueRemove(queue, NULL);
	 *_status |= QueueInsert(queue, 11);

	 
	 QueueDestroy(queue);
	 if(*_status == ERR_OK) return  SUCCEED ;
	 else return FAIL;

}

TestResult TestQueueInsert3(ADTErr* _status)
{
	
	Queue * queue = QueueCreate(2);

	 *_status = QueueInsert(queue, 10);
	 *_status |= QueueInsert(queue, 11);
	 *_status |= QueueRemove(queue, NULL);
	 *_status |= QueueInsert(queue, 13);

	 
	 QueueDestroy(queue);
	 if(*_status == ERR_OK) {*_status = ERR_OK;return  SUCCEED ;}
	 else return FAIL;

}

TestResult TestQueueRemove1(ADTErr* _status)
{
	
	Queue * queue = QueueCreate(2);

	 *_status = QueueInsert(queue, 10);
	 *_status |= QueueRemove(queue, NULL);
	 *_status |= QueueRemove(queue, NULL);

	 QueueDestroy(queue);
	 if(*_status != ERR_OK) {*_status = ERR_OK;return  SUCCEED ;}
	 else return FAIL;

}


int main()
{
	TestResult result ;
	ADTErr status ;
	result = TestQueueCreate1(&status);
	PrintResult("TestQueueCreate1", result,status);
	
	result = TestQueueCreate2(&status);
	PrintResult("TestQueueCreate2", result,status);
	
	result = TestQueueCreate3(&status);
	PrintResult("TestQueueCreate3", result,status);

	result = TestQueueDestroy1(&status);
	PrintResult("TestQueueDestroy1", result,status);

	result = TestQueueDestroy2(&status);
	PrintResult("TestQueueDestroy2", result,status);

	result = TestQueueDestroy3(&status);
	PrintResult("TestQueueDestroy3", result,status);

	result = TestQueueInsert1(&status);
	PrintResult("TestQueueInsert1", result,status);

	result = TestQueueInsert2(&status);
	PrintResult("TestQueueInsert2", result,status);

	result = TestQueueInsert2(&status);
	PrintResult("TestQueueInsert2", result,status);

	result = TestQueueRemove1(&status);
	PrintResult("TestQueueRemove1", result,status);
	return 0;
}
