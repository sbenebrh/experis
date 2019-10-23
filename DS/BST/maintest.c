#include<stdlib.h>
#include<stdio.h>
#include"ADTErr.h"
#include"binarySearchTree.h"
#include"test.h"


int main()
{
	ADTErr status ;
	TestResult res;

	PrintResult("TestCreateBST", TestCreateBST(),ERR_OK);
	PrintResult("TestDestroy", TestDestroy(),ERR_OK);

	res = TestInsert1(&status);
	PrintResult("TestInsert1", res, status);

	res = TestInsert2(&status);
	PrintResult("TestInsert2", res, status);

	PrintResult("Testsearch1", Testsearch1(),ERR_OK);
	PrintResult("Testsearch2", Testsearch2(),ERR_OK);
	PrintResult("Testsearch3", Testsearch3(),ERR_OK);
	PrintResult("Testsearch4", Testsearch3(),ERR_OK);


	res = TestIsFullTree1(&status);
	PrintResult("TestIsFullTree1", res, status);

	res = TestIsFullTree2(&status);
	PrintResult("TestIsFullTree2", res, status);

	res = TestAreSimilareTrees1(&status);
	PrintResult("TestAreSimilareTrees1", res, status);

	res = TestAreSimilareTrees2(&status);
	PrintResult("TestAreSimilareTrees2", res, status);
	return 0;
}
