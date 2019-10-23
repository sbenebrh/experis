#include<iostream>

#include "UniqueCharacter.h"

int main()
{
    std::string str;
    std::cin >> str;
    preparation::Strings mstrings(str);
    std::cout << mstrings.Isuniqueloop() << std::endl ;
    std::cout << mstrings.Isuniquemap() << std::endl ;
    return 0; 
}