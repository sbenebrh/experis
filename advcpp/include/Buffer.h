#ifndef BUFFER_H
#define BUFFER_H

#include <cstddef> //size_t
#include <exception>
#include <iterator>

#include "Flags.h"

namespace advcpp
{

template<class T>
class Buffer
{
    typedef unsigned char Byte;
    static const int defaultSize = 64;
public:
    typedef T* Iter;
    typedef const T* const CIter;
    //typedef const T* ConstIter 
    Buffer(size_t capacity = defaultSize);
    ~Buffer();

    Buffer(const Buffer& original);
    Buffer& operator=(const Buffer& original);
    

    size_t Capacity() const;
    const T& Get(size_t index) const; 

    T& operator[](size_t index); 
    const T& operator[](size_t index) const ;

    T& Put(const T& item, size_t index);
    void Grow(size_t factor);
    void Shrink(size_t factor);

    //ConstIter Begin() const; to protect the T and not the pointer
    const Iter Begin() const ;
    const Iter End() const;

    const CIter CBegin() const ;
    const CIter CEnd() const;



private:

    Byte* growCapacity(size_t newCapacity);
    void DeleteElement(size_t index);
    void DeleteAll();
    void resize(size_t newSize);

private:
    Flags m_flags;
    Byte* m_data;
    size_t m_capacity;
    
};

//create a class flags and initialize it first in order to avoid memory leaks
template<class T>
Buffer<T>::Buffer(size_t capacity)
: m_flags(capacity)
, m_data(new Byte[capacity * sizeof(T)])
, m_capacity(capacity)
{

}

template<class T>
Buffer<T>::~Buffer()
{
    DeleteAll();   
}

template<typename U>
class Copier
{
    size_t i;
    const Flags& m_flags;
    typename Buffer<U>::Iter target;
public:
    Copier(typename Buffer<U>::Iter target,const Flags& flags)
    :i(0)
    , m_flags(flags)
    , target(target)
    {

    }
    void operator()(U& obj)
    {
        if(m_flags[i++])
        {
            new(target) U(obj);
        }
        ++target;
    }
};

template<class T>
Buffer<T>::Buffer(const Buffer& original)
: m_flags(original.m_flags)
, m_data(new Byte[original.m_capacity])
, m_capacity(original.m_capacity)
{
    std::for_each(original.Begin(), original.End(), Copier<T>(Begin(), original.m_flags));
}

template<class T>
Buffer<T> & Buffer<T>::operator=(const Buffer& original)
{

    if(this == & original)
    {
        return *this;
    }

    Buffer<T> tmp(original);
    std::swap(tmp.m_data, m_data);
    m_flags = original.m_flags;
    m_capacity = original.m_capacity;

    return *this;
}

template<typename U>
class Destroyer
{
    size_t i;
    const Flags& m_flags;
public:
    Destroyer(const Flags& flags):i(0), m_flags(flags){}
    void operator()(U& obj)
    {
        if(m_flags[i++])
        {
            obj.U::~U();
        }
    }
};

template<class T>
void Buffer<T>::DeleteAll()
{
    std::for_each(Begin(), End(), Destroyer<T>(m_flags));
    delete[] m_data;
}

template<class T>
const typename Buffer<T>::Iter Buffer<T>::Begin() const
{
    return reinterpret_cast<Buffer<T>::Iter>(m_data);
}

template<class T>
const typename Buffer<T>::Iter Buffer<T>::End() const
{
    return reinterpret_cast<Buffer<T>::Iter>(m_data + (m_capacity * sizeof(T)));
}

template<class T>
void Buffer<T>::DeleteElement(size_t index)
{
    Buffer<T>::Iter it = Begin();
    it += index;
    it -> T::~T(); 
    m_flags.UnmarkeSlot(index);
}

template<class T>
typename Buffer<T>::Byte* Buffer<T>::growCapacity(size_t newCapacity)
{
    Byte* temp = new Byte[newCapacity * sizeof(T)];
    return temp;

}

template<class T>
size_t Buffer<T>::Capacity() const
{
    return m_capacity ;
}

template<class T>
const T& Buffer<T>::Get(size_t index) const
{
    if(!m_flags[index])
    {
        throw std::out_of_range("the index is too big or no object");
    }
    return *this[index];
}

template<class T>
void Buffer<T>::Grow(size_t factor)
{
    size_t newCapacity = m_capacity + factor;
    Byte* temp = growCapacity(newCapacity);
    m_capacity = newCapacity;
    m_flags.Grow(factor);

    Iter itNew = reinterpret_cast<Buffer<T>::Iter>(temp);
    std::for_each(Begin(), End(), Copier<T>(itNew, m_flags));

    DeleteAll();
    m_data = temp;
}

template<class T>
void Buffer<T>::Shrink(size_t factor)
{
    size_t newCapacity = m_capacity - factor;
    Byte* temp = growCapacity(newCapacity);

    Iter itNew = reinterpret_cast<Buffer<T>::Iter>(temp);
    Iter itEnd = reinterpret_cast<Buffer<T>::Iter>(temp + (newCapacity * sizeof(T)));
    std::for_each(itNew, itEnd, Copier<T>(Begin(), m_flags));

    DeleteAll();
    m_data = temp;
    m_capacity = newCapacity;
}

void resize(size_t newSize)
{
    
}

template<class T>
T& Buffer<T>::operator[](size_t index)
{
    Iter it = Begin();
    it += index;
    return *it;
}

template<class T>
const T& Buffer<T>::operator[](size_t index) const
{
    Iter it = Begin();
    it += index;
    return *it;
}

template<class T>
T& Buffer<T>::Put(const T& item, size_t index)
{
    if(index >= m_capacity )
    {
        throw std::out_of_range("the index is too big or no object");
    }
    
    Iter target = Begin() + index;
    if(m_flags[index])
    {
        
        *target = item;
        return *target;
    }
    m_flags.MarkeSlot(index);
    return * new(target) T(item);
}


}

#endif //BUFFER_H