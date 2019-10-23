#ifndef UNIQUECHARACTER_H
#define UNIQUECHARACTER_H

#include<string>

namespace preparation
{

class Strings
{
public:
    Strings(char* str = "");
    Strings(const std::string& str);
    

    bool Isuniqueloop() const;
    bool Isuniquemap() const;

private:
    std::string m_str;
};
}


#endif
