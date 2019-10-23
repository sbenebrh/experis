#include "Query.h"

namespace advcpp
{

Query::Query(shared_ptr<Iquery> query)
: m_query(query)
{

}

shared_ptr<Book> Query::GetBook(const ISBN& isbn) const
{
    return m_query -> GetBook(isbn);
} 

std::set<shared_ptr<Book> > Query::GetBook(const std::string& keyword) const 
{
    return m_query -> GetBook(keyword);
}

}