// iterator interface

#ifndef NULL
#define NULL 0
#endif

#ifndef ITERATOR_H
#define ITERATOR_H

#include "my_iterator.h"

namespace my_data_structures 
{

//Iterator Interface
//basic functions to be specialised inside each data structure it is used in
template<typename T> 
class Iterator
{
public:
    Iterator() : d_item(NULL) {}
    Iterator(Iterator const& it) : d_item(it.d_item) {}
    Iterator(T* val) : d_item(val) {}
    virtual ~Iterator() {};

    //advances and retreats: to be specialised in each data structure class
    Iterator<T>& operator++();                                  //++it
    Iterator<T>& operator++(int unused) { return operator++();} //it++
    
    Iterator<T>& operator--();
    Iterator<T>& operator--(int unused) { return operator--();}
    
    //dereferences and returns the object pointed to
    T& operator*() { return *d_item; }
    T& operator->() { return operator*(); }

    //assignment
    Iterator& operator= (Iterator const& it);
    
    //comparison operators
    bool operator==(Iterator const& rhs);
    bool operator!=(Iterator const& rhs) {return !operator==(rhs);}

protected:
    T* d_item;
    
    virtual void increment() = 0;
    
    //implementable for all structure except forward list (single list)
    virtual void decrement() = 0; 
};


template<typename T>
Iterator<T>& Iterator<T>::operator=(Iterator<T> const& it)
{
    if (this != &it)
        d_item = it.d_item;
    return *this;
}

template<typename T>
Iterator<T>& Iterator<T>::operator++()
{
    increment();
    return *this;
}

template<typename T>
Iterator<T>& Iterator<T>::operator--()
{
    decrement();
    return *this;
}

template<typename T>
bool Iterator<T>::operator==(Iterator<T> const& rhs)
{
    return this->d_item == rhs.d_item;
}


} //my_data_structures

#endif
