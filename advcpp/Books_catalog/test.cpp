#include "Iinserter.h"
#include "Catalog.h"
#include <tr1/memory>
#include <iostream>
#include "Book.h"
#include "BookDetails.h"

int main()
{
    advcpp::Catalog * catalog = new advcpp::Catalog;
    std::tr1::shared_ptr<advcpp::Iinserter > inserter (catalog );
    inserter -> insert(advcpp::BookDetails("12345","the new begining", "john Collins","1990",  "Galia")); 
    inserter -> insert(advcpp::BookDetails("23456", "the new empire", "john Collins","1945",  "Galia"));
    inserter -> insert(advcpp::BookDetails("2346", "the new commandement", "john Collins","1915",  "Galia"));


    std::tr1::shared_ptr<advcpp::Iquery> query(catalog);
    //std::set<std::tr1::shared_ptr<advcpp::Book> > books = query -> GetBook(" the new");
    
    std::cout << *(query ->GetBook(12345))<< std::endl ;
    
    std::set<std::tr1::shared_ptr<advcpp::Book> > books = query -> GetBook("the new");
    size_t size = books.size();
    
    std::set<std::tr1::shared_ptr <advcpp::Book> >::iterator it = books.begin();
    for(size_t i = 0; i < size; ++i)
    {
        std::cout << **it << std::endl;
        ++it;
    }
}

 