#include<stdio.h>
#include"test.h"


void PrintResult(char* _testName, TestResult _result)
{
	printf("%s\t%s\n",_testName, (_result == SUCCEED)? "succed": "failed" );
}

int main()
{
	PrintResult("TestHEAPBuild1", TestHEAPBuild1());
	PrintResult("TestHEAPBuild2", TestHEAPBuild2());
	PrintResult("TestHEAPBuild3", TestHEAPBuild3());
	PrintResult("TestHEAPBuild4", TestHEAPBuild4());
	PrintResult("TestHEAPDestroy1", TestHEAPDestroy1());
	PrintResult("TestHEAPDestroy2", TestHEAPDestroy2());
	PrintResult("TestHEAPInsert1", TestHEAPInsert1());
	PrintResult("TestHEAPInsert2", TestHEAPInsert2());
	PrintResult("TestHEAPInsert3", TestHEAPInsert3());
	PrintResult("TestHEAPInsert4", TestHEAPInsert4());
	PrintResult("TestHEAPPeak1", TestHEAPPeak1());
	PrintResult("TestHEAPPeak2", TestHEAPPeak2());
	PrintResult("TestHEAPPeak3", TestHEAPPeak3());
	PrintResult("TestHEAPPeakEx1", TestHEAPPeakEx1());
	PrintResult("TestHEAPPeakEx2", TestHEAPPeakEx2());
	PrintResult("TestHEAPPeakEx3", TestHEAPPeakEx3());
	PrintResult("TestHEAPSize1", TestHEAPSize1());
	PrintResult("TestHEAPSize2", TestHEAPSize2());
	return 0;
}