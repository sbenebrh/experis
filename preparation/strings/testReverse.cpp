#include <iostream>
#include <cstdlib>
#include <cstring>

#include "Reverser.h"



int main()
{

    char* str = (char*)malloc(100 * sizeof(char));
    strcpy(str, "hello");
    preparation::Reverser rev(str);
    rev.ReverserIt();
    std::cout << str;
    free(str);

    return 0;

}