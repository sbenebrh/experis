#ifndef BOOKDETAILS_H
#define BOOKDETAILS_H

#include <string>

namespace advcpp
{
class BookDetails{
public:
    BookDetails(std::string isbn, std::string title, std::string author, std::string year, std::string publisher);
    const std::string &  Title() const;
    const std::string &  Author() const;
    const std::string &  Year() const;
    const std::string &  Publisher() const;
    const std::string &  ISBN() const;

private:
    std::string m_ISBN;
    std::string m_title;
    std::string m_Author;
    std::string m_year;
    std::string m_Publisher;
};
}

#endif