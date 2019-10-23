#ifndef __TEST_ITR_H__
#define __TEST_ITR_H__

#include"list_itr.h"
#include"../list.h"

typedef enum 
{
	SUCCEED,
	FAIL
}TestResult;


TestResult TestItrBegin();
TestResult TestItrEnd();
TestResult TestItrEqual1();
TestResult TestItrEqual2();
TestResult TestItrNext1();
TestResult TestItrNext2();
TestResult TestItrNext3();
TestResult TestItrNext4();
TestResult TestItrPrev1();
TestResult TestItrPrev2();
TestResult TestItrPrev3();
TestResult TestItrPrev4();
TestResult TestItrGet1();
TestResult TestItrGet2();
TestResult TestItrSet1();
TestResult TestItrSet2();
TestResult TestItrInsert1();
TestResult TestItrInsert2();
TestResult TestItrRemove1();
TestResult TestItrRemove2();
TestResult TestFindFirst1();
TestResult TestFindFirst2();
TestResult TestFindFirst3();
TestResult TestForEach1();
TestResult TestForEach2();
TestResult TestCount1();
TestResult TestCount2();
TestResult TestCount3();
TestResult TestCut1();
TestResult TestCut2();



#endif