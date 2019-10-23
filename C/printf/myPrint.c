#include<stdio.h>
#include<string.h>
#include<stdarg.h>
#include"myPrint.h"
int MyPrintf(const char* _strFormat, ...)
{
	char result[1024] = "";
	char * ptr;
	int integerInput;
	double doubleInput;
	char stringInput[1024] = "";
	char* ptrTemp;
	va_list args;
	char format[1024];
	va_start(args, _strFormat);

	if(!_strFormat)
	{
		return -1;
	}
	strcpy(format, _strFormat);
	ptr = format;
	ptrTemp = format;
	while(1)
	{
		if(*ptr =='\0')
		{
			break;
		}

		ptr = strchr(ptr,'%');
		if(! ptr)
		{
			strcat(result,ptrTemp);
			break;
		}
		strncat(result, ptrTemp , ptr - ptrTemp );

		switch(_strFormat[ptr - _strFormat + 1])/*the char after %*/
		{
			case 's':
				strcpy(stringInput , va_arg(args, char*));
				strcat(result, stringInput);
				break;
			case 'f':
				doubleInput = va_arg(args, double);
				sprintf(stringInput,"%f", doubleInput);
				strcat(result, stringInput);
				break;
			case 'd':
				integerInput = va_arg(args, int);
				sprintf(stringInput,"%d",integerInput);
				strcat(result, stringInput);
				break;
			case '%':
				strcat(result,"%");
				break;
		}
		ptrTemp = ptr + 2;
		ptr = ptr+2;


	}
	va_end(args);

	return puts(result);
}

int main()
{
	
	MyPrintf("my name is %s i am %d my gpa is %f and i am at 80%% of my capabilities ","samuel",28,84.2);
}