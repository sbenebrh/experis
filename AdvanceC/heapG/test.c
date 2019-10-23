#include<stdio.h>
#include <stdlib.h>
#include"test.h"
#include"vector.h"
#include"Heap.h"

#define CHECKVECTOR if(test == NULL) return FAIL;
#define CHECKHEAP	if(test == NULL){Vector_Destroy(&test,NULL); return FAIL;}
#define SIZE	16

int intCompare(const void* _a,const void* _b)
{
	return *(int*) _a < *(int*)_b;
}
void Delete(void* a)
{
	free(a);
}
TestResult fillVector(Vector* _vector)
{
	int i;
	int * arr = (int*)malloc(5*sizeof(int));
	arr[0] = 10;
	arr[1] = 1;
	arr[2] = 45;
	arr[3] = 8;
	arr[4] = 100;
	
	for(i = 0; i < 5; ++i)
	{
		if(Vector_Append(_vector, &arr[i]) != VECTOR_SUCCESS)
		{
			return FAIL;
		}
	}
	return SUCCEED;

}

TestResult TestHEAPBuild1()
{
	Heap* heapTest;
	Vector* test = Vector_Create(SIZE,SIZE);
	CHECKVECTOR

	heapTest = Heap_Build(test, intCompare);
	CHECKHEAP

	Heap_Destroy(&heapTest);
	Vector_Destroy(&test,NULL);
	return SUCCEED;


}

TestResult TestHEAPBuild2()
{
	Heap* heapTest;
	Vector* test = Vector_Create(SIZE,SIZE);
	CHECKVECTOR

	if(fillVector(test) != SUCCEED)
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}
	heapTest = Heap_Build(test, intCompare);
	CHECKHEAP
	Heap_Destroy(&heapTest);
	Vector_Destroy(&test,NULL);
	return SUCCEED;

}

TestResult TestHEAPBuild3()
{
	void* value;
	Heap* heapTest;
	int i;
	int arr[5] = { 10, 1, 45, 8, 100};

	Vector* test = Vector_Create(SIZE,SIZE);
	CHECKVECTOR
	for(i = 0; i < 5; ++i)
	{
		if(Vector_Append(test, &arr[i]) != VECTOR_SUCCESS)
		{
			return FAIL;
		}
	}
	heapTest = Heap_Build(test, intCompare);
	CHECKHEAP

	if(Vector_Get(test, 0, &value) != VECTOR_SUCCESS || (*(int*)value) != 100)
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	Heap_Destroy(&heapTest);
	Vector_Destroy(&test,NULL);
	return SUCCEED;


}
TestResult TestHEAPBuild4()
{
	void* value;
	Heap* heapTest;
	int i;
	int arr[10] = { 10, 1, 45, 8, 100,21,17,9,64,87};

	Vector* test = Vector_Create(SIZE,SIZE);
	CHECKVECTOR
	for(i = 0; i < 10; ++i)
	{
		if(Vector_Append(test, &arr[i]) != VECTOR_SUCCESS)
		{
			return FAIL;
		}
	}
	heapTest = Heap_Build(test, intCompare);
	CHECKHEAP

	if(Vector_Get(test, 0, &value) != VECTOR_SUCCESS || (*(int*)value) != 100)
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return FAIL;
	}


	Heap_Destroy(&heapTest);
	Vector_Destroy(&test,NULL);
	return SUCCEED;


}

TestResult TestHEAPDestroy1()
{
	Heap* heapTest;
	Vector* test = Vector_Create(SIZE,SIZE);
	CHECKVECTOR

	heapTest = Heap_Build(test, intCompare);
	CHECKHEAP

	Heap_Destroy(&heapTest);
	Vector_Destroy(&test,NULL);
	Vector_Destroy(&test,NULL);
	return SUCCEED;
}

TestResult TestHEAPDestroy2()
{
	void* value;
	Heap* heapTest;
	int i;
	int arr[5] = { 10, 1, 45, 8, 100};

	Vector* test = Vector_Create(SIZE,SIZE);
	CHECKVECTOR
	for(i = 0; i < 5; ++i)
	{
		if(Vector_Append(test, &arr[i]) != VECTOR_SUCCESS)
		{
			return FAIL;
		}
	}
	heapTest = Heap_Build(test, intCompare);
	CHECKHEAP

	if(Vector_Get(test, 0, &value) != VECTOR_SUCCESS || (*(int*)value) != 100)
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	Heap_Destroy(&heapTest);
	Vector_Destroy(&test,NULL);
	Heap_Destroy(&heapTest);
	return SUCCEED;


}

TestResult TestHEAPInsert1()
{
	Heap* heapTest;
	int a = 10;
	void* value;
	Vector* test = Vector_Create(SIZE,SIZE);
	CHECKVECTOR

	heapTest = Heap_Build(test, intCompare);
	CHECKHEAP
	if(Heap_Insert(heapTest,&a) != HEAP_SUCCESS)
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return FAIL;
	}
	if(Vector_Get(test, 0, &value) != VECTOR_SUCCESS || (*(int*)value) != 10)
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return FAIL;
	}
	Heap_Destroy(&heapTest);
	Vector_Destroy(&test,NULL);
	
	return SUCCEED;
}

TestResult TestHEAPInsert2()
{
	int a =0;
	void* value;
	Heap* heapTest;
	int i;
	int arr[10] = { 10, 1, 45, 8, 100,21,17,9,64,87};

	Vector* test = Vector_Create(SIZE,SIZE);
	CHECKVECTOR
	for(i = 0; i < 10; ++i)
	{
		if(Vector_Append(test, &arr[i]) != VECTOR_SUCCESS)
		{
			return FAIL;
		}
	}
	heapTest = Heap_Build(test, intCompare);
	CHECKHEAP

	if(Heap_Insert(heapTest,&a) != HEAP_SUCCESS)
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	if(Vector_Get(test, 10, &value) != VECTOR_SUCCESS || (*(int*)value) != 0)
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return FAIL;
	}


	Heap_Destroy(&heapTest);
	Vector_Destroy(&test,NULL);
	return SUCCEED;


}

TestResult TestHEAPInsert3()
{
	int a =60;
	void* value;
	Heap* heapTest;
	int i;
	int arr[10] = { 10, 1, 45, 8, 100,21,17,9,64,87};

	Vector* test = Vector_Create(SIZE,SIZE);
	CHECKVECTOR
	for(i = 0; i < 10; ++i)
	{
		if(Vector_Append(test, &arr[i]) != VECTOR_SUCCESS)
		{
			return FAIL;
		}
	}
	heapTest = Heap_Build(test, intCompare);
	CHECKHEAP

	if(Heap_Insert(heapTest,&a) != HEAP_SUCCESS)
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	if(Vector_Get(test, 0, &value) != VECTOR_SUCCESS || (*(int*)value) !=100)
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return FAIL;
	}


	Heap_Destroy(&heapTest);
	Vector_Destroy(&test,NULL);
	return SUCCEED;


}

TestResult TestHEAPInsert4()
{
	int a =500;
	void* value;
	Heap* heapTest;
	int i;
	int arr[10] = { 10, 1, 45, 8, 100,21,17,9,64,87};

	Vector* test = Vector_Create(SIZE,SIZE);
	CHECKVECTOR
	for(i = 0; i < 10; ++i)
	{
		if(Vector_Append(test, &arr[i]) != VECTOR_SUCCESS)
		{
			return FAIL;
		}
	}
	heapTest = Heap_Build(test, intCompare);
	CHECKHEAP

	if(Heap_Insert(heapTest,&a) != HEAP_SUCCESS)
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	if(Vector_Get(test, 0, &value) != VECTOR_SUCCESS || (*(int*)value) !=500)
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return FAIL;
	}


	Heap_Destroy(&heapTest);
	Vector_Destroy(&test,NULL);
	return SUCCEED;


}

TestResult TestHEAPPeak1()
{
	Heap* heapTest;
	Vector* test = Vector_Create(SIZE,SIZE);
	CHECKVECTOR

	heapTest = Heap_Build(test, intCompare);
	CHECKHEAP
	if(NULL == Heap_Peek(heapTest))
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return SUCCEED;		
	}
	Heap_Destroy(&heapTest);
	Vector_Destroy(&test,NULL);
	return FAIL;
}

TestResult TestHEAPPeak2()
{
	void* value;
	Heap* heapTest;
	int i;
	int arr[10] = { 10, 1, 45, 8, 100,21,17,9,64,87};

	Vector* test = Vector_Create(SIZE,SIZE);
	CHECKVECTOR
	for(i = 0; i < 10; ++i)
	{
		if(Vector_Append(test, &arr[i]) != VECTOR_SUCCESS)
		{
			return FAIL;
		}
	}
	heapTest = Heap_Build(test, intCompare);
	CHECKHEAP

	if(Vector_Get(test, 0, &value) != VECTOR_SUCCESS || value != Heap_Peek(heapTest))
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return FAIL;
	}


	Heap_Destroy(&heapTest);
	Vector_Destroy(&test,NULL);
	return SUCCEED;


}

