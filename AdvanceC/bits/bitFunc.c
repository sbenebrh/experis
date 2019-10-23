#include<math.h>

void swap1(int *_first, int *_second)
{
	*_second = *_first + *_second;
	*_first = *_second - *_first;
	*_second = *_second - *_first;
}

void swap2(int* _first, int* _second)
{
	*_first = *_first ^ *_second;
	*_second = *_first ^ *_second;
	*_first = *_first ^ *_second; 
}

void swap3(int* _first, int* _second)
{
	*_first = *_first * *_second;
	*_second = *_first / *_second;
	*_first = *_first / *_second;
}

int IsNegative(int number)
{
	number = number>>sizeof(int)- 1;
	return number & 1;
	
}
int abs1(int number)
{
	int mask = number >> sizeof(int) - 1;
	return (mask + number) ^ mask;
}

int abs2(int number)
{
	return number *((number > 0)  - (number < 0));
}

int IsPowTwo1(int number)
{
	int i;
	int arr[INT_MAX] = {0};

	for(i = 1; i < INT_MAX;i*= 2)
	{
		arr[i] = 1;
	}

	return arr[number];
}

int IsPowTwo2(int number)
{
	int counter = 0;
	int i;

	for(i = 0; i < sizeof(int); ++i)
	{
		count += number & 1;
		number = number >> 1;
	}
	if(count == 1)
	{
		return 1;
	}
	return 0;
}

int Add1(int number1,int number2)
{
	    while (number2 != 0) 
    { 

        int carry = number1 & number2;   

        number1 = number1 ^ number2;  
  
        number2 = carry << 1; 
    } 
    return number1;
}

int Add2(int number1,int number2)
{
	if(number2 == 0)
        return number1;

    return Add2( number1 ^ number2, (number1 & number2) << 1);
}

int num_to_bits[16] =  {0, 1, 1, 2, 1, 2, 2, 3,   
                       1, 2, 2, 3, 2, 3, 3, 4}; 
  
unsigned int countSetBitsRec(unsigned int num) 
{ 
   int nibble = 0; 
   if (0 == num) 
      return num_to_bits[0]; 
  
   nibble = num & 0xf; 

   return num_to_bits[nibble] + 
          countSetBitsRec(num >> 4); 
}

int countSetBits(int n) 
{ 
    if (n == 0) 
        return 0; 
    else
        return 1 + countSetBits(n & (n - 1)); 
} 

int flipNumber(int number, int start, int end)
{
    int num = ((1 << start) - 1) ^ ((1 << (end - 1)) - 1); 

    return (number ^ num); 
}
int flipOneBit(int number,int position)
{
	int mask = 1<<position;
	return number^mask;
}


unsigned int bitMirror(unsigned int a)
{
	unsigned int b = 0;
	int i = 0;
	for(i = 0; i < CHAR_BIT/2;++i)
	{
		b|= lut[(a>>(CHAR_BIT *i) & 0xff]<<(CHAR_BIT/2 -i)* CHAR_BIT)  ;
	}
	return b;
}

void printBin(int number)
{
	int k, c;
	for (c = sizeof(int) - 1; c >= 0; c--)
  {
    k = number >> c;
 
    if (k & 1)
      printf("1");
    else
      printf("0");
  }
 
  printf("\n");
 
  return 0;
}
