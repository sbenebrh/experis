#ifndef __MEMPAGE_H__
#define __MEMPAGE_H__
#include "memManager_t.h"

class MemPage_t:public MemManager_t
{
private:
    char* m_buffer;
    static size_t s_capacity;
    const size_t m_capacity;
    //CTOR avoid copy 
    MemPage_t(const MemPage_t& _memPage);
    const MemPage_t& operator=(const MemManager_t& _memPage);
   
public:
    MemPage_t():m_capacity(s_capacity) { m_buffer = new char[m_capacity];}
    MemPage_t(size_t _capacity):m_capacity(_capacity) { m_buffer = new char[m_capacity];}
    virtual ~MemPage_t()  { delete[] m_buffer;}

    virtual size_t     read(size_t _position, const void* _buff, size_t _size);  // read from a specific position
    virtual size_t     read(const void* _buff, size_t _size);
    virtual size_t     write(size_t _position, const void* _buff, size_t _size); // write from a specific position
    virtual size_t     write(const void* _buff, size_t _size);  
            bool    IsFull() const { return m_capacity == GetSize();} 
    static  size_t  GetCapacity()  { return s_capacity;} 
    static  size_t  SetCapacity(size_t _capacity) 
            {
                size_t c = s_capacity;
                s_capacity = _capacity;
                return c;
            }
};






#endif /*__MEMPAGE_H__*/
