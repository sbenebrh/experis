
#include <string.h>
#include"stringF.h"
#include"test.h"
#include"ADTErr.h"

#define BUFFER	32

TestResult TestLen1(ADTErr* _status)
{
	char test[BUFFER] = "aaaaa";

	if(StrLen(test) == strlen(test) )
	{
		return SUCCEED;
	}
	return FAIL;
}

TestResult TestLen2(ADTErr* _status)
{
	char test[BUFFER] = "";

	if(strlen(test) == StrLen(test))
	{
		return SUCCEED;
	}
	return FAIL;
}

TestResult TestLen3(ADTErr* _status)
{
	char test[BUFFER];

	if(strlen(test) == StrLen(test))
	{
		return SUCCEED;
	}
	return FAIL;
}



TestResult TestLenRec1(ADTErr* _status)
{
	char test[BUFFER] = "aaaaa";

	if(strlen(test) == StrLenRec(test))
	{
		return SUCCEED;
	}
	return FAIL;
}

TestResult TestLenRec2(ADTErr* _status)
{
	char test[BUFFER] = "";

	if(strlen(test) == StrLenRec(test))
	{
		return SUCCEED;
	}
	return FAIL;
}

TestResult TestLenRec3(ADTErr* _status)
{
	char test[BUFFER];

	if(strlen(test) == StrLenRec(test))
	{
		return SUCCEED;
	}
	return FAIL;
}


TestResult TestCmp1(ADTErr* _status)
{
	char test1[BUFFER] = "aaaa";
	char test2[BUFFER] = "aaaa";

	if(strcmp(test1,test2) == StrCompare(test1,test2))
	{
		return SUCCEED;
	}
	return FAIL;


}
TestResult TestCmp2(ADTErr* _status)
{
	char test1[BUFFER] = "aaaaa";
	char test2[BUFFER] = "aaaa";
	int a = strcmp(test1,test2);
	if(strcmp(test1,test2) == StrCompare(test1,test2))
	{
		return SUCCEED;
	}
	return FAIL;


}

TestResult TestCmp3(ADTErr* _status)
{
	char test1[BUFFER] = "aaaa";
	char test2[BUFFER] = "aaaaa";

	if(strcmp(test1,test2) == StrCompare(test1,test2))
	{
		return SUCCEED;
	}
	return FAIL;


}


TestResult TestCmpRec3(ADTErr* _status)
{
	char test1[BUFFER] = "aaaa";
	char test2[BUFFER] = "aaaaa";

	if(strcmp(test1,test2) == StrCompareRec(test1,test2))
	{
		return SUCCEED;
	}
	return FAIL;

}
TestResult TestCmpRec2(ADTErr* _status)
{
	char test1[BUFFER] = "aaaaa";
	char test2[BUFFER] = "aaaa";

	if(strcmp(test1,test2) == StrCompareRec(test1,test2))
	{
		return SUCCEED;
	}
	return FAIL;


}

TestResult TestCmpRec1(ADTErr* _status)
{
	char test1[BUFFER] = "aaaa";
	char test2[BUFFER] = "aaaa";

	if(strcmp(test1,test2) == StrCompareRec(test1,test2))
	{
		return SUCCEED;
	}
	return FAIL;
}


TestResult TestCopy1(ADTErr* _status)
{
	char test1[BUFFER] ;
	char test2[BUFFER] = "aaaa";

	if(strcmp(strcpy(test1,test2),StrCopy(test1,test2)) == 0)
	{
		return SUCCEED;
	}
	return FAIL;
}

TestResult TestCopyRec1(ADTErr* _status)
{
	char test1[BUFFER] ;
	char test2[BUFFER] = "aaaa";

	if(strcmp(strcpy(test1,test2),StrCopyRec(test1,test2)) == 0)
	{
		return SUCCEED;
	}
	return FAIL;
}


TestResult TestNCopy1(ADTErr* _status)
{
	char test1[BUFFER] ;
	char test2[BUFFER] = "aaaa";

	if(strcmp(strncpy(test1,test2,0),StrNCopy(test1,test2,0)) == 0)
	{
		return SUCCEED;
	}
	return FAIL;
}
TestResult TestNCopy2(ADTErr* _status)
{
	char test1[BUFFER] ;
	char test2[BUFFER] = "aaaa";

	if(strcmp(strncpy(test1,test2,2),StrNCopy(test1,test2,2)) == 0)
	{
		return SUCCEED;
	}
	return FAIL;
}

TestResult TestNCopy3(ADTErr* _status)
{
	char test1[BUFFER] ;
	char test2[BUFFER] = "aaaa";

	if(strcmp(strncpy(test1,test2,5),StrNCopy(test1,test2,5)) == 0)
	{
		return SUCCEED;
	}
	return FAIL;
}

TestResult TestNCopyRec3(ADTErr* _status)
{
	char test1[BUFFER] ;
	char test2[BUFFER] = "aaaa";

	if(strcmp(strncpy(test1,test2,5),StrNCopyRec(test1,test2,5)) == 0)
	{
		return SUCCEED;
	}
	return FAIL;
}

TestResult TestNCopyRec2(ADTErr* _status)
{
	char test1[BUFFER] ;
	char test2[BUFFER] = "aaaa";

	if(strcmp(strncpy(test1,test2,2),StrNCopyRec(test1,test2,2)) == 0)
	{
		return SUCCEED;
	}
	return FAIL;
}

TestResult TestNCopyRec1(ADTErr* _status)
{
	char test1[BUFFER] ;
	char test2[BUFFER] = "aaaa";

	if(strcmp(strncpy(test1,test2,0),StrNCopyRec(test1,test2,0)) == 0)
	{
		return SUCCEED;
	}
	return FAIL;
}


TestResult TestConcat1(ADTErr* _status)
{
	char test1[BUFFER] = "bbbb" ;
	char test2[BUFFER] = "aaaa";

	if(strcmp(strcat(test1,test2),StrConcat(test1,test2)) == 0)
	{
		return SUCCEED;
	}
	return FAIL;
}



TestResult TestsubString1(ADTErr* _status)
{
	char test1[BUFFER] = "bbbbaaaabbbb" ;
	char test2[BUFFER] = "aaaa";

	if(strcmp(strstr(test1,test2),StrSubString(test1,test2)) == 0)
	{
		return SUCCEED;
	}
	return FAIL;
}


TestResult TestsubString2(ADTErr* _status)
{
	char test1[BUFFER] = "bbbbaabbbb" ;
	char test2[BUFFER] = "aaaa";
	
	
	if(NULL == StrSubString(test1,test2) )
	{
		return SUCCEED;
	}
	return FAIL;
}
