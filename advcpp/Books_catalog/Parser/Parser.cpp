#include "Parser.h"



namespace advcpp
{

size_t Parser::nOfline = 0;

Parser::Parser(std::istream& istream, const std::string& delims, std::string * fields, size_t size)
: m_delims(delims)
, is(istream)
, m_fields(fields)
, m_fieldsSize(size) 
{

}


const std::tr1::unordered_map<std::string, std::string>& Parser::nextBookRecord()  
{
    m_tokens.erase(m_tokens.begin(), m_tokens.end());

    std::string line;
	if(getline(is,line))
	{  ++nOfline;
		Tokenize(line);
	}

    return m_tokens;
}

void Parser::Tokenize(const std::string& line)
{

    size_t currentPos=0;
    size_t found=line.find_first_of(m_delims);
    for(size_t i = 0 ; i < m_fieldsSize; ++i)
    {
        m_tokens[m_fields[i]] = line.substr(currentPos, found - currentPos);

        currentPos=found+1;
        found=line.find_first_of(m_delims,found+1);
    }
}

size_t Parser::NumberOfLine() 
{
    return nOfline;
}

}