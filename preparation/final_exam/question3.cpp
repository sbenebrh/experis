
#include <string>
#include <iostream>
namespace preparation
{
static int myStrCompareRec(std::string first, std::string second, int index, int size1, int size2);

int myStrCompare(std::string first, std::string second)
{
    return myStrCompareRec(first, second, 0, first.size(), second.size());
}


static int myStrCompareRec(std::string first, std::string second, int index, int size1, int size2)
{

    if(first[index] != second[index])
    {
        return first[index] - second[index];
    }
    if(index == size1 && index == size2)
    {
        return 0;
    }
    
    return myStrCompareRec(first, second, ++index, size1, size2);
}


}


int main()
{
    std::string str1 = "hello", str2 = "hell";
    std::cout<< preparation::myStrCompare(str2, str1);
}