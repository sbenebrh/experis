#include "Catalog.h"

#include <tr1/memory>
#include <exception>
#include <stdexcept>
#include <tr1/unordered_map>
#include <iostream>
#include <bits/stdc++.h> 
#include "Book.h"
#include "Author.h"
namespace advcpp
{

using std::tr1::unordered_map;
using std::tr1::shared_ptr;


Catalog::Catalog()
{
    
}

shared_ptr<Book> Catalog::GetBook(const ISBN& isbn) const 
{
   shared_ptr<Book> out;
    if(m_catalog.search(isbn.GetISBN(),out)== true)
    {
        return out;
    }
    throw std::out_of_range("the book is not in the catalog");
     
}

void Catalog::insert(const BookDetails& bd)
{
    /*
    - findAuthor(author);
    - if not found create the author and insert into the container
    - findPublisher(Publisher);
    - if not found  create Publisher and insert into the container
    - create book and insert it into the container
    - insert ptr to book to the author and publisher
    - add pointer to book to kewyword catalog
    */
    shared_ptr<Author> pAuthor = findIntoContainer<Author>(bd.Author(), m_catAuthor);
    shared_ptr<Publisher> pPublisher = findIntoContainer<Publisher>(bd.Publisher(), m_catPublisher);
    shared_ptr<Book> pBook;
    try
    {
        shared_ptr<Book> temp(new Book(ISBN( bd.ISBN()), bd.Title(), pAuthor, Year( std::stoi(bd.Year())), pPublisher));
        pBook = temp;
    }
    catch(const std::exception& e)
    {
        shared_ptr<Book> temp(new Book(ISBN( bd.ISBN()), bd.Title(), pAuthor, Year( 0), pPublisher));
        pBook = temp;
    }
    

    //safe zone
    m_catalog.add(bd.ISBN() , pBook);
    m_catAuthor.add(bd.Author(), pAuthor);
    m_catPublisher.add(bd.Publisher(), pPublisher);

    pAuthor -> Author::AddBook(pBook);
    pPublisher -> Publisher::AddBook(pBook);

    updateCatByKey(bd.Title(), pBook);

}


template<typename T>
shared_ptr<T> Catalog::findIntoContainer(const std::string& str, IndexBy<std::string , shared_ptr<T> >& container)
{
    shared_ptr<T> pObject;
    if(container.search(str, pObject) == false)
    {
        shared_ptr<T> ptemp(new T(str));
        pObject = ptemp;
    }
    return pObject;
}  

void Catalog::updateCatByKey(std::string title, shared_ptr<Book> pBook)
{
    std::istringstream str(title);
    
    while (str)
    {
        std::string word ;
        str >> word;
        if(word == "")
        {
            break;
        }
        
        m_catByKeyword[word].insert(pBook);
    }      
}

std::set<shared_ptr<Book> > Catalog::GetBook(std::string keywords) const
{
     /*go over every word
     - if word start with '-' got or of book with this word
     else got intersection
     */
    std::istringstream str(keywords);
    std::set<shared_ptr<Book> > nonWantedWord;
    std::set<shared_ptr< Book> > intersection;
    // check if it is the first word
    bool flag = false;

    char delim = '-';
    while (str)
    {
        std::string word ;
        str >> word;

        if(word[0] == delim)
        {
            std::string key = word.substr(1,word.length());
            std::set<shared_ptr<Book> > setBook;
            if(m_catByKeyword.search(key, setBook) == true)
            {
                nonWantedWord.insert(setBook.begin(), setBook.end());
            }
        }
        else if(flag == true)
        {
            try
            {
                std::set<shared_ptr< Book> > temp = getIntersectionBook(word, intersection);
                intersection  = temp; 
            }catch(std::exception ex)
            {
                break;
            }
        }
        else
        {
            std::set<shared_ptr<Book> > setBook;
            if(m_catByKeyword.search(word, setBook) == true)
            {
                intersection.insert(setBook.begin(), setBook.end());
            }
            flag = true;
        }  
    } 
    std::set< shared_ptr<Book> >result;
    std::set_difference(intersection.begin(), intersection.end(), nonWantedWord.begin(), nonWantedWord.end(),
    std::inserter(result, result.end()));
    return result;
}



std::set< shared_ptr<Book> > Catalog::getIntersectionBook(std::string keyword, std::set<shared_ptr< Book> >&intersection) const
{
    std::set< shared_ptr<Book> > out;
    std::set< shared_ptr<Book> > intersectionBooks;

    if(m_catByKeyword.search(keyword, out) == true)
    {
               std::set_intersection(intersection.begin(), intersection.end(), 
                           out.begin(), out.end(), 
                            std::inserter(intersectionBooks, intersectionBooks.end()));
                            return intersectionBooks;
    }
    throw std::out_of_range("no intersection");
}

} // advcpp
