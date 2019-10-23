#ifndef CATALOG_H
#define CATALOG_H

#include <tr1/memory>
#include <unordered_map>
#include <tr1/unordered_map>
#include <set>

#include "Book.h"
#include "Author.h"
#include "Publisher.h"
#include "Iquery.h"
#include "Iinserter.h"
#include "BookDetails.h"
#include "ISBN.h"
#include "IndexBy.h"

namespace advcpp
{
using std::tr1::shared_ptr;


class Catalog:public Iinserter , public Iquery, NonCopyable
{

public:
    Catalog();

    void insert(const BookDetails& details); //should be private and only for test debug it is public

    virtual shared_ptr<Book> GetBook(const ISBN& isbn) const ;
    virtual std::set<shared_ptr<Book> > GetBook(std::string keyword) const ;

private:
    Catalog(const Catalog& catalog);
    Catalog& operator= (const Catalog& catalog);
    

    template<typename T>
    shared_ptr<T> findIntoContainer(const std::string& str, IndexBy<std::string , shared_ptr<T> >& container);

    void updateCatByKey(std::string title, shared_ptr<Book> pBook);
    std::set< shared_ptr<Book> > getIntersectionBook(std::string keyword, std::set< shared_ptr<Book> >& original) const;
    

private:
    typedef shared_ptr<Book> pBook;
    typedef std::string keyword;
    typedef std::set<pBook> CatByKey;
    typedef std::string name;

    IndexBy<std::string , pBook> m_catalog;
    IndexBy<keyword, CatByKey> m_catByKeyword;
    IndexBy<name , shared_ptr<Author> > m_catAuthor;
    IndexBy<name , shared_ptr< Publisher> > m_catPublisher;

};

}


#endif
