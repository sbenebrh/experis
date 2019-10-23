#ifndef __CITY_H__
#define __CITY_H__

#include "Street.h"

template<class T, class S, class V>
class City_t
{
public:
    City_t(const T& _id);
    virtual~City_t();
    void SetCityID(const T& _id);
    const T& GetCityID() const;
    void AddStreet(const Street_t<S,V>* _Street);
    const Street_t<S,V>& GetStreet(const S& _id) const;

private:
    T m_id;
    vector<Street_t<S,V>*> m_vec;
    City_t(const City_t& _city);
    const City_t<T,V,S> operator=( City_t<T,V,S>& _city );
};

template<class T, class S, class V>
City_t<T,S,V>::City_t(const T& _id)
{
    m_id = _id;
}

template<class T, class S, class V>
City_t<T,S,V>::~City_t()
{
     int size = m_vec.size();
    while(size > 0)
    {
        delete m_vec[--size];
    }
}

template<class T, class S, class V>
void City_t<T,S,V>::SetCityID(const T& _id)
{
    m_id = _id;
}

template<class T, class S, class V>
const T& City_t<T,S,V>::GetCityID() const
{
    return m_id;
}

template<class T, class S, class V>
void City_t<T,S,V>::AddStreet(const Street_t<S,V>* _Street)
{
    m_vec.insert(m_vec.end(), &_Street);
}

template<class T, class S, class V>
const Street_t<S,V>& City_t<T,S,V>::GetStreet(const S& _id) const
{
    size_t size = m_vec.size();
    while(size)
    {
        if(m_vec[size--] -> GetStreetID() == _id)
        {
            return *m_vec[size++];
        } 
    }
}

#endif /*__CITY_H__*/