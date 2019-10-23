#ifndef __TCONTAINER_H__
#define __TCONTAINER_H__

#include <stddef.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

template < class T, template< typename,typename S = allocator<T*>  > class container >
class tContainer_t
{

public:
    typedef typename container<T*>::const_iterator iter_t;
    
    tContainer_t(){};
    tContainer_t(container<T*> _container): m_container(_container){};
    virtual ~tContainer_t(){};
    bool Isempty() const { return m_container.empty();}
    size_t GetNumberOfElement() const {return m_container.size();};
    void insert(const T* _item); //throw exception
    //not const T* because we dont change data member
    const T* FirstElement() const { if(Isempty()){ throw string("empty container");}return *(m_container.begin());} // throw exception(empty)
    const T* LastElement() const { if(Isempty()){throw string("empty container");} return  *(m_container.rbegin());} // throw exception(empty)
    const T* Find(const T& value ) const;
    T* Remove(const T& _element) ; // throw exception
    void RemoveAll() ;
    void Delete(const T& _element, void (*destroy)(T* _pelement)); //throw exception
    void DeleteAll(void (*destroy)(T* _pelement));
    const T* operator[](size_t _index) const; //throw exception
    T* operator[](size_t _index);
protected:
class GreaterValue{
public: 
    GreaterValue(T i) :val(i){}
    bool operator()(T* param){ return *param > val;}
private:
T val;
};

private:
    container<T*> m_container ;

    tContainer_t(const tContainer_t& _container);
    tContainer_t& operator=(const tContainer_t& _container);

}; 

template < class T, template< typename, typename S  > class container >
void tContainer_t<T,container >::insert(const T* _item)
{
    
    if(NULL == _item)
    {
        throw string("null pointer");
    }
    
    m_container.insert(m_container.end(),(T*) _item);
}

template < class T, template< typename, typename  S > class container >
T* tContainer_t<T,container>::Remove(const T& _element) 
{
    iter_t it = m_container.begin();
    for(; it != m_container.end();++it)
    {
        if(**it = _element)
        {
            m_container.erase(it);
            return *it;
        }
    }
    throw _element;
}

template < class T, template< typename, typename  S > class container >
void tContainer_t<T,container>::RemoveAll()
{
    m_container.erase(m_container.begin(), m_container.end());  
}

template < class T, template< typename, typename S  > class container >
void tContainer_t<T,container>::Delete(const T& _element, void (*destroy)(T* _pelement))
{
    iter_t it = m_container.begin();
    for(; it != m_container.end();++it)
    {
        if(**it = _element)
        {
            T* deleted = m_container.erase(it);
            if(destroy!= NULL)
            {
                destroy(deleted);
            }
            return ;
        }
    }
    throw _element;
}

template < class T, template< typename, typename S  > class container >
void tContainer_t<T,container>::DeleteAll(void (*destroy)(T* _pelement))
{
    iter_t it = m_container.begin();
    for(; it != m_container.end();++it)
    {
        T* deleted = m_container.erase(it);
        if(destroy!= NULL)
            {
                destroy(deleted);
            }  
    }
}

template < class T, template< typename, typename S = allocator<T*>  > class container >
T* tContainer_t<T,container>::operator[](size_t _index)
{
    if(m_container.size()<= _index)
    {
        throw string("out of bound");
    }


    if(typeid(container<T*>) == typeid(vector<T*>))
    {
        return (*(vector<T*>*)&m_container)[_index];
    }
    else
    {
        iter_t it = m_container.begin();
        for (int i = 0;i  < _index; ++i, ++it);
        return *it;
    }  
}

template < class T, template< typename, typename S =allocator<T*>  > class container >
const T* tContainer_t<T,container>::operator[](size_t _index) const
{
    if(m_container.size()<= _index)
    {
        throw string("out of bound");
    }
    if(typeid(container<T* >) == typeid(vector<T*>))
    {
        return (*(vector<T*>*)&m_container)[_index];
    }
    else
    {
        iter_t it = m_container.begin();
        for (int i = 0;i  < _index; ++i, ++it);
        return *it;
    }
}

template < class T, template< typename, typename  S =allocator<T*>  > class container >
const T* tContainer_t<T,container>::Find(const T& value ) const
{
    return *(find_if(m_container.begin(), m_container.end(), GreaterValue(value)));
}
#endif // __TCONTAINER_H__