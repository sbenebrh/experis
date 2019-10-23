#include <vector>
#include "Item.h"

class Record
{
public:
    const vector<Item*>& GetContainer() const ;
    const Item*& GetItem() const ;

    virtual ~Record() = 0;
protected:
    Item* m_Item;
    vector<Item*> m_container;

};


Record::~Record()
{
    
}