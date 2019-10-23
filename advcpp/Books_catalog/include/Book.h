#ifndef BOOK_H
#define BOOK_H

#include <cstddef>
#include <string>
#include <set>
#include <tr1/memory>

#include "Year.h"
#include "ISBN.h"
#include "NonCopyable.h"

namespace advcpp
{
    
class Author;
class Publisher;

using std::tr1::shared_ptr;

class Book:NonCopyable
{

public:
    Book(ISBN isbn, const std::string & title, shared_ptr<Author> author, Year year, shared_ptr<Publisher> Publisher );
    
    const ISBN& GetISBN() const ;
    const std::string & GetTitle() const ;
    const shared_ptr<Author> GetAuthor() const;
    const Year& GetYear() const;
    const shared_ptr<Publisher> GetPublisher() const;

private:


    ISBN m_ISBN;
    Year m_year;
    const std::string m_title;
    const shared_ptr<Author> m_author;
    const shared_ptr<Publisher> m_publisher;

};

bool operator==(const Book & a, const Book & b );
std::ostream& operator<<(std::ostream& os , const Book& book);
std::ostream& operator<<(std::ostream& od , const std::set<shared_ptr<Book> > & pbooks);

}


#endif
