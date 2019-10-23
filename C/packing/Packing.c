#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE_NEW_CHAR 4
#define MYLANGUAGE(c) ((c) <= 'a'+('p'-'a') && (c) >= 'a' )|| (c) == '\0'

typedef struct BitfieldAlpha
{
	unsigned int first: SIZE_NEW_CHAR;
	unsigned int second: SIZE_NEW_CHAR;

} newAlpha_t;

typedef union 
{
	newAlpha_t new;
	char letter;
}charUnion;

typedef int (*Packing)(unsigned char*);

int packFunc(Packing _func, unsigned char* _str)
{
	return _func(_str);
}


int packingBitWise(unsigned char* _str)
{	
	int i;
	int temp = 0;
	int length = strlen((char*)_str);
	int effectiveLength = length/2 + length % 2;

	if(!_str)
	{
		return -1;
	}
	for (i = 0; i < effectiveLength; ++i)
	{
		temp = i * 2;
		if(!MYLANGUAGE(_str[temp]) || !MYLANGUAGE(_str[temp + 1]) )
		{
			return -1;
		}
		if(_str[temp + 1] == '\0')
		{
			_str[i] = (_str[temp] - 'a') << SIZE_NEW_CHAR ;

		}
		else
			{
				_str[i] = ((_str[temp] - 'a') << SIZE_NEW_CHAR | _str[temp + 1] - 'a');
			}
	}
	_str[i + 1] ='\0';

	return length;
}

int packingBitField( unsigned char* _str)
{
	int i;
	charUnion pack;
	int temp = 0;
	int length = strlen((char*)_str);
	int effectiveLength = length/2 + length % 2;

	if(!_str)
	{
		return -1;
	}
	for (i = 0; i < effectiveLength; ++i)
	{
		
		temp = i * 2;
	if(!MYLANGUAGE(_str[temp]) || !MYLANGUAGE(_str[temp + 1]) )
		{
			return -1;
		}

		pack.new.first = _str[temp] -'a';

		if(_str[temp + 1] == '\0')
		{
			pack.new.second = 0;
		}
		else
		{
			pack.new.second = _str[temp + 1] - 'a';
		}
		_str[i] = pack.letter;

	}


	return length;
}

int main()
{
	Packing arrPa[2] ={ packingBitWise, packingBitField };
	int count = 1; 
	int res;
	unsigned char str[16];
	while(count)
	{
		printf("%s\n","press 1 to packingBitWise\n"
				"press 2 to packingBitField\n"
				"press 0 to exit" );
		scanf("%d", &count);
		if(count)
		{
		printf("%s\n","please enter string" );
		scanf("%s", str);
		res = packFunc(arrPa[count - 1],str);
		printf("%d\n", res);
		}	

	}
	return 0;
}
