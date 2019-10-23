#include<stdio.h>
#include<ctype.h>
#include"string_function.h"

int strlengh(char * _str)
{
	char * temp = _str ;
	for(; *temp != '\0';temp++){}
	return (temp - _str);
	
}
char*  strcopy( char * _destination, const char * _source )
{
	int i = 0;
	char * temp = _destination;
	if(NULL == _source || NULL == _destination)
	{
		return NULL;
	}
	while(_destination[i++] = _source[i++]);

	return temp;
}
void reverse(char * _str)
{	char  reversedStr[120];
	int i = strlengh(_str) - 1;
	int j;
	for(j = 0 ; i >= 0 ; i--, j++)
	{
		reversedStr[j] = (_str)[i];
	}
	reversedStr[strlengh(_str)] = '\0';
	printf("%s\n",reversedStr);
}
char * myStrcat ( char * _destination, const char * _source )
{
	int i;
	if(NULL == _source || NULL == _destination)
	{
		return NULL;
	}

	while(*_destination != '\0')
	{
		_destination++;
	}
	for(i = 0;_destination[i] = _source[i];i++);

	return _destination;

}
int mystrcmp( const char * _string1, const char * _string2 )
{
	int i;
	 for (i = 0; ; i++)
    {
        if (_string1[i] != _string2[i])
        {
            return _string1[i] < _string2[i] ? -1 : 1;
        }

        if (_string1[i] == '\0')
        {
            return 0;
        }
    }
}

int charToInt (const char * _str)
{
	int signeFlag = 0;
	int flag = 0;
	int i;
	int result = 0;
	if(NULL == _str)
	{
		return 0;
	}
	for(i = 0;_str[i] != '\0';i++)
	{
		if(_str[i] == '-' && flag == 0 || isalpha(_str[i]))
		{
			signeFlag = 1;
			flag = 1;
		}
		else if(isdigit(_str[i]))
		{
			result = result * 10 + _str[i] - '0';
			flag = 1;
		}
		else if(!isdigit(_str[i]) && flag)
		{
			break;
		}
	}
	if(signeFlag)
	{
		result = -result;
	}
	return result;
}

