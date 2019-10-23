#include<stdio.h>
#include<string.h>
#define TRUE  1
#define FALSE !TRUE
#include"../DS/include/stack.h"
#include"recursiveFunctions.h" 

int factorial(int _n)
{
	if( _n <= 1)
	{
		return 1;
	}
	return	 _n * factorial(_n-1);
}

int power(int _num,int _k)
{
	if( _k <= 0)
	{
		return 1;
	}
	return _num * power(_num , _k - 1);
}


int sum(int* arr, int size)
{
	if(size -1 <= 0)
	{
		return arr[0];
	}
	return arr[size -1] + sum(arr, size -1);
}

int maximum(int ar[], int n)
{
  int max;
  if(!(n-1))
  {
    return ar[n];
  }
  max = maximum(ar,n-1);
  return ar[n]>max ? ar[n]:max;
}
double help(int a[], int i, int n) 
{  
    if (i == n-1) 
        return a[i]; 
   
    if (i == 0) 
        return ((a[i] + help(a, i+1, n))/n); 
  
    return (a[i] + help(a, i+1, n)); 
} 
  
double average(int a[], int n) 
{ 
     return help(a, 0, n); 
} 

size_t fiboRecursive(size_t _n)
{
	if(_n == 0)
	{
		return 0;
	}
	if(_n == 1)
	{
		return 1;
	}
	return fiboRecursive(_n - 1) + fiboRecursive(_n - 2);
}



char* RecReverseString(char* _str,int _index,int _size)
{
	
    char temp;
    temp = _str[_size];
    _str[_size] = _str[_index];
    _str[_index] = temp;
    if (_index == _size / 2)
    {
        return _str;
    }
  return  RecReverseString(_str, _index + 1, _size - 1);

}

int RecIsPalyndrome(char* _str,int _index, int _size)
{
	if(_index >= _size)
	{
		return TRUE;
	}
	if(_str[_index] != _str[_size])
	{
		return FALSE;
	}
	return RecIsPalyndrome( _str,_index + 1,_size - 1);

}
int IsPalyndromeBis(char*_str)
{
	if(_str)
	{
		return RecIsPalyndrome(_str, 0, strlen(_str) -1);
	}
	return -1;
}
char* reverseString(char* _str)
{	
	if(_str)
	{
		return	 RecReverseString(_str, 0, strlen(_str) - 1);
	}
	return NULL;
}

size_t fiboIter(size_t _n)
{

  size_t first = 0;
  size_t second = 1;
  size_t tmp;
  
  while (_n--) {
    tmp = first + second;
    first = second;
    second = tmp;
  }
  return first;

}
int IsPalindrome(char* _str)
{	
	
	char *temp = _str;
	reverseString(_str);
	return _str == temp ? TRUE: FALSE;
}

void Hanoi(int _n, char _from, char _to, char _via)
{
 
    if (_n == 1) 
    { 
        printf("\n Move disk 1 from %c to %c", _from, _to); 
        return; 
    } 
    Hanoi(_n-1, _from, _via, _to); 
    printf("\n Move disk %d from %c to  %c", _n, _from, _to); 
    Hanoi(_n-1, _via, _to, _from); 
} 
void RecStackHanoi(int _n,Stack* _rod1,Stack* _rod2,Stack* _rod3,char _from,char _to,char _via)
{
	int top;
	  if (_n == 1) 
    { 
        printf("Move disk 1 from %c to %c\n", _from, _to); 
        StackPop(_rod1, &top);
        StackPush(_rod2, top); 
        return; 
    } 
    
    RecStackHanoi(_n -1,_rod1, _rod3, _rod2, _from, _via, _to) ;
    printf("Move disk %d from %c to  %c\n", _n, _from, _to); 
    RecStackHanoi(_n -1 , _rod3, _rod2, _rod1, _via, _to, _from);
    
    
    
}
void StackHanoi(int _n, char _from, char _to, char _via)
{
	if (_n)/*TODO check why the Vector Print doesn t work*/
	{
		Stack* rod1 = StackCreate(_n, 0);
		Stack* rod2 = StackCreate(_n, 0);
		Stack* rod3 = StackCreate(_n, 0);
		RecStackHanoi(_n, rod1, rod2, rod3, _from, _to, _via);
		
		
		
		StackDestroy(rod1);
		StackDestroy(rod2);
		StackDestroy(rod3);
	}
}

int main()
{
	int arr[4] = {2,3,4,5};
	char string[30] = "hello";
	printf("%d\n", factorial(3));
	printf("%d\n", power(2,3));
	printf("%d\n", sum(arr,4));
	printf("%d\n", maximum(arr,4));
	printf("%.2f\n", average(arr,4));
	
	printf("      %s\t%s\n","  recusrsive","iterative");
	printf("%s%ld\t\t%ld\n","i = 10:  ", fiboRecursive(10),fiboIter(10));
	printf("%s%ld\t\t%ld\n","i = 20:  ", fiboRecursive(20),fiboIter(20));
	printf("%s%ld\t%ld\n","i = 40:  ", fiboRecursive(40),fiboIter(40));
	
	printf("%s\n",string);
	reverseString(string);
	printf("%s\n",string);
	printf("%d\n\n",IsPalyndromeBis("abccba"));
	

	StackHanoi(0,'A', 'B', 'C');
	StackHanoi(4, 'A', 'B', 'C');
	
	return 0;
} 		
