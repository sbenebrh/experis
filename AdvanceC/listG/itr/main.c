#include<stdio.h>
#include"test.h"

void PrintResult(char* _testName, TestResult _result)
{
	printf("%s\t%s\n",_testName, (_result == SUCCEED)? "succed": "failed" );
}

int main()
{
	PrintResult("TestItrBegin",TestItrBegin());
	PrintResult("TestItrEnd",TestItrEnd());
	PrintResult("TestItrEqual1",TestItrEqual1());
	PrintResult("TestItrEqual2",TestItrEqual2());
	PrintResult("TestItrNext1",TestItrNext1());
	PrintResult("TestItrNext2",TestItrNext2());
	PrintResult("TestItrNext3",TestItrNext3());

	PrintResult("TestItrPrev1",TestItrPrev1());
	PrintResult("TestItrPrev2",TestItrPrev2());
	PrintResult("TestItrPrev3",TestItrPrev3());
	PrintResult("TestItrPrev4",TestItrPrev4());
	PrintResult("TestItrGet1",TestItrGet1());
	PrintResult("TestItrGet2",TestItrGet2());
	PrintResult("TestItrSet1",TestItrSet1());
	PrintResult("TestItrSet2",TestItrSet2());
	PrintResult("TestItrInsert1",TestItrInsert1());
	PrintResult("TestItrInsert2",TestItrInsert2());
	PrintResult("TestItrRemove1",TestItrRemove1());
	PrintResult("TestItrRemove2",TestItrRemove2());
	PrintResult("TestFindFirst1",TestFindFirst1());
	PrintResult("TestFindFirst2",TestFindFirst2());
	PrintResult("TestFindFirst3",TestFindFirst3());
	PrintResult("TestForEach1",TestForEach1());
	PrintResult("TestForEach2",TestForEach2());
	PrintResult("TestCount1",TestCount1());
	PrintResult("TestCount2",TestCount2());
	PrintResult("TestCount3",TestCount3());
	PrintResult("TestCut1",TestCut1());
	PrintResult("TestCut2",TestCut2());

	return 0;
}