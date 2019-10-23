#ifndef __RECORD_BORROWER_H__
#define __RECORD_BORROWER_H__

#include "Book.h"
#include "Record.h"
#include "Borrower.h"
class RecordBorrower:public Record
{
friend class BorrowerAdmin;
public:
    RecordBorrower(const Borrower& _borrower);
    void AddBook(const Book& _book); // throw exception
    const Book& RemoveBook(const Book& Book); //throw expcetion if the book isnt in the container
    
protected:
    virtual ~RecordBorrower();

private:
    RecordBorrower(const RecordBorrower& _rec);
    const RecordBorrower& operator=(const RecordBorrower& _rec);
};

#endif //__RECORD_BORROWER_H__