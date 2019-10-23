#include<stdlib.h>
#include<stdio.h>
#include"ADTErr.h"
#include"binarySearchTree.h"
#include"test.h"

void PrintResult(char* _testName, TestResult _result, ADTErr _stat)
{
	if(_stat != ERR_OK) printf("%s %s \n","test error of the", _testName );
	printf("%s\t%s\n",_testName, (_result == SUCCEED)? "succed": "failed" );
}



TestResult TestCreateBST()
{
	TestResult res;
	Tree* newTree = TreeCreate();
	if(newTree)
	{
	 	res = SUCCEED;
	}
	else
	{
		res = FAIL;
	}
	TreeDestroy(newTree);
	return res;

}

TestResult TestDestroy()
{
	Tree* newTree = TreeCreate();
	if(newTree)
	{
		TreeDestroy(newTree);
		TreeDestroy(newTree);
	}
	return SUCCEED;
}
TestResult TestInsert1(ADTErr* _status)/* insert one element */
{
	Tree* newTree = TreeCreate();
	if(!newTree)
	{
		*_status = ERR_ALLOCATION;
		return FAIL;
	}	
	if(*_status = TreeInsert(newTree, 10) != ERR_OK)
	{
		TreeDestroy(newTree);
		return FAIL; 
	
	}
	TreePrint(newTree, IN_ORDER);
	TreeDestroy(newTree);
	return SUCCEED;
}

TestResult TestInsert2(ADTErr* _status)/* insert more than one element */
{
	int arr[5] = {2, 3 , 4, 1 , 7};
	int i;
	Tree* newTree = TreeCreate();
	if(!newTree)
	{
		*_status = ERR_ALLOCATION;
		return FAIL;
	}
	for(i = 0; i < 5 ;i++)
	{
		*_status |= TreeInsert(newTree, arr[i]);
	}
	if(*_status != ERR_OK)
	{
		TreeDestroy(newTree);
		return FAIL; 
	}
	TreePrint(newTree, IN_ORDER);
	TreeDestroy(newTree);
	return SUCCEED;
}

TestResult Testsearch1()/*search data in the tree*/
{
	
	int arr[5] = {2, 3 , 4, 1 , 7};
	int i;
	Tree* newTree = TreeCreate();
	if(!newTree)
	{
		return FAIL;
	}
	for(i = 0; i < 5 ;i++)
	{
		TreeInsert(newTree, arr[i]);
	}
	if(TreeIsDataFound(newTree,4))
	{
		TreeDestroy(newTree);
 		return SUCCEED;
	}
	return FAIL;
}
TestResult Testsearch3()/*search data in the tree*/
{
	
	int arr[5] = {2, 3 , 4, 1 , 7};
	int i;
	Tree* newTree = TreeCreate();
	if(!newTree)
	{
		return FAIL;
	}
	for(i = 0; i < 5 ;i++)
	{
		TreeInsert(newTree, arr[i]);
	}
	if(TreeIsDataFound(newTree,1))
	{
		TreeDestroy(newTree);
 		return SUCCEED;
	}
	return FAIL;
}
TestResult Testsearch2()/*search data not in the tree*/
{
	
	int arr[5] = {2, 3 , 4, 1 , 7};
	int i;
	Tree* newTree = TreeCreate();
	if(!newTree)
	{
		return FAIL;
	}
	for(i = 0; i < 5 ;i++)
	{
		TreeInsert(newTree, arr[i]);
	}
	if(!TreeIsDataFound(newTree,17))
	{
		TreeDestroy(newTree);
 		return SUCCEED;
	}
	return FAIL;
}

TestResult Testsearch4()/*search data not in the tree but in a second tree*/
{
	
	int arr[5] = {2, 3 , 4, 1 , 7};
	int arr2[5] = { 11, 3, 6, 17, 15};
	int i;
	Tree* newTree = TreeCreate();
	Tree* tree2 = TreeCreate();
	if(!newTree || !tree2)
	{
		return FAIL;
	}
	for(i = 0; i < 5 ;i++)
	{
		TreeInsert(newTree, arr[i]);
		TreeInsert(tree2, arr2[i]);
	}
	if(!TreeIsDataFound(newTree,6))
	{
		TreeDestroy(newTree);
 		return SUCCEED;
	}
	return FAIL;
}

TestResult TestIsFullTree1(ADTErr* _status)
{
	int arr[5] = {2, 3 , 4, 1 , 7};
	int i;
	Tree* newTree = TreeCreate();
	if(!newTree)
	{
		return FAIL;
	}
	for(i = 0; i < 5 ;i++)
	{
		*_status = TreeInsert(newTree, arr[i]);
	}
	if(IsFullTree(newTree) == TRUE)
	{
		return FAIL;
	}
	return SUCCEED;
}

TestResult TestIsFullTree2(ADTErr* _status)
{
	int arr[5] = {10, 5 , 15, 3 , 7};
	int i;
	Tree* newTree = TreeCreate();
	if(!newTree)
	{
		return FAIL;
	}
	for(i = 0; i < 5 ;i++)
	{
		*_status = TreeInsert(newTree, arr[i]);
	}
	if(IsFullTree(newTree) == TRUE)
	{
		return SUCCEED;
	}
	return FAIL;
}


TestResult TestAreSimilareTrees1(ADTErr* _status)
{
	int arr[5] = {10, 5 , 15, 3 , 7};
	int i;
	Tree* tree1 = TreeCreate();
	Tree* tree2 = TreeCreate();
	if(!tree1 || !tree2)
	{
		return FAIL;
	}
	for(i = 0; i < 5 ;i++)
	{
		*_status = TreeInsert(tree1, arr[i]);
		*_status = TreeInsert(tree2, arr[i]);
	}
	if(AreSimilarTrees(tree1, tree2) == TRUE)
	{
		return SUCCEED;
	}
	return FAIL;
}

TestResult TestAreSimilareTrees2(ADTErr* _status)
{
	int arr[5] = {10, 5 , 15, 3 , 7};
	int i;
	Tree* tree1 = TreeCreate();
	Tree* tree2 = TreeCreate();
	if(!tree1 || !tree2)
	{
		return FAIL;
	}
	for(i = 0; i < 5 ;i++)
	{
		*_status = TreeInsert(tree1, arr[i]);
		*_status = TreeInsert(tree2, arr[i]);
	}
	*_status = TreeInsert(tree2, 1);
	if(  FALSE == AreSimilarTrees(tree1, tree2))
	{
		return SUCCEED;
	}
	return FAIL;
}