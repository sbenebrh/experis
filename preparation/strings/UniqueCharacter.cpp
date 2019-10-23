#include "UniqueCharacter.h"
#include <algorithm>
#include <tr1/unordered_map>
#include <exception>
#include <stdexcept>


namespace preparation
{

Strings::Strings(char* str )
: m_str(str)
{

}
Strings::Strings(const std::string& str)
: m_str(str)
{

}

bool Strings::Isuniqueloop() const
{
    int size = m_str.length();
    for(int i = 0; i < size; ++i)
    {
        for(int j = i + 1; j < size; ++j)
        {
            if(m_str[i]== m_str[j])
            {
                return false;
            }
        }
    }
    return true;
}
class inserter
{
public:
    inserter(std::tr1::unordered_map<char,int>& map)
    : m_map(map)
    {

    }

    void operator()(const char& c)
    {
        if(m_map[c] == 1)
        {
            throw std::out_of_range("excpetion");
        }
        m_map[c]++;
    }

private:
    std::tr1::unordered_map<char,int>& m_map;
};

bool Strings::Isuniquemap() const
{
    std::tr1::unordered_map<char,int> map;
    try
    {
        std::for_each(m_str.begin(), m_str.end(), inserter(map));
    }
    catch(const std::exception& e)
    {
        return false;
    }
    return true;
    

}
}