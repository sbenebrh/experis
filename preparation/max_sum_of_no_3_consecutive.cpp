
#include <iostream>
#include <stdlib.h>

template< typename Iter>
int foo(Iter begin, Iter end, size_t size)
{
    int* sum = new int[size];
    Iter it = begin;
    sum[0] = *it++;
    sum[1] = *it++;
    for(size_t i = 2; it != end;++it, ++i)
    {
        sum[i] = std::max(std::max(sum[i - 1], sum[i -2] + *it), sum[i - 3] + *it + *(it - 1));
    }
    int result = sum[size - 1];
    delete[] sum;
    return result; 
}
char * foo2()
{
    char * result = (char*)malloc(10);
}

int main()
{
    int b[] = {2,3, 5, 6, 7, 20, 19};
    char * testMemory_Leak = foo2();
    
    std::cout << foo(b, b + 7, 7)<< std::endl;
    free(testMemory_Leak);
}