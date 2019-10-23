#ifndef QUERY_H
#define QUERY_H

#include "Iquery.h"
#include<set>

namespace advcpp
{

class Query
{
public:
    Query(shared_ptr<Iquery> query);

    shared_ptr<Book> GetBook(const ISBN & isbn) const; 
    std::set<shared_ptr<Book> > GetBook(const std::string& keyword) const ;
    
private:
    shared_ptr<Iquery> m_query;
};

}

#endif