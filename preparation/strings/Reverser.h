#ifndef REVERSER_H
#define REVERSER_H

namespace preparation
{

class Reverser
{

char *  m_str;

public:
    Reverser(char*  str);
    char* ReverserIt();
    char* ReverseRec();
};
}


#endif