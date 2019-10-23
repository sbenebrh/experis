#include <stdio.h>


#include "test.h"
#include"stringF.h"
#include<string.h>

void PrintResult(char* _testName, TestResult _result, ADTErr _stat)
{
	if(_stat != ERR_OK) printf("%s %s \n","test error of the", _testName );
	printf("%s\t%s\n",_testName, (_result == SUCCEED)? "succed": "failed" );
}

int main()
{
	ADTErr status;
	PrintResult("TestLen1",TestLen1(&status), ERR_OK);
	PrintResult("TestLen2",TestLen2(&status), ERR_OK);
	PrintResult("TestLen3",TestLen3(&status), ERR_OK);

	PrintResult("TestLenRec1",TestLenRec1(&status), ERR_OK);
	PrintResult("TestLenRec2",TestLenRec2(&status), ERR_OK);
	PrintResult("TestLenRec3",TestLenRec3(&status), ERR_OK);

	PrintResult("TestCmp1",TestCmp1(&status), ERR_OK);
	PrintResult("TestCmp2",TestCmp2(&status), ERR_OK);

	PrintResult("TestCmp3",TestCmp3(&status), ERR_OK);


	PrintResult("TestCmpRec1",TestCmpRec1(&status), ERR_OK);
	PrintResult("TestCmpRec2",TestCmpRec2(&status), ERR_OK);

	PrintResult("TestCmpRec3",TestCmpRec3(&status), ERR_OK);

	PrintResult("TestCopy1",TestCopy1(&status), ERR_OK);
	PrintResult("TestCopyRec1",TestCopyRec1(&status), ERR_OK);


	PrintResult("TestnCopy1",TestNCopy1(&status), ERR_OK);
	PrintResult("TestnCopyRec1",TestNCopyRec1(&status), ERR_OK);

	PrintResult("TestnCopy2",TestNCopy2(&status), ERR_OK);
	PrintResult("TestnCopyRec2",TestNCopyRec2(&status), ERR_OK);

	PrintResult("TestnCopy3",TestNCopy3(&status), ERR_OK);
	PrintResult("TestnCopyRec3",TestNCopyRec3(&status), ERR_OK);

	PrintResult("TestConcat1",TestConcat1(&status), ERR_OK);

	PrintResult("Testsubstring1",TestsubString1(&status), ERR_OK);

	PrintResult("Testsubstring2",TestsubString2(&status), ERR_OK);


}
