#ifndef SHAREDPTR_H
#define SHAREDPTR_H

namespace Preparation
{


template<typename T>
class SharedPtr
{

SharedPtr(T*);
SharedPtr(const SharedPtr&);
~SharedPtr();
SharedPtr& operator=(const SharedPtr&);
T& operator*() const;
T* operator->() const;

private:
    T* ptr;
    int* counter;
};



template<typename T>
SharedPtr<T>::SharedPtr(T* p)
: ptr(p)
, counter(new int(1))
{

}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& shptr)
{
    if(*shptr.counter > 0)
    {
        ptr = shptr;
        counter = shptr.counter;
        ++*counter;
    }

}
template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& s)
{
    if(SharedPtr.*counter > 0)
    {
        ~SharedPtr();
        SharedPtr sh(s);
        
    }
    return *this;
}

template<typename T>
SharedPtr<T>::~SharedPtr()
{
    if(*counter < 2 && *counter > 0)
    {
        ~T();
    }
    --*counter;
}


}


#endif