#ifndef IQUERY_H
#define IQUERY_H

#include <tr1/memory>
#include <list>

#include "Book.h"

namespace advcpp
{

class Iquery
{
public:    
    virtual shared_ptr<Book> GetBook(const ISBN & isbn) const = 0;
    virtual std::set<shared_ptr<Book> > GetBook(std::string keyword) const = 0;
};

}
#endif