#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"bits.h"

void IntToBin(unsigned int _a, char* _result)
{
	int size = SIZE_BYTE, i;
	if(NULL == _result){ return ;}
	_result[size]='\0';
	for (i = size-1; i >= 0; --i)
	{
		_result[i] = ( _a%2 == 0 ? '0': '1' );
		_a /= 2;
	}

}
void CharToBin(unsigned char _a,unsigned char* _result)
{
	int size = SIZE_BYTE, i;
	if(NULL == _result){ return ;}
	_result[size]='\0';
	for (i = size-1; i >= 0; i--)
	{
		_result[i] = ( _a % 2 == 0 ? '0': '1' );
		_a /= 2;
	}

}

unsigned char SetBits_1(unsigned char _X,unsigned int _N,unsigned int _P,unsigned char _Y )
{

	unsigned char XRight, XLeft;
	if(_P>SIZE_BYTE || _P<_N){ printf("INVALID INPUT\n"); return 0;}
	
	XRight = (_X << (SIZE_BYTE-(_P - _N)) ) ;
	XRight = ( XRight >> (SIZE_BYTE-(_P - _N)) );
	XLeft  = (_X >> _P) << _P;  
	_Y	   = (_Y << (SIZE_BYTE-_N));
	_Y 	   = (_Y >> (SIZE_BYTE-_P));
	return XLeft | XRight | _Y ;

}
unsigned int SetBits_2(unsigned char _W, unsigned char i,unsigned char j, unsigned char value)
{
	unsigned int ones = ~0;
	unsigned int WR, WL;
	WR = (_W << (SIZE_BYTE-(i) )) >> (SIZE_BYTE-(i));
	WL = (_W >> (j+1)) << (j+1);
	if(value)
	{
		ones = (ones << (SIZE_BYTE-(j+1-i)))>>(SIZE_BYTE-(j+1)); 
		return ones | WR | WL; 
	}
	return WR | WL;
}

 
unsigned char complement(unsigned char _source)
{
	unsigned char ones = ~0;
	
	return _source ^ ones;
}
unsigned char rotate(unsigned char _n, unsigned char _x)
{
	unsigned char y, z; 
	if(_n > SIZE_BYTE)
	{
		_n %= SIZE_BYTE;
	}
	y = _x << (SIZE_BYTE - _n);
	z = _x>> _n;
	_x = y | z;
	
	return _x;
}