TestResult TestHEAPPeak3()
{
	int a =500;
	void* value;
	Heap* heapTest;
	int i;
	int arr[10] = { 10, 1, 45, 8, 100,21,17,9,64,87};

	Vector* test = Vector_Create(SIZE,SIZE);
	CHECKVECTOR
	for(i = 0; i < 10; ++i)
	{
		if(Vector_Append(test, &arr[i]) != VECTOR_SUCCESS)
		{
			return FAIL;
		}
	}
	heapTest = Heap_Build(test, intCompare);
	CHECKHEAP

	if(Heap_Insert(heapTest,&a) != HEAP_SUCCESS)
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	if(Vector_Get(test, 0, &value) != VECTOR_SUCCESS || value !=Heap_Peek(heapTest))
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return FAIL;
	}


	Heap_Destroy(&heapTest);
	Vector_Destroy(&test,NULL);
	return SUCCEED;


}

TestResult TestHEAPPeakEx1()
{
	Heap* heapTest;
	Vector* test = Vector_Create(SIZE,SIZE);
	CHECKVECTOR

	heapTest = Heap_Build(test, intCompare);
	CHECKHEAP
	if(NULL == Heap_Extract(heapTest))
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return SUCCEED;		
	}
	Heap_Destroy(&heapTest);
	Vector_Destroy(&test,NULL);
	return FAIL;
}

TestResult TestHEAPPeakEx2()
{
	void* value;
	Heap* heapTest;
	int i;
	int arr[10] = { 10, 1, 45, 8, 100,21,17,9,64,87};

	Vector* test = Vector_Create(SIZE,SIZE);
	CHECKVECTOR
	for(i = 0; i < 10; ++i)
	{
		if(Vector_Append(test, &arr[i]) != VECTOR_SUCCESS)
		{
			return FAIL;
		}
	}
	heapTest = Heap_Build(test, intCompare);
	CHECKHEAP

	if(Vector_Get(test, 0, &value) != VECTOR_SUCCESS || value != Heap_Extract(heapTest))
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return FAIL;
	}


	Heap_Destroy(&heapTest);
	Vector_Destroy(&test,NULL);
	return SUCCEED;


}

TestResult TestHEAPPeakEx3()
{
	void* value;
	Heap* heapTest;
	int i;
	int arr[10] = { 10, 1, 45, 8, 100,21,17,9,64,87};

	Vector* test = Vector_Create(SIZE,SIZE);
	CHECKVECTOR
	for(i = 0; i < 10; ++i)
	{
		if(Vector_Append(test, &arr[i]) != VECTOR_SUCCESS)
		{
			return FAIL;
		}
	}
	heapTest = Heap_Build(test, intCompare);
	CHECKHEAP

	if(Vector_Get(test, 0, &value) != VECTOR_SUCCESS || value != Heap_Extract(heapTest)||*(int*)Heap_Peek(heapTest) != 87)
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return FAIL;
	}


	Heap_Destroy(&heapTest);
	Vector_Destroy(&test,NULL);
	return SUCCEED;


}

TestResult TestHEAPSize1()
{
	Heap* heapTest;
	Vector* test = Vector_Create(SIZE,SIZE);
	CHECKVECTOR

	

	heapTest = Heap_Build(test, intCompare);
	CHECKHEAP
	if(Heap_Size(test) != 0)
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return FAIL;
	}
	Heap_Destroy(&heapTest);
	Vector_Destroy(&test,NULL);
	return SUCCEED;

}

TestResult TestHEAPSize2()
{
	Heap* heapTest;
	Vector* test = Vector_Create(SIZE,SIZE);
	CHECKVECTOR

	if(fillVector(test) != SUCCEED)
	{
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	heapTest = Heap_Build(test, intCompare);
	CHECKHEAP
	if(Heap_Size(test) != 5)
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return FAIL;
	}
	Heap_Destroy(&heapTest);
	Vector_Destroy(&test,NULL);
	return SUCCEED;

}

TestResult TestHEAPInsert114()
{
	int a =500;
	void* value;
	Heap* heapTest;
	int i;
	int arr[10] = { 10, 1, 45, 8, 100,21,17,9,64,87};

	Vector* test = Vector_Create(SIZE,SIZE);
	CHECKVECTOR
	heapTest = Heap_Build(test, intCompare);
	CHECKHEAP
	for(i = 0; i < 10; ++i)
	{
		if(Heap_Insert(heapTest,  &arr[i]) != 0)
		{
			return FAIL;
		}
	}

	if(Heap_Insert(heapTest,&a) != HEAP_SUCCESS)
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return FAIL;
	}

	if(Vector_Get(test, 0, &value) != VECTOR_SUCCESS || (*(int*)value) !=500)
	{
		Heap_Destroy(&heapTest);
		Vector_Destroy(&test,NULL);
		return FAIL;
	}


	Heap_Destroy(&heapTest);
	Vector_Destroy(&test,NULL);
	return SUCCEED;


}
