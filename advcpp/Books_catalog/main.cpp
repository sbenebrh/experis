#include <iostream>
#include <fstream>
#include <tr1/memory>

#include "Catalog.h"
#include "BookReader.h"
#include "Query.h"
#include "Book.h"

int main()
{
using std::tr1::shared_ptr;

shared_ptr<advcpp::Catalog> catalog(new advcpp::Catalog);
std::ifstream is("/home/samuel/Downloads/books-42.txt");
std::string fields[] = {"ISBN", "TITLE", "AUTHOR", "YEAR", "PUBLISHER"};
advcpp::BookReader br(is, catalog, "|", fields, 5 );
br.InsertBook();
advcpp::Query query(catalog);

int choice = -1;
while(choice != 0)
{
    std::cout << "1- Search by ISBN " << std::endl;
    std::cout << "2- Search by Keywords" << std::endl;
    std::cout << "0- exit"<< std::endl;

    std::cin >> choice;

    switch (choice)
    {
        case 1:
        {
            std::cout << "enter an isbn" << std::endl;
            std::string isbn;
            std::cin >> isbn;
            std::cout<< *query.GetBook(advcpp::ISBN(isbn))<< std::endl;
            break;
        }
        case 2:
        {
            std::cout <<"enter keywords" << std::endl;
            std::string str;
            std::cin.get();
            getline(std::cin, str, '\n');
            std::cout << query.GetBook(str) << std::endl;
            
            break;
        }
        default:
            break;
    }
}

}