#include <string>
#include <vector>
#include "Book.h"
#include "Item.h"
using namespace std;

class Borrower:public Item
{
public:

string GetTitle();

Borrower(size_t _isbn, string _author, string _title);
Borrower& operator=(const Borrower& _Borrower);
Borrower(const Borrower& _Borrower);
virtual ~Borrower();

const vector<Book*>& GetBorrowedBooks() const;


protected:
vector<Book*> m_borrowedBooks;

private:
    string m_title;
};