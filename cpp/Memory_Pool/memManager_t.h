#ifndef __MEMMANAGER_H__
#define __MEMMANAGER_H__
#include<stddef.h> //size_t

class MemManager_t
{
private:
size_t m_position;          // the position of the cursor
size_t m_size;              // the actual written size 

MemManager_t(const MemManager_t& _memManager); 
MemManager_t& operator=(const MemManager_t& _memManager); 

public:
MemManager_t(){ m_position = 0; m_size = 0;}
virtual         ~MemManager_t() ; 

bool                IsEmpty() const    { return !m_size;}
size_t              GetPositon() const { return m_position;}                         //not virtual because the same for every one
size_t              GetSize() const    { return m_size;}
virtual size_t      read(size_t _position, const void* _buff, size_t _size)= 0 ;     // read from a specific position pure virtual
virtual size_t      read(const void* _buff, size_t _size) = 0 ;                      // read from a specific position pure virtual
virtual size_t      write(size_t _position, const void* _buff, size_t _size)  = 0 ;  // write from a specific position
virtual size_t      write(const void* _buff, size_t _size) = 0 ;
size_t              SetPosition(size_t _position) 
{ 
    size_t pos = m_position;
    m_position = (_position <= m_size ? _position:m_position); 
    return pos;
} 
 

protected:
                                                 //virtual dctor because this class will be derived
void            SetSize( size_t _size) { m_size = _size;}

};


#endif /* __MEMMANAGER_H__*/