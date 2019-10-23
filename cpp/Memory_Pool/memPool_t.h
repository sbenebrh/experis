#ifndef __MEMPOOL_H__
#define __MEMPOOL_H__

#include <vector>

using namespace std;

#include "memManager_t.h"
#include "memPage_t.h"

class MemPool_t:public MemManager_t
{
private:
    vector<MemPage_t*> v;
    size_t GetPage(size_t _position);
    MemPool_t(const MemPool_t&);
    const MemPool_t& operator=(const MemPool_t&);
public:
    MemPool_t();
    virtual ~MemPool_t();
    

virtual    size_t read(size_t _position, const void* _buff, size_t _size);  
virtual    size_t read(const void* _buff, size_t _size);
virtual    size_t write(size_t _position, const void* _buff, size_t _size); 
virtual    size_t write(const void* _buff, size_t _size);

    static size_t SetPageSize(size_t _size) 
    { 
        return  MemPage_t::SetCapacity(_size); 
    }
};





#endif /*__MEMPOOL_H__*/