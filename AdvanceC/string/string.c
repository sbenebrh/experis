#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"stringF.h"

size_t StrLen(const char* _str)
{
	int i = 0;

	if(NULL == _str )
	{
		return 0;
	}
	while(_str[i++]);
	i--;

	return i;
}

size_t StrLenRec(const char* _str)
{
	if(*_str == '\0')
	{
		return 0;
	}
	return 1 + StrLenRec(_str +1);
}

int StrCompare(const char* _s1, const char* _s2)
{
	int i;
	if(!_s1)
	{
		return _s2[0];
	}
	if(!_s2)
	{
		return _s1[0];
	}
	for(i = 0; _s1[i] && _s2[i]; i++)
	{
		if(_s1[i] != _s2[i])
		{
			return _s1[i] - _s2[i];
		}
	}

	if(_s1[i] && _s2[i])
	{
		return 0 ;
	}
	if(_s1[i] && !_s2[i])
	{
		return _s1[i];
	}
	else
	{
		return  - _s2[i];
	}
}

int StrCompareRec(const char* _s1, const char * _s2)
{
	if(! *_s1 && ! *_s2)
	{
		return 0;
	}
	if(! *_s1)
	{
		return - _s2[0];
	}
	if(! *_s2)
	{
		return _s1[0];
	}


	return StrCompareRec(_s1 + 1 , _s2 + 1);
}

char* StrCopy(char* _destination, const char* _source)
{
	int i = 0;
	if(!_destination || !_source)
	{
		return NULL;
	}

	while(_destination[i++] = _source[i]);

	return _destination;
}

char* StrCopyRec(char* _destination, const char* _source)
{
	if(! *_source)
	{
		return;
	}
	*_destination = *_source;
	StrCopyRec(_destination + 1, _source + 1);
	return _destination;

}

char* StrNCopy(char* _destination, const char* _source, size_t _num)
{
	int i = 0;
	if(!_destination || !_source)
	{
		return NULL;
	}

	while(_num && (_destination[i++] = _source[i] ))
	{
		--_num;
	}
	_destination[i] = '\0';

	return _destination;
}

char* StrNCopyRec(char* _destination, const char* _source, size_t _num)
{
	if(! *_source )
	{
		return;
	}
	if(!_num)
	{
		_destination[0] = '\0';
		return;
	}
	*_destination = *_source;
	StrNCopyRec(_destination + 1, _source + 1 , _num -1);
	return _destination;
}

char* StrConcat(char* _destination, const char* _source)
{
	char *returndest = _destination;

    while (*_destination)
    {
      _destination++;
    }
    while (*_destination++ = *_source++);

    return returndest;
}

char* StrSubString(const char* _str, const char* _search)
{
	char *h, *n;
	int size1 = strlen(_str);
	int size2 = strlen(_search);

	char* returnChar = (char*)malloc(size1 * sizeof(char));
	char* tmp =(char*) malloc(size2 * sizeof(char));

	StrCopy(returnChar, _str);
	StrCopy(tmp, _search);
	 if (_str == NULL || _search == NULL ) 
	 {
        return NULL;
    }

    for ( ; *returnChar; returnChar++) {
        
        
        for (h = returnChar, n = tmp; *h && *n && (*h == *n); ++h, ++n) {
            
        }
        if (*n == '\0') {
           
            return returnChar;
        }
        
    }
    return NULL;
}
