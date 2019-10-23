#include "BookDetails.h"

namespace advcpp
{
BookDetails::BookDetails(std::string isbn, std::string title, std::string author, std::string year, std::string publisher)
: m_ISBN(isbn)
, m_title(title)
, m_Author(author)
, m_year(year)
, m_Publisher(publisher)
{

}

const std::string &  BookDetails::Title() const
{
    return m_title;
}

const std::string &  BookDetails::Author() const
{
    return m_Author;
}

const std::string &  BookDetails::Year() const
{
    return m_year;
}

const std::string &  BookDetails::Publisher() const
{
    return m_Publisher;
}

const std::string &  BookDetails::ISBN() const
{
    return m_ISBN;
}

}