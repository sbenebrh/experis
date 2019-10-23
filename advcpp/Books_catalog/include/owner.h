#ifndef OWNER_H
#define OWNER_H

#include <string>
#include <set>
#include <tr1/memory>

#include "Book.h"

namespace advcpp
{
    
using std::tr1::shared_ptr;
class Book;

class Owner:NonCopyable
{

public:
    typedef std::set< shared_ptr<Book> >::iterator Iter;  
    Owner(const std::string& name);
    
    
    void AddBook(shared_ptr<Book> );

    const std::set<shared_ptr<Book> >& GetBibliography() const ; 
    const std::string & GetName() const ;

    Iter Begin() ;
    Iter End();
    virtual ~Owner(){}


private:
    const std::string m_name; 
    //change it to set 
    std::set<shared_ptr<Book> > m_bibliography;
};
bool operator==(const Owner& a, const Owner & b);
std::ostream & operator<<(std::ostream& os, const Owner& Owner);
}

#endif
