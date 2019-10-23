#ifndef __TEST_HEAP_H__
#define __TEST_HEAP_H__


typedef enum 
{
	SUCCEED,
	FAIL
}TestResult;

TestResult TestHEAPBuild1();
TestResult TestHEAPBuild2();
TestResult TestHEAPBuild3();
TestResult TestHEAPBuild4();
TestResult TestHEAPDestroy1();
TestResult TestHEAPDestroy2();
TestResult TestHEAPInsert1();
TestResult TestHEAPInsert2();
TestResult TestHEAPInsert3();
TestResult TestHEAPInsert4();
TestResult TestHEAPPeak1();
TestResult TestHEAPPeak2();
TestResult TestHEAPPeak3();
TestResult TestHEAPPeakEx1();
TestResult TestHEAPPeakEx2();
TestResult TestHEAPPeakEx3();
TestResult TestHEAPSize1();
TestResult TestHEAPSize2();

#endif