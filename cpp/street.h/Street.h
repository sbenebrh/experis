#ifndef __STREET_H__
#define __STREET_H__
#include <vector>
#include "Building.h"

using namespace std;

template<class T, class S>
class Street_t
{
public:
    Street_t(const T& _id);
    virtual ~Street_t();
    const T SetStreetID(const T& _id);
    const T& GetStreetID() const;
    Street_t<T, S>& operator=(const Street_t& _Street);
    void AddBuilding2Street(Building_t<S>* _building);
    const Building_t<S>& GetBuilding(const S& _id);

private:
    T m_Id;
    vector<Building_t<S>*> m_vec;
    Street_t(const Street_t& _buiding);
};

template<class T, class S>
Street_t<T, S>::Street_t(const T& _id)
{
    m_Id = _id;
}


template<class T, class S>
const T Street_t<T, S>::SetStreetID(const T& _id)
{
    T oldId = m_Id;
    m_Id = _id;
    return oldId;
}

template<class T, class S>
const T& Street_t<T, S>::GetStreetID() const
{
    return m_Id;
}

template<class T, class S>
Street_t<T,S>& Street_t<T, S>::operator=(const Street_t& _Street)
{
    if(this != & _Street)
    {
        m_vec = _Street.m_vec;
    }
    return *this;

}

template<class T, class S>
void Street_t<T, S>::AddBuilding2Street(Building_t<S> *_building)
{
    m_vec.push_back( _building);
}

template<class T, class S>
const Building_t<S>& Street_t<T, S>::GetBuilding(const S& _id)
{
    size_t size = m_vec.size();
    while(size)
    {
        if(m_vec[--size] -> GetBuildingID() == _id)
        {
            return *m_vec[size];
        } 
    }
}

template<class T, class S>
Street_t<T, S>::~Street_t()
{   
    
  
}
#endif /* __STREET_H__*/
