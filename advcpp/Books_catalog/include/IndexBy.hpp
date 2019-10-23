#include "IndexBy.h"

namespace advcpp
{

template<typename Key, typename Value>
IndexBy<Key,Value>::IndexBy(Iter b, Iter e)
{
    m_index.insert(b, e);
}

template<typename Key, typename Value>
IndexBy<Key,Value>::IndexBy()
{
}

template<typename Key, typename Value>
void IndexBy<Key,Value>::add(Key k, Value v)
{
    m_index[k] = v;
}

template<typename Key, typename Value>
bool IndexBy<Key,Value>::search(Key k, Value& out) const
{
    typename std::tr1::unordered_map<Key, Value>::const_iterator it = m_index.find(k);
    if(it == m_index.end())
    {
        return false;
    }
    out = (it -> second);
    return true;
}

template<typename Key, typename Value>
Value& IndexBy<Key,Value>::operator[](Key k )
{
    return m_index[k];
}

}