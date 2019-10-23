#ifndef INDEXBY_H
#define INDEXBY_H

#include <iterator>

#include<tr1/memory>

namespace advcpp
{

template<typename Key, typename Value>
class IndexBy
{
public:
    
    typedef typename std::tr1::unordered_map<Key, Value>::iterator Iter;

    IndexBy(Iter b , Iter e);
    IndexBy();

    void add(Key, Value);
    bool search(Key k, Value& out) const ;

    Value& operator[](Key k );
private:
    typedef std::tr1::unordered_map<Key,Value> Map;
    Map  m_index;
};



}
#include "IndexBy.hpp"

#endif
