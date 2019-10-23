#include<stdio.h>
#include"list_itr.h"
#include"../list.h"
#include"test.h"
#include"list_functions.h"


int equalToTen(void* _element, void* _context)
{
	void* b;
	b = ListItr_Get(_element);
	return *(int*)b == 10;
}

int PrintInt(void* _element, void* _context)
{
	void* b;
	b = ListItr_Get(_element);
	printf("%d\n", *(int*)b);
	return 1;
}

TestResult TestItrBegin()
{
	void* begin;
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	begin = ListItr_Begin(test);
	if(NULL == begin)
	{
		List_Destroy(&test, NULL);
		return FAIL;
	}
	List_Destroy(&test, NULL);
	return SUCCEED;

}

TestResult TestItrEnd()
{
	void* begin;
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	begin = ListItr_End(test);
	if(NULL == begin)
	{
		List_Destroy(&test, NULL);
		return FAIL;
	}
	List_Destroy(&test, NULL);
	return SUCCEED;

}

TestResult TestItrEqual1()
{
	
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(ListItr_Equals(ListItr_Begin(test),ListItr_End(test)) == 1)
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	
	List_Destroy(&test, NULL);
	return FAIL;

}

TestResult TestItrEqual2()
{
	int a = 9;
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(List_PushHead(test, &a) != LIST_SUCCESS)
	{
		List_Destroy(&test, NULL);
		return FAIL;
	}
	if(ListItr_Equals(ListItr_Begin(test),ListItr_End(test)) == 0)
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	
	List_Destroy(&test, NULL);
	return FAIL;

}

TestResult TestItrNext1()
{
	
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(ListItr_Equals(ListItr_Next(ListItr_Begin(test)),ListItr_End(test)) == 1)
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	
	List_Destroy(&test, NULL);
	return FAIL;

}

TestResult TestItrNext2()
{
	
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(ListItr_Equals(ListItr_Next(ListItr_End(test)),ListItr_End(test)) == 1)
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	
	List_Destroy(&test, NULL);
	return FAIL;

}

TestResult TestItrNext3()
{

	int a = 9;
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(List_PushHead(test, &a) != LIST_SUCCESS)
	{
		List_Destroy(&test, NULL);
		return FAIL;
	}
	if(ListItr_Equals(ListItr_Next(ListItr_Begin(test)),ListItr_End(test)) == 1)
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	
	List_Destroy(&test, NULL);
	return FAIL;

}


TestResult TestItrPrev1()
{
	
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(ListItr_Equals(ListItr_Prev(ListItr_Begin(test)),ListItr_End(test)) == 1)
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	
	List_Destroy(&test, NULL);
	return FAIL;

}

TestResult TestItrPrev2()
{
	
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(ListItr_Equals(ListItr_Prev(ListItr_Begin(test)),ListItr_Begin(test)) == 1)
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	
	List_Destroy(&test, NULL);
	return FAIL;

}

TestResult TestItrPrev3()
{

	int a = 9;
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(List_PushHead(test, &a) != LIST_SUCCESS)
	{
		List_Destroy(&test, NULL);
		return FAIL;
	}
	if(ListItr_Equals(ListItr_Prev(ListItr_End(test)),ListItr_End(test)) == 0)
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	
	List_Destroy(&test, NULL);
	return FAIL;

}
TestResult TestItrPrev4()
{

	int a = 9;
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(List_PushHead(test, &a) != LIST_SUCCESS)
	{
		List_Destroy(&test, NULL);
		return FAIL;
	}
	if(ListItr_Equals(ListItr_Prev(ListItr_End(test)),ListItr_Begin(test)) == 1)
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	
	List_Destroy(&test, NULL);
	return FAIL;

}

TestResult TestItrGet1()
{
	
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(NULL==ListItr_Get(ListItr_Begin(test)))
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	List_Destroy(&test, NULL);
	return FAIL;

}

TestResult TestItrGet2()
{
	int a = 9;
	void* b;
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(List_PushHead(test, &a) != LIST_SUCCESS)
	{
		List_Destroy(&test, NULL);
		return FAIL;
	}
	b = ListItr_Get(ListItr_Begin(test));
	if(b && *(int*)b == 9)
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	
	List_Destroy(&test, NULL);
	return FAIL;

}


TestResult TestItrSet1()
{
	void* b ;
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(NULL==ListItr_Set(ListItr_Begin(test),b))
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	List_Destroy(&test, NULL);
	return FAIL;

}

TestResult TestItrSet2()
{
	int a = 9;
	int b = 10;
	void* c;
	void* d;
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(List_PushHead(test, &a) != LIST_SUCCESS)
	{
		List_Destroy(&test, NULL);
		return FAIL;
	}
	d = ListItr_Begin(test);
	c = ListItr_Set(d,&b);
	if(*(int*)c == 9)
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	
	List_Destroy(&test, NULL);
	return FAIL;

}

TestResult TestItrInsert1()
{
	int a = 9;

	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(ListItr_InsertBefore(ListItr_Begin(test),&a) == NULL)
	{
		List_Destroy(&test, NULL);
		return FAIL;
	}
	
	List_Destroy(&test, NULL);
	return SUCCEED;

}

TestResult TestItrInsert2()
{
	int a = 9;

	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(ListItr_InsertBefore(ListItr_Begin(test),&a) == NULL)
	{
		List_Destroy(&test, NULL);
		return FAIL;
	}

	if(ListItr_Equals(ListItr_Begin(test),ListItr_End(test)) == 0)
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	
	List_Destroy(&test, NULL);
	return FAIL;

}

TestResult TestItrRemove1()
{

	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(ListItr_Remove(ListItr_Begin(test)) == NULL)
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	
	List_Destroy(&test, NULL);
	return FAIL;

}

TestResult TestItrRemove2()
{
	int a = 10;
	void* b;
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(ListItr_InsertBefore(ListItr_Begin(test),&a) == NULL)
	{
		List_Destroy(&test, NULL);
		return FAIL;
	}
	b = ListItr_Remove(ListItr_Begin(test));
	if( b == NULL)
	{
		List_Destroy(&test, NULL);
		return FAIL;
	}
	if(*(int*)b = 10)
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	
	List_Destroy(&test, NULL);
	return FAIL;

}

/*********************TEST FUNCTIONS ON ITR**************************/

TestResult TestFindFirst1()
{
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(ListItr_Equals( ListItr_FindFirst(ListItr_Begin(test),ListItr_End(test),equalToTen,NULL),ListItr_End(test)))
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	List_Destroy(&test, NULL);
	return FAIL;
}

TestResult TestFindFirst2()
{
	int a = 10;
	void* b;
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(ListItr_InsertBefore(ListItr_Begin(test),&a) == NULL)
	{
		List_Destroy(&test, NULL);
		return FAIL;
	}
	b = ListItr_Get(ListItr_Begin(test));
	if(b && *(int*)b != 10)
	{
		List_Destroy(&test, NULL);
		return FAIL;
	} 
	if(ListItr_Equals( ListItr_FindFirst(ListItr_Begin(test),ListItr_End(test),equalToTen,NULL),ListItr_Begin(test)))
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	List_Destroy(&test, NULL);
	return FAIL;
}

TestResult TestFindFirst3()
{
	int a = 9;
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(ListItr_InsertBefore(ListItr_Begin(test),&a) == NULL)
	{
		List_Destroy(&test, NULL);
		return FAIL;
	}
	if(ListItr_Equals( ListItr_FindFirst(ListItr_Begin(test),ListItr_End(test),equalToTen,NULL),ListItr_End(test)))
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	List_Destroy(&test, NULL);
	return FAIL;
}

TestResult TestForEach1()
{
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(ListItr_Equals( ListItr_ForEach(ListItr_Begin(test),ListItr_End(test),PrintInt,NULL),ListItr_End(test)))
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	List_Destroy(&test, NULL);
	return FAIL;
}



TestResult TestForEach2()
{
	int a = 9;
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(ListItr_InsertBefore(ListItr_Begin(test),&a) == NULL)
	{
		List_Destroy(&test, NULL);
		return FAIL;
	}
	if(ListItr_Equals( ListItr_ForEach(ListItr_Begin(test),ListItr_End(test),PrintInt,NULL),ListItr_Begin(test)))
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	List_Destroy(&test, NULL);
	return FAIL;
}

TestResult TestCount1()
{
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(0 ==ListItr_CountIf(ListItr_Begin(test),ListItr_End(test),equalToTen,NULL))
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	List_Destroy(&test, NULL);
	return FAIL;
}

TestResult TestCount2()
{
	int a = 9;
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(ListItr_InsertBefore(ListItr_Begin(test),&a) == NULL)
	{
		List_Destroy(&test, NULL);
		return FAIL;
	}
	if(0 ==ListItr_CountIf(ListItr_Begin(test),ListItr_End(test),equalToTen,NULL))
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	List_Destroy(&test, NULL);
	return FAIL;
}

TestResult TestCount3()
{
	int a = 10;
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(ListItr_InsertBefore(ListItr_Begin(test),&a) == NULL)
	{
		List_Destroy(&test, NULL);
		return FAIL;
	}
	if(1 ==ListItr_CountIf(ListItr_Begin(test),ListItr_End(test),equalToTen,NULL))
	{
		List_Destroy(&test, NULL);
		return SUCCEED;
	}
	List_Destroy(&test, NULL);
	return FAIL;
}

TestResult TestCut1()
{
	List* cut;
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	cut = ListItr_Cut(ListItr_Begin(test),ListItr_End(test));
	if(ListItr_Equals(ListItr_Begin(cut),ListItr_End(cut)) == 1)
	{
		List_Destroy(&test, NULL);
		List_Destroy(&cut, NULL);
  
		return SUCCEED;
	}

	List_Destroy(&test, NULL);
	List_Destroy(&cut, NULL);

	return FAIL;
}

TestResult TestCut2()
{
	int a = 10;
	List* cut;
	List* test = List_Create();
	if(NULL == test)
	{
		return FAIL;
	}
	if(ListItr_InsertBefore(ListItr_Begin(test),&a) == NULL)
	{
		List_Destroy(&cut, NULL);
		List_Destroy(&test, NULL);
		return FAIL;
	}	
	cut = ListItr_Cut(ListItr_Begin(test),ListItr_End(test));
	if(ListItr_Equals(ListItr_Begin(cut),ListItr_End(cut)) == 0  && ListItr_Equals(ListItr_Begin(test),ListItr_End(test)) == 1)
	{
		List_Destroy(&test, NULL);
		List_Destroy(&cut, NULL);
  
		return SUCCEED;
	}

	List_Destroy(&test, NULL);
	List_Destroy(&cut, NULL);

	return FAIL;
}