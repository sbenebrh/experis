
#include "Admin.h"
#include "Borrower.h"
#include "Book.h"

class BookAdmin:public Admin
{
friend class Lib; 
public:
BookAdmin();

virtual void            Add(size_t _number, const Item& _item) ; // catch exception .try to update record and if not exist(cath exception Create a new Record)
virtual void            Remove(const Item& _item) ; //throw exception
virtual const vector< Item*>& Search(size_t _key, SearchKeyType _type) = 0; // throw exception exception. for improve the complexity search by ISBN for book or ID for borrower
virtual const Record&    Report(const Item& _item)  ; //throw exception
        const vector< Borrower*>& HasBorrowed(const Book& _book) const ; // throw exception

protected:
void updateRecord(const Book& _book) const ; // throw exception
~BookAdmin();
private:
BookAdmin(const BookAdmin& _bAd);
const BookAdmin& operator=(const BookAdmin& _bAd);
};