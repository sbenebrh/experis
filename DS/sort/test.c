#include"sorts.h"
#include "vector.h"
#include "ADTErr.h"
#include<stdio.h>
#include<time.h>
#define SIZE 5


static void PrintResult(char* _testName, TestResult _result, ADTErr _stat)
{
	if(_stat != ERR_OK) printf("%s %s \n","test error of the", _testName );
	printf("%s\t%s\n",_testName, (_result == SUCCEED)? "succed": "failed" );
}

TestResult TestBubbleSort(ADTErr* _status)
{
	int i;
	clock_t timer;
	double execution;
	int num;
	Vector* newVector = VectorCreate(50000, SIZE);

	if(NULL == newVector)
	{
		return FAIL;
	}
	for( i = 0; i <50000 ; ++i)
	{
		num = rand() % 1000 + 1;
		*_status != VectorAdd(newVector , num);
	}
	timer = clock();

	*_status = BubbleSort(newVector);

	timer = clock() - timer;
	execution = ((double)timer / CLOCKS_PER_SEC);
	
	printf("\n");
	printf("%f\n",execution );

	VectorDestroy(newVector);

	return ERR_OK;

}

TestResult TestShakeSort(ADTErr* _status)
{
	int i;
	clock_t timer;
	double execution;
	int num;
	Vector* newVector = VectorCreate(1000, 500);

	if(NULL == newVector)
	{
		return FAIL;
	}
	for( i = 0; i <1000 ; ++i)
	{
		num = rand() % 999 + 1;
		*_status |= VectorAdd(newVector , num);
	}
	timer = clock();

	*_status = RadixSort(newVector, 3);

	timer = clock() - timer;
	execution = ((double)timer / CLOCKS_PER_SEC);
	
	printf("\n");
	printf("%f\n",execution );

	VectorDestroy(newVector);

	return ERR_OK;

}

TestResult TestQuickRec(ADTErr* _status)
{
	int i;
	Vector* newVector = VectorCreate(SIZE, SIZE);
	int arr[5] = { 6, 21, 3, 17, 9};
	if(NULL == newVector)
	{
		return FAIL;
	}
	for( i = 0; i < 5; ++i)
	{
		*_status |= VectorAdd(newVector , arr[i]);
	}
	VectorPrint(newVector);
	printf("\n");
	*_status = QuickSort(newVector, 1);
	VectorPrint(newVector);	
	printf("\n");

	VectorDestroy(newVector);

	return ERR_OK;

}
TestResult TestQuickNR(ADTErr* _status)
{
	int i;
	Vector* newVector = VectorCreate(SIZE, SIZE);
	int arr[5] = { 6, 21, 3, 17, 9};
	if(NULL == newVector)
	{
		return FAIL;
	}
	for( i = 0; i < 5; ++i)
	{
		*_status |= VectorAdd(newVector , arr[i]);
	}
	VectorPrint(newVector);
	printf("\n");
	*_status = QuickSort(newVector, 0);
	VectorPrint(newVector);	
	printf("\n");

	VectorDestroy(newVector);

	return ERR_OK;

}

TestResult TestInsertion(ADTErr* _status)
{
	int i;
	Vector* newVector = VectorCreate(SIZE, SIZE);
	int arr[5] = { 6, 21, 3, 17, 9};
	if(NULL == newVector)
	{
		return FAIL;
	}
	for( i = 0; i < 5; ++i)
	{
		*_status |= VectorAdd(newVector , arr[i]);
	}
	VectorPrint(newVector);
	printf("\n");
	*_status = InsertionSort(newVector);
	VectorPrint(newVector);	
	printf("\n");

	VectorDestroy(newVector);

	return ERR_OK;

}

TestResult TestSelectionSort(ADTErr* _status)
{
	int i;
	Vector* newVector = VectorCreate(SIZE, SIZE);
	int arr[10] = {229, 311, 117, 786, 125, 453, 989, 532, 748, 153};
	if(NULL == newVector)
	{
		return FAIL;
	}
	for( i = 0; i < 10; ++i)
	{
		*_status |= VectorAdd(newVector , arr[i]);
	}
	VectorPrint(newVector);
	printf("\n");
	*_status = RadixSort(newVector, 3);
	VectorPrint(newVector);	
	printf("\n");

	VectorDestroy(newVector);

	return ERR_OK;

}

TestResult TestShellSort(ADTErr* _status)
{
	int i;
	clock_t timer;
	double execution;
	int num;
	Vector* newVector = VectorCreate(10000, SIZE);
	
	if(NULL == newVector)
	{
		return FAIL;
	}
	for( i = 0; i < 10000; ++i)
	{
		num = rand() % 1000 + 1;
		*_status |= VectorAdd(newVector , num);
	}
	
	
	
	printf("\n\n");
	timer = clock();

	*_status = ShellSortByInser(newVector);
	timer = clock() - timer;
	execution = ((double)timer / CLOCKS_PER_SEC);
	
	printf("\n");
	printf("%f\n",execution );
	
	

	VectorDestroy(newVector);

	return ERR_OK;

}

TestResult TestMergeSortRec(ADTErr* _status)
{
	int i;
	Vector* newVector = VectorCreate(SIZE, SIZE);
	int arr[6] = { 6, 21, 3, 17, 9, 1};
	if(NULL == newVector)
	{
		return FAIL;
	}
	for( i = 0; i < 6; ++i)
	{
		*_status |= VectorAdd(newVector , arr[i]);
	}
	VectorPrint(newVector);
	printf("\n");
	*_status = MergeSort(newVector, 1);
	VectorPrint(newVector);	
	printf("\n");

	VectorDestroy(newVector);

	return ERR_OK;

}

TestResult TestMergeSortNR(ADTErr* _status)
{
	int i;
	Vector* newVector = VectorCreate(SIZE, SIZE);
	int arr[6] = { 6, 21, 3, 17, 9, 1};
	if(NULL == newVector)
	{
		return FAIL;
	}
	for( i = 0; i < 6; ++i)
	{
		*_status |= VectorAdd(newVector , arr[i]);
	}
	VectorPrint(newVector);
	printf("\n");
	*_status = MergeSort(newVector, 0);
	VectorPrint(newVector);	
	printf("\n");

	VectorDestroy(newVector);

	return ERR_OK;

}

double recordTime(int _functions, int _j)
{
	int i;
	clock_t timer;
	double execution;
	int num;
	Vector* newVector = VectorCreate(_j, _j/2);
	if(NULL == newVector)
	{
		return ERR_UNINITIALIZED;
	}

		for( i = 0; i < _j; ++i)
	{
		num = rand() % 1000 + 1;
		VectorAdd(newVector , num);
	}
	switch(_functions)
	{
		case 0:
			timer = clock();
			BubbleSort(newVector);
			timer = clock() - timer;
			break;
		case 1:
			timer = clock();
			ShakeSort(newVector);
			timer = clock() - timer;
			break;
		case 2:
			timer = clock();
			QuickSort(newVector, 1);
			timer = clock() - timer;
			break;
		case 3:
			timer = clock();
			QuickSort(newVector, 0);
			timer = clock() - timer;
			break;
		case 4:
			timer = clock();
			InsertionSort(newVector);
			timer = clock() - timer;
			break;
		case 6:
			timer = clock();
			SelectionSort(newVector);
			timer = clock() - timer;
			break;
		case 7:
			timer = clock();
			MergeSort(newVector,0);
			timer = clock() - timer;
			break;
		case 5:
			timer = clock();
			MergeSort(newVector,1);
			timer = clock() - timer;
			break;

		case 8:
			timer = clock();
			ShellSortByInser(newVector);
			timer = clock() - timer;
			break;

	}
	execution = ((double)timer / CLOCKS_PER_SEC);
	VectorDestroy(newVector);
	return execution;
}
void WriteInfileResult()
{
	int size = 1000, i, j;
	double result;
	FILE* file = fopen("resultFile.txt", "w");
	if(NULL == file)
	{
		return;
	}
	for(i = 0; i < 8; i++)
		{
			size = 1000;
			for(j = 1; j < 3; j++)
			{
				result = recordTime(i, size);
				fprintf(file, "%d\t %d\t%lf\t",i, size, result );
				size *=10;
			}
				result = recordTime(i, 50000);
				fprintf(file, "%d\t %d\t%lf\t",i, 50000, result );


			fprintf(file, "\n");
		}


		fclose(file);
	

}


int main()
{
	ADTErr stat;
	TestResult res;

/*	res = TestBubbleSort(&stat);
	PrintResult("TestBubbleSort", res, stat);*/

	res = TestShakeSort(&stat);
	PrintResult("TestShakeSort", res, stat);

/*	res = TestQuickRec(&stat);
	PrintResult("TestQuickRec", res, stat);
	res = TestQuickNR(&stat);
	PrintResult("TestQuickNR", res, stat);

	res = TestInsertion(&stat);
	PrintResult("TestInsertion", res, stat);

	res = TestSelectionSort(&stat);
	PrintResult("TestSelectionSort", res, stat);

	res = TestShellSort(&stat);
	PrintResult("TestShellSort", res, stat);
/*	res = TestMergeSortRec(&stat);
	PrintResult("TestMergeSortRec", res, stat);

	res = TestMergeSortNR(&stat);
	PrintResult("TestMergeSortNR", res, stat);
	res = TestSelectionSort(&stat);
	PrintResult("TestSelectionSort", res, stat);

	/*WriteInfileResult();*/
	return 0;

}