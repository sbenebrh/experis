#include "BookReader.h"

#include <iostream>

namespace advcpp
{

BookReader::BookReader(std::istream& istream , std::tr1::shared_ptr<Iinserter> inserter, const std::string& delim,  std::string * fields, size_t size)
: m_source( new Parser(istream, delim, fields, size))
, m_inserter(inserter)

{

}

void BookReader::InsertBook() 
{
    //fields
    m_source -> nextBookRecord();
    while(true)
    {
        std::tr1::unordered_map< std::string, std::string > m = m_source -> nextBookRecord();
        if(m.empty())
        {
            break;
        }
        BookDetails  bp(m["ISBN"], m["TITLE"], m["AUTHOR"], m["YEAR"], m["PUBLISHER"]);
        m_inserter->insert(bp);
    }
    
}

} // advcpp
