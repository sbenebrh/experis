#include <stddef.h>
#include "Book.h"
#include "Record.h"
#include "Borrower.h"

class  RecordBook: public Record
{
friend class BookAdmin;
friend class Lib;
private:
    
    size_t m_nOfCopies;
    RecordBook(const RecordBook& _recordBook);
    const RecordBook& operator==(const RecordBook& _rec);
    enum status 
    {
        AVAILABLE,
        OUT
    }m_status;
    
public:
    RecordBook(Book* _book, size_t _nofCopies);
    const size_t& GetNumOfCopies() const ;
    bool IsAvailable() const; // return true if number of copie > size of the container

protected:
    size_t SetNumberOfCopies(size_t _copies);
    void AddBorrower(const Borrower& _borrower); // throw exception
    void RemoveBorrower(const Borrower& _borrower); //throw expcetion if the borower isnt in the container


    virtual ~ RecordBook();
};

