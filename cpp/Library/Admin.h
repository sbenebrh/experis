#ifndef __ADMIN_H__
#define __ADMIN_H__
#include "Record.h"
#include <vector>
#include <map>
#include "Item.h"

using namespace std;
class Admin
{
public:
enum SearchKeyType
{
    NAME,
    ID,
    ISBN,
    AUTHOR,
    TITLE
};

Admin();
Admin(const Admin& _admin);
Admin& operator=(const Admin& _admin);
virtual ~Admin();

virtual void            Add(size_t _number,const Item& _item) = 0;
virtual void            Remove(const Item& _item) = 0;
virtual const vector< Item*>& Search(size_t _key, SearchKeyType _type) = 0; // for improve the complexity search by ISBN for book or ID for borrower
virtual const Record&    Report(const Item& _item) = 0;
 
protected:
map<size_t,Item* > m_vec;

private:

};

#endif /*__ADMIN_H__*/