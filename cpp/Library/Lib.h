#ifndef __LIB_H__
#define __LIB_H__

#include <stddef.h>
#include <vector>
#include <string>
#include "Book.h"
#include "Borrower.h"
#include "Record.h"
#include "Admin.h"
using namespace std;
class Lib
{
public:
    void AddBook(const Book& _book,size_t _nofCopies); //catch
    const Book& RemoveBook(const Book& _book) const;// catch
    const Book& SearchBook(size_t _Isbn) const;// catch
    vector<Book*>& SearchBook(string _string) const; //catch
    const vector<Borrower*>& ReportBook(const Book& _book) const;//catch
    void AddBorrower(string _name, string _phone, size_t _id) const ;//catch
    const Record& SearchBorrower(const size_t _id)const ;//catch
    const Borrower& RemoveBorrower(size_t _id) const;//catch
    const Book& Borrow(size_t _isbn, const Borrower&);//catch
    void ReturnBook(Book*_book);//catch


    Lib();
    Lib(const Lib& _lib);
    Lib& operator=(const Lib& _lib);
    virtual ~Lib();
private:
    Admin * m_AdBook;
    Admin * m_AdBorrower;
};

#endif /*__LIB_H__*/
