// linked list interface

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "my_node.h"

namespace my_data_structures 
{

//List Interface
//it allows simple types only; for classes specify the operator==
//insertions are un-sorted
template<typename T> 
class List
{
public:
    List() : d_size(0) {}

    virtual ~List() {};

    //how many items are in the list
    inline unsigned size() const {return d_size;}

    //adds a value at the bottom of the list
    virtual void append(T const& value) = 0;
    //adds a value at the top of the list
    virtual void insert(T const& value) = 0;
    
    //returns the item at the beginning
    virtual T& top() = 0;
    //returns the item at the end of the list
    virtual T& bottom() = 0;
    //returns the k-th item of the list; throws it out of range
    virtual T& at(unsigned const k) = 0;
    //returns the item ats the top of the list and deletes it
    virtual T pop() = 0;

    //deletes the first occurrence of a given value
    virtual void remove(T const& value) = 0;
    //adds a value at the bottom of the list
    virtual void removeAll(T const& value) = 0;
    
protected:
    unsigned d_size;
};


} //my_data_structures

#endif
