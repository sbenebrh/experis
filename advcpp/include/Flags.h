#ifndef FLAGS_H
#define FLAGS_H

#include <cstddef> 
#include <algorithm>
#include <stdexcept>

namespace advcpp
{

class Flags
{
    
// become of typedef char create a flag with default ctr to init every flag
public:
    typedef char Flag;
    typedef Flag* Iter;
    typedef const Flag* const CIter;

    Flags(size_t capacity);
    
    Flags(const Flags& original);
    Flags& operator=(const Flags& original);

    ~Flags();

    bool IsMarkedSlot(size_t index);
    void MarkeSlot(size_t index);
    void UnmarkeSlot(size_t index);
    void Grow(size_t factor);

    const Flag& operator[](size_t index) const;
    Flag& operator[](size_t index);


    const Iter Begin() const;
    const Iter End()  const;

    CIter CBegin() const;
    CIter CEnd()  const;

private:

    void initFlags();

private:
    Flag* m_flags;
    size_t m_capacity;

};




Flags::Flags(size_t capacity)
: m_flags(new Flag[capacity])
, m_capacity(capacity)
{
    initFlags();
}

Flags::Flags(const Flags& original)
: m_flags(new Flag[original.m_capacity])
, m_capacity(original.m_capacity)
{
    Iter it = original.Begin();
    Iter end = original.End();

    std::copy(it, end, m_flags);
}

Flags& Flags::operator=(const Flags& original)
{
    if(this == & original)
    {
        return *this;
    }

    Flags tmp(original);
    std::swap(tmp.m_flags,m_flags );

    return *this;
}

Flags::~Flags()
{
    delete[] m_flags;
}

bool Flags::IsMarkedSlot(size_t index)
{
    if(index >= m_capacity)
    {
        throw std::out_of_range("index too big");
    }
    return m_flags[index] == 1;
}

void Flags::MarkeSlot(size_t index)
{
    if(index >= m_capacity)
    {
        throw std::out_of_range("index too big");
    }
    m_flags[index] = 1;
}

void Flags::UnmarkeSlot(size_t index)
{
    if(index >= m_capacity)
    {
        throw std::out_of_range("index too big");
    }
    m_flags[index] = 0;
}


void Flags::Grow(size_t factor)
{
    size_t newCapacity = m_capacity + factor;
    Flag *temp = new Flag[newCapacity];

    Iter target = reinterpret_cast<Iter>(temp);
    Iter source = Begin();
    Iter end = End();

    for (size_t i = 0; source != end; ++i)
    {
        *target = *source;
        ++target;
        ++source;
    }

    Iter endTarget = reinterpret_cast<Iter>(temp + (newCapacity * sizeof(Flag)));
    std::fill(target, endTarget, 0);
  
    delete[] m_flags;
    m_flags = temp;
    m_capacity = newCapacity;

}

const Flags::Flag& Flags::operator[](size_t index) const
{
    return *(Begin() + index);
}

Flags::Flag& Flags::operator[](size_t index) 
{
    return *(Begin() + index);
}

const typename Flags::Iter Flags::Begin() const
{
    return reinterpret_cast<Iter>(m_flags);
}

const typename Flags::Iter Flags::End() const
{
    return reinterpret_cast<Iter>(m_flags + (m_capacity * sizeof(Flag)));
}

void Flags::initFlags()
{
    Iter it = Begin();
    Iter end = End();
    std::fill(it, end, 0);
}

}





#endif