#include "Book.h"

#include <iostream>
#include <iterator>
#include <algorithm>

#include "Publisher.h"
#include "Author.h"

namespace advcpp
{
Book::Book(ISBN isbn, const std::string & title, 
            shared_ptr<Author> author, Year year, \
                shared_ptr<Publisher> publisher )
: m_ISBN(isbn)
, m_year(year)
, m_title(title)
, m_author(author)
, m_publisher(publisher)
{

}
const ISBN& Book::GetISBN() const 
{
    return m_ISBN;
}

const std::string & Book::GetTitle() const 
{
    return m_title;
}

const shared_ptr<Author> Book::GetAuthor() const
{
    return m_author;
}

const Year& Book::GetYear() const
{
    return m_year;
}

const shared_ptr<Publisher> Book::GetPublisher() const
{
    return m_publisher;
}

bool operator==(const Book & a, const Book & b )
{
    return a.GetISBN() == b.GetISBN(); 
}

std::ostream& operator<<(std::ostream& os , const Book& book)
{
    os << "ISBN: "<< book.GetISBN() << std::endl;
    os << "Title: "<< book.GetTitle() << std::endl;
    os << "Year: "<< book.GetYear() << std:: endl;
    os << "Author: "<< *book.GetAuthor() << std::endl;
    os << "Publisher: "<< *book.GetPublisher() << std::endl;
    return os;
}


class Printer
{
public:
    Printer(std::ostream& os): m_os(os){}
    void operator()(const shared_ptr<Book> pBook)
    {
        m_os << pBook -> GetISBN() << " | " << pBook -> GetTitle() 
            << " | "  <<*( pBook -> GetAuthor() )<< " | " 
            << pBook -> GetYear() << " | " << *(pBook -> GetPublisher())  << std::endl;
    }

private:
    std::ostream& m_os;
};

std::ostream& operator<<(std::ostream& os , const std::set<shared_ptr<Book> > & pbooks)
{
    std::for_each(pbooks.begin(), pbooks.end(), Printer(os));
    return os;
}

} // advcpp
