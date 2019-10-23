#include "owner.h"

#include <iterator>
#include <algorithm>
#include <exception>

//#include "Book.h"

namespace advcpp
{
    
Owner::Owner(const std::string& name)
: m_name(name)
{

}


void Owner::AddBook(std::tr1::shared_ptr<Book> pbook )
{
    m_bibliography.insert(pbook);
} 


using std::tr1::shared_ptr;
const std::set<shared_ptr<Book> >& Owner::GetBibliography() const 
{
    return m_bibliography;
}

Owner::Iter Owner::Begin()
{
    return m_bibliography.begin();
}

Owner::Iter Owner::End()
{
    return m_bibliography.end();
}

const std::string & Owner::GetName() const 
{
    return m_name;
}

std::ostream & operator<<(std::ostream& os, const Owner& Owner)
{
    os << Owner.GetName();
    return os;
}



}
