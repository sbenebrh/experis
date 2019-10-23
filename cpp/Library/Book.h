


#include <stddef.h>
#include <string>

#include "Item.h"

using namespace std;
class Book:public Item
{
public:

const string& GetTitle() const ;
const string& GetPhone() const ;
void SetPhone(const string _phone);


Book(size_t _isbn, string _author, string _title);
Book& operator=(const Book& _book);
Book(const Book& _book);
virtual ~Book();




private:
    string m_title;
   
};
