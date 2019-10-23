#ifndef PARSER_H
#define PARSER_H

#include <istream>
#include <tr1/unordered_map>

namespace advcpp
{

class Parser
{
public:    
    Parser(std::istream& istream, const std::string& delims, std::string * fields, size_t size);
    
    const std::tr1::unordered_map<std::string, std::string>& nextBookRecord()  ;
    static size_t NumberOfLine() ;
    

private:
    void Tokenize(const std::string& line);

private:
    std::string m_delims;
    std::istream& is;
    std::tr1::unordered_map<std::string, std::string> m_tokens;
    std::string * m_fields;
    size_t m_fieldsSize;
    
    static size_t nOfline;
};

}


#endif


