#ifndef BOOKREADER_H
#define BOOKREADER_H

#include <tr1/memory>
#include "Parser.h"
#include "Iinserter.h"

namespace advcpp
{

class BookReader
{
public:
    BookReader(std::istream& istream , std::tr1::shared_ptr<Iinserter> inserter, const std::string& delim, std::string * fields, size_t size);

    void InsertBook();
private:
    std::tr1::shared_ptr<Parser>  m_source;
    std::tr1::shared_ptr<Iinserter> m_inserter;
};

}

#endif