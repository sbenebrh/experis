#include<stdio.h>
#include<stdlib.h>
#include"heap.h"
#include"ADTErr.h"
#include"vector.h"

static void PrintResult(char* _testName, TestResult _result, ADTErr _stat)
{
	if(_stat != ERR_OK) printf("%s %s \n","test error of the", _testName );
	printf("%s\t%s\n",_testName, (_result == SUCCEED)? "succed": "failed" );
}

TestResult TestHeapBuild1()/*test with no items in the vector*/
{
	Heap * newHeap;

	Vector * controler = VectorCreate(10, 2);
	if(NULL == controler)
	{
		return FAIL;
	}
	newHeap = HeapBuild(controler);
	if(NULL == newHeap)
	{
		return FAIL;
	}
	
	HeapDestroy(newHeap);
	VectorDestroy(controler);
	
	return SUCCEED;
}

TestResult TestHeapBuild2(ADTErr* status)
{
	Heap * newHeap;
	int i;
	int arr[5] = { 3 , 11 , 8 , 17, 18};

	Vector * controler = VectorCreate(4, 2);
	if(NULL == controler)
	{
		return FAIL;
	}
	for(i = 0; i < 5 ; i++)
	{	
		*status |= VectorAdd(controler, arr[i]);
	}
	newHeap = HeapBuild(controler);
	if(NULL == newHeap)
	{
		return FAIL;
	}
	HeapItemsPrint(newHeap);

	HeapDestroy(newHeap);
	VectorDestroy(controler);
	
	return SUCCEED;

}

TestResult TestHeapBuild3()/*test with no items in the vector*/
{
	Heap * newHeap;

	Vector * controler;


	newHeap = HeapBuild(controler);
	if(NULL == newHeap)
	{
		HeapDestroy(newHeap);
		return SUCCEED;
	}
	
	HeapDestroy(newHeap);
	
	return FAIL;
}

TestResult TestHeapDestroy1()/*test apply destroy twice*/
{
	Heap * newHeap;

	Vector * controler = VectorCreate(10, 2);
	if(NULL == controler)
	{
		return FAIL;
	}
	newHeap = HeapBuild(controler);
	if(NULL == newHeap)
	{
		return FAIL;
	}
	
	HeapDestroy(newHeap);
	HeapDestroy(newHeap);
	VectorDestroy(controler);
	
	return SUCCEED;
}
TestResult TestHeapDestroy2(ADTErr* status)/* create 2 build with the same vector delete one and check if the second is work*/
{
	Heap *newHeap, *secondHeap;
	int i;
	int arr[5] = { 3 , 11 , 8 , 17, 18};

	Vector * controler = VectorCreate(4, 2);
	if(NULL == controler)
	{
		return FAIL;
	}
	for(i = 0; i < 5 ; i++)
	{	
		*status |= VectorAdd(controler, arr[i]);
	}
	newHeap = HeapBuild(controler);
	secondHeap = HeapBuild(controler);
	if(NULL == newHeap || NULL == secondHeap)
	{
		return FAIL;
	}
	HeapDestroy(secondHeap);
	HeapItemsPrint(newHeap);

	HeapDestroy(newHeap);
	VectorDestroy(controler);
	
	return SUCCEED;

}


TestResult TestHeapDestroy3()/*test destroy vector first and use heap after*/
{
	Heap * newHeap;

	Vector * controler = VectorCreate(10, 2);
	if(NULL == controler)
	{
		return FAIL;
	}
	newHeap = HeapBuild(controler);
	if(NULL == newHeap)
	{
		return FAIL;
	}
	VectorDestroy(controler);
	HeapDestroy(newHeap);
	
	
	return SUCCEED;
}

TestResult TestInsert1(ADTErr* _status)/*insert to an empty heap that should be the max*/
{
	Heap * newHeap;
	int i;
	int arr[5] = { 3 , 11 , 8 , 17, 18};

	Vector * controler = VectorCreate(4, 2);
	if(NULL == controler)
	{
		return FAIL;
	}
	for(i = 0; i < 5 ; i++)
	{	
		*_status |= VectorAdd(controler, arr[i]);
	}

	newHeap = HeapBuild(controler);
	if(NULL == newHeap)
	{
		return FAIL;
	}

	*_status |= HeapInsert(newHeap, 50);

	HeapItemsPrint(newHeap);

	HeapDestroy(newHeap);
	VectorDestroy(controler);

	return *_status == ERR_OK ? SUCCEED: FAIL;

}

TestResult TestInsert2(ADTErr* _status)/*insert to an not empty heap*/
{
	Heap * newHeap;

	Vector * controler = VectorCreate(10, 2);
	if(NULL == controler)
	{
		return FAIL;
	}
	newHeap = HeapBuild(controler);
	if(NULL == newHeap)
	{
		return FAIL;
	}
	*_status |= HeapInsert(newHeap, 15);

	HeapItemsPrint(newHeap);

	HeapDestroy(newHeap);
	VectorDestroy(controler);

	return *_status == ERR_OK ? SUCCEED: FAIL;

}

TestResult TestInsert3(ADTErr* _status)/*insert more than one element to an not empty heap*/
{
	Heap * newHeap;
	int i;

	Vector * controler = VectorCreate(10, 2);
	if(NULL == controler)
	{
		return FAIL;
	}
	newHeap = HeapBuild(controler);
	if(NULL == newHeap)
	{
		return FAIL;
	}
	for(i = 10 ; i < 60; i += 11)
	{
		*_status |= HeapInsert(newHeap, i);
	}
	HeapItemsPrint(newHeap);
	HeapDestroy(newHeap);
	VectorDestroy(controler);

	return *_status == ERR_OK ? SUCCEED: FAIL;

}
TestResult TestExtractMax1(ADTErr* _status)/*extract of an empty heap*/
{
	Heap * newHeap;
	int max;

	Vector * controler = VectorCreate(10, 2);
	if(NULL == controler)
	{
		return FAIL;
	}
	newHeap = HeapBuild(controler);
	if(NULL == newHeap)
	{
		return FAIL;
	}
	*_status = HeapExtractMax(newHeap, &max);

	HeapDestroy(newHeap);
	VectorDestroy(controler);

	return *_status == ERR_EMPTY ? SUCCEED:FAIL; 
}

TestResult TestExtractMax2(ADTErr* _status)/*extract max of an heap*/
{
	Heap * newHeap;
	int i, max;
	int arr[5] = { 3 , 11 , 8 , 17, 18};

	Vector * controler = VectorCreate(4, 2);
	if(NULL == controler)
	{
		return FAIL;
	}

	*_status = VectorAdd(controler, 1);
	for(i = 0; i < 5 ; i++)
	{	
		*_status |= VectorAdd(controler, arr[i]);
	}

	newHeap = HeapBuild(controler);
	if(NULL == newHeap)
	{
		return FAIL;
	}

	*_status |= HeapInsert(newHeap, 50);
	HeapItemsPrint(newHeap);
	*_status |= HeapExtractMax(newHeap, &max);

	HeapItemsPrint(newHeap);

	printf("\n%d\n",max );

	HeapDestroy(newHeap);
	VectorDestroy(controler);

	return *_status == 50 ? SUCCEED: FAIL;

}


int main()
{
	ADTErr stat = 0;
	TestResult res;
	PrintResult("TestHeapBuild1", TestHeapBuild1(),ERR_OK);
	
	res = TestHeapBuild2(&stat);
	PrintResult("\nTestHeapBuild2", res,stat);

	PrintResult("TestHeapBuild3", TestHeapBuild3(),ERR_OK);
	PrintResult("TestHeapDestroy1", TestHeapDestroy1(),ERR_OK);

	res = TestHeapDestroy2(&stat);
	PrintResult("\nTestHeapBuild2", res,stat);
	PrintResult("TestHeapDestroy3", TestHeapDestroy3(),ERR_OK);

	res = TestInsert1(&stat);
	PrintResult("TestInsert1", res,stat);

	res = TestInsert2(&stat);
	PrintResult("TestInsert2", res,stat);

	res = TestInsert3(&stat);
	PrintResult("TestInsert3", res,stat);

	res = TestExtractMax1(&stat);
	PrintResult("TestExtractMax1", res,ERR_OK);

	res = TestExtractMax2(&stat);
	PrintResult("TestExtractMax2", res,ERR_OK);
	return 0;
}
