#include "memPool_t.h"
#include <iostream>


MemPool_t::MemPool_t()
{
    MemPage_t* memPage = new MemPage_t;
    v.insert(v.end(), memPage);    
}


size_t MemPool_t::read(size_t _position, const void* _buff, size_t _size)
{
    size_t read = 0;
    if(_buff == NULL || _position == GetSize())
    {
        return 0;
    }
    SetPosition(_position);
    size_t page = GetPage(GetPositon());
    
    size_t sizeVector = v.size();
    // read while its possible may from many pages at once
    while(sizeVector > page )
    {
        read += v[page] -> read((char*)_buff + read, _size -read);
        if(read == _size)
        {
            break;
        }
        page++;
        v[page] -> SetPosition(0);
    }
    
    SetPosition(GetPositon() + read);
    return read;
}

size_t MemPool_t::read(const void* _buff, size_t _size)
{
    return read(GetPositon(), _buff, _size);
}


size_t MemPool_t::write(size_t _position, const void* _buff, size_t _size)
{
    size_t write = 0;
    if(_buff == NULL)
    {
        return 0;
    }
    SetPosition(_position);
    size_t page = GetPage(GetPositon());

    // write until we reach the _size maybe on more than one file
    size_t sizeVector = v.size();
    while(1)
    {
        write += v[page] -> write((char*)_buff + write, _size - write);
        if(write == _size)
        {
            break;
        }
        // no more page in the vector
        if(sizeVector == page -1)
        {
            MemPage_t* memPage = new MemPage_t;
            v.insert(v.end(), memPage);
        }

        page++;
    }
    size_t newPosition = GetPositon();
    size_t size = (newPosition + write < GetSize() ? GetSize() : newPosition + write);
    SetSize(size);
    SetPosition(GetPositon() + write);
    
    return write;

}

size_t MemPool_t::write(const void* _buff, size_t _size)
{
    return write(GetPositon(), _buff, _size);
}

size_t MemPool_t::GetPage(size_t _position)
{
    size_t page       = 0;
    size_t globalPosition = 0;
    size_t insidePosition = 0;

    vector<MemPage_t*>::iterator it = v.begin();
    for(;it != v.end();++it)
    {
        if((globalPosition  + (*it ))-> GetSize() < _position)
        {
            globalPosition += (*it )-> GetSize();
            page++;
        }
        else
        {
            globalPosition += _position - globalPosition;
            insidePosition = _position - globalPosition;
            break;
        }
    }
    (*it) -> SetPosition(insidePosition);
    return page++;
}

MemPool_t::~MemPool_t() 
{
    vector<MemPage_t*>::iterator it = v.begin();
    for(;it != v.end();++it)
    {
        delete *it;
    }
}

