
#include <string>

using namespace std;
class Item
{
public:
size_t GetID() const ;
string GetName() const ; 
virtual ~Item()  = 0  ;

protected:
string m_name;
const size_t m_Id;


};
Item::~Item() 
{}
