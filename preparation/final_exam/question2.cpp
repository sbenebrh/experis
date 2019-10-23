#include <stddef.h>


namespace preparation
{


/* 2 ways to answer this question to get minimum compare:
    if we can change the array change the last element to the need one and check the index (n + 1 comparaisons)
    if we cant create a local variable at every loop local variable *= (need - a[i]) if local variable = 0 it is in the array
*/



bool findElement1(int* const arr , const int & n , const int & size)
{
     if(NULL == arr)
    {
        return  false;
    }
    if(size == 0)
    {
        return false;
    }

    if(arr[size -1] == n)
    {
        return true;
    }
    arr[size - 1 ] = n;
    int i = 0;
    for(; arr[i] < n; ++i);
    if( i < size - 1)
    {
        return true;
    }
    return false;
}

bool findElement2(const int * arr, const int& n,const int& size)
{
    if(NULL == arr)
    {
        return  false;
    }
    if(size == 0)
    {
        return false;
    }

    int count = 0;
    for(int i = 0; i < size;++i)
    {
        count *= arr[i] - n;
    }
    if(count == 0)
    {
        return true;
    }
    return false;
}
}