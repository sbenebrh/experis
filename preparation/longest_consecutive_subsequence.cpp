/*

Given an array of integers, 
find the length of the longest sub-sequence such that elements in the subsequence are consecutive integers,
the consecutive numbers can be in any order.
*/
#include <set>
#include <iostream>
#include <iterator>
#include<unordered_set>
//solution O(nlogn)
template<typename Iter> 
int foo1(Iter begin, Iter end )
{
    std::set<int> a ;
    a.insert(begin, end);
    int countReturn = 0;
    int tempCount = 0;
    std::set<int>::iterator it = a.begin();
    for(int i = 0;it != a.end(); ++i )
    {
        int first = *it++;
        int second = *it - 1;
        if(first  == second )
        {
            ++tempCount;
        }
        else
        {
            if(tempCount >= countReturn)
            {
                countReturn = tempCount + 1;
            }
            tempCount = 0;
        }
        
    }
    return countReturn;

}

//solution with O(n)
template<typename Iter>
int foo2(Iter begin, Iter end)
{
    std::unordered_set<int> S;
    S.insert(begin, end);
    int countReturn = 0;
    int tempCount = 0;
    Iter it = begin;
    for(int i = 0; it != end;++i,++it)
    {
        if(S.find(*it - 1) == S.end())
        {
            int j = *it;
            while(S.find(j++) != S.end())
            {
                ++tempCount;
            }
            countReturn = std::max(countReturn, tempCount );
            tempCount = 0;
        }
    }
    return countReturn;
}

int main()
{
    int b[] = {2,3, 5, 6, 7, 20, 19};
    std::cout << foo1(b, b + 7)<< std::endl;
    std::cout <<foo2(b, b + 7) << std::endl;

    
}