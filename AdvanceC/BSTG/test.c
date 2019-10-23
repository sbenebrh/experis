#include<stdlib.h>
#include "stdio.h"
#include"bin_tree.h"
#include"test.h"
int intComparator(void* _left, void* _right)
{
	return *(int*) _left < *(int*)_right;
}
int morethan5(void* _a, void* _b)
{
	return *(int*)_a > 5;
}
int morethan15(void* _a, void* _b)
{
	return *(int*)_a > 15;
}
int printint(void* _a, void* _b)
{
	printf("%d\n", *(int*)_a ); 
}
TestResult TestBstCreate1()
{
	TestResult result;
	BSTree* bstTest = BSTree_Create(intComparator);
	result = (bstTest == NULL ? FAIL: SUCCEED);
	BSTree_Destroy(&bstTest,NULL);
	return result;
}

TestResult TestBstDestroy1()
{
	TestResult result;
	BSTree* bstTest = BSTree_Create(intComparator);
	result = (bstTest == NULL ? FAIL: SUCCEED);
	BSTree_Destroy(&bstTest,NULL);
	return result;
}

TestResult TestBstDestroy2()
{
	TestResult result;
	BSTree* bstTest = BSTree_Create(intComparator);
	result = (bstTest == NULL ? FAIL: SUCCEED);
	BSTree_Destroy(&bstTest,NULL);
	BSTree_Destroy(&bstTest,NULL);
	return result;
}

TestResult TestBstInsert1()
{
	int a = 10;
	TestResult result = SUCCEED;
	BSTree* bstTest = BSTree_Create(intComparator);
	if(NULL == bstTest)
	{
		return FAIL;
	}
	BSTree_Insert(bstTest, &a);
	BSTree_Destroy(&bstTest,NULL);
	return result;
}

TestResult TestBstInsert2()
{
	int i;
	int a[10] = {1,3,8,2,4,5,11,9,6};
	TestResult result = SUCCEED;

	BSTree* bstTest = BSTree_Create(intComparator);
	if(NULL == bstTest)
	{
		return FAIL;
	}
	for(i = 0; i < 9;++i)
	{
		BSTree_Insert(bstTest, &a[i]);
	}
	BSTree_Destroy(&bstTest,NULL);
	return result;
}

TestResult TestBstInsert3()
{
	int i;
	int a[10] = {5,3,8,2,4,1,11,9,6};
	TestResult result = SUCCEED;

	BSTree* bstTest = BSTree_Create(intComparator);
	if(NULL == bstTest)
	{
		return FAIL;
	}
	for(i = 0; i < 9;++i)
	{
		BSTree_Insert(bstTest, &a[i]);
	}
	BSTree_Destroy(&bstTest,NULL);
	return result;
}

TestResult TestBstFindFirst1()
{
	int i;
	int a[10] = {1,3,8,2,4,5,11,9,6};
	TestResult result = SUCCEED;

	BSTree* bstTest = BSTree_Create(intComparator);
	if(NULL == bstTest)
	{
		return FAIL;
	}
	for(i = 0; i < 9;++i)
	{
		BSTree_Insert(bstTest, &a[i]);
	}
	if(BSTreeItr_Get(BSTree_FindFirst(bstTest,morethan5,NULL)) == &a[8])
	{
		BSTree_Destroy(&bstTest,NULL);
		return result;
	}
	BSTree_Destroy(&bstTest,NULL);
	return FAIL;
}

TestResult TestBstFindFirst2()
{
	BSTree* bstTest = BSTree_Create(intComparator);
	if(NULL == bstTest)
	{
		return FAIL;
	}
	if(NULL == BSTree_FindFirst(bstTest,morethan5,NULL))
	{
		BSTree_Destroy(&bstTest,NULL);
		return SUCCEED;
	}
	BSTree_Destroy(&bstTest,NULL);
	return FAIL;

}

TestResult TestBstFindFirst3()
{
	int i;
	int a[10] = {1,3,8,2,4,5,11,9,6};
	TestResult result = FAIL;

	BSTree* bstTest = BSTree_Create(intComparator);
	if(NULL == bstTest)
	{
		return FAIL;
	}
	for(i = 0; i < 9;++i)
	{
		BSTree_Insert(bstTest, &a[i]);
	}
	if(BSTree_FindFirst(bstTest,morethan15,NULL) == BSTreeItr_End(bstTest))
	{
		result = SUCCEED;
	}
	BSTree_Destroy(&bstTest,NULL);
	return result;
}

TestResult TestBstBegin1()
{
	TestResult result = FAIL;
	BSTree* bstTest = BSTree_Create(intComparator);
	if(NULL == bstTest)
	{
		return FAIL;
	}

	if(BSTreeItr_Begin(bstTest) == BSTreeItr_End(bstTest))
	{
		result = SUCCEED;
	}

	BSTree_Destroy(&bstTest,NULL);
	return result;
}

TestResult TestBstBegin2()
{
	int i;
	int a[10] = {1,3,8,2,4,5,11,9,6};
	TestResult result = FAIL;
	BSTree* bstTest = BSTree_Create(intComparator);
	if(NULL == bstTest)
	{
		return FAIL;
	}

	for(i = 0; i < 9;++i)
	{
		BSTree_Insert(bstTest, &a[i]);
	}

	if(BSTreeItr_Get(BSTreeItr_Begin(bstTest)) == &a[0])
	{
		result = SUCCEED;
	}

	BSTree_Destroy(&bstTest,NULL);
	return result;
}

TestResult TestBstBegin3()
{
	int i;
	int a[10] = {3,2,8,1,4,5,11,9,6};
	TestResult result = FAIL;
	BSTree* bstTest = BSTree_Create(intComparator);
	if(NULL == bstTest)
	{
		return FAIL;
	}

	for(i = 0; i < 9;++i)
	{
		BSTree_Insert(bstTest, &a[i]);
	}

	if(BSTreeItr_Get(BSTreeItr_Begin(bstTest)) == &a[3])
	{
		result = SUCCEED;
	}

	BSTree_Destroy(&bstTest,NULL);
	return result;
}

TestResult TestBstEqual1()
{
	TestResult result = FAIL;
	BSTree* bstTest = BSTree_Create(intComparator);
	if(NULL == bstTest)
	{
		return FAIL;
	}
	if(BSTreeItr_Equals(BSTreeItr_Begin(bstTest), BSTreeItr_End(bstTest)) == 1)
	{
		result = SUCCEED;
	}
	BSTree_Destroy(&bstTest,NULL);
	return result;
}
TestResult TestBstEqual2()
{
	int i;
	int a[10] = {3,2,8,1,4,5,11,9,6};
	TestResult result = FAIL;
	BSTree* bstTest = BSTree_Create(intComparator);
	if(NULL == bstTest)
	{
		return FAIL;
	}

	for(i = 0; i < 9;++i)
	{
		BSTree_Insert(bstTest, &a[i]);
	}

	if(BSTreeItr_Equals(BSTreeItr_Begin(bstTest), BSTreeItr_End(bstTest)) == 0)
	{
		result = SUCCEED;
	}

	BSTree_Destroy(&bstTest,NULL);
	return result;
}
TestResult TestBstForEach1()
{
	int i;
	int a[10] = {3,2,8,1,4,5,11,9,6};
	TestResult result = FAIL;
	BSTree* bstTest = BSTree_Create(intComparator);
	if(NULL == bstTest)
	{
		return FAIL;
	}

	for(i = 0; i < 9;++i)
	{
		BSTree_Insert(bstTest, &a[i]);
	}

	if(BSTree_ForEach(bstTest, BSTREE_TRAVERSAL_INORDER,printint,NULL))
	{
		result = SUCCEED;
	}

	BSTree_Destroy(&bstTest,NULL);
	return result;
}