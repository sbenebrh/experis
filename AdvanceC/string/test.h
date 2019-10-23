#ifndef __TESTSTRING_H__
#define __TESTSTRING_H__

#include<string.h>
#include "ADTErr.h"

/* check the strlen function using a valid string*/
TestResult TestLen1(ADTErr* _status);

/*check the strlen using an empty string*/
TestResult TestLen2(ADTErr* _status);

/*check the strlen using an NULL string*/
TestResult TestLen3(ADTErr* _status);

/* check the strlen function using a valid string*/
TestResult TestLenRec1(ADTErr* _status);

/*check the strlen using an empty string*/
TestResult TestLenRec2(ADTErr* _status);

/*check the strlen using an NULL string*/
TestResult TestLenRec3(ADTErr* _status);



/* check the strcompare function using two string with the same content*/
TestResult TestCmp1(ADTErr* _status);

/*check the strlen using first string longer than the second*/
TestResult TestCmp2(ADTErr* _status);

/*check the strlen using first string shorter than the second*/
TestResult TestCmp3(ADTErr* _status);

/* check the strcompare function using two string with the same content*/
TestResult TestCmpRec1(ADTErr* _status);

/*check the strlen using an empty string*/
TestResult TestCmpRec2(ADTErr* _status);

/*check the strlen using an NULL string*/
TestResult TestCmpRec3(ADTErr* _status);

/* test copy*/
TestResult TestCopy1(ADTErr* _status);

TestResult TestCopyRec1(ADTErr* _status);


/*check  strncopy with parameter 0;*/
TestResult TestNCopy1(ADTErr* _status);

TestResult TestNCopyRec1(ADTErr* _status);


/*check  strncopy with parameter in the lenght*/
TestResult TestNCopy2(ADTErr* _status);

TestResult TestNCopyRec2(ADTErr* _status);

/*check  strncopy with parameter over the lenght*/
TestResult TestNCopy3(ADTErr* _status);

TestResult TestNCopyRec3(ADTErr* _status);

TestResult TestsubString1(ADTErr* _status);

TestResult TestsubString2(ADTErr* _status);


#endif