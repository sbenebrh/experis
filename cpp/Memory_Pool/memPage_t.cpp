#include "memPage_t.h"

#include <string.h>

size_t MemPage_t::s_capacity = 6; // initalize static member

size_t MemPage_t::read(size_t _position, const void* _buff, size_t _size)  
{
    size_t actualReadable = 0;
    size_t position = 0;
    size_t nbytes = 0;
    if(_buff == NULL || _position == GetSize())
    {
        return 0;
    }
    SetPosition(_position);
    position = GetPositon();
    actualReadable = GetSize() - position;
    nbytes = actualReadable < _size ? actualReadable : _size; 
    
    memcpy((char*)_buff, m_buffer + position, nbytes);
    SetPosition(nbytes + position);
    return nbytes;
}

size_t MemPage_t::read(const void* _buff, size_t _size)
{
    return read(GetPositon(), _buff, _size);
}

size_t MemPage_t::write(size_t _position, const void* _buff, size_t _size)
{
    if(_buff == NULL)
    {
        return 0;
    }
    size_t newPosition = 0;
    size_t  freeSpace = m_capacity - GetPositon();
    SetPosition(_position);
    newPosition = GetPositon();
    if(IsFull())
    {
        return 0;
    }
    size_t nbytes = freeSpace < _size? freeSpace: _size;
    memcpy(m_buffer + newPosition, _buff , nbytes);

    size_t size = (newPosition + nbytes < GetSize() ? GetSize() : newPosition + nbytes);
    SetSize(size);
    SetPosition(nbytes + newPosition);

    return nbytes;
}

size_t MemPage_t::write(const void* _buff, size_t _size)
{
    return write(MemManager_t::GetPositon(), _buff, _size);
}