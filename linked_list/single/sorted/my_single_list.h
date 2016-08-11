// single sorted linked list
// not thread safe
// not exception safe yet

#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#include "my_single_unsorted_list.h"

#include <stdexcept>

namespace my_data_structures 
{

//Double linked list
template<typename T> 
class SingleList : public SingleUnsortedList<T>
{
public:
    SingleList() : SingleUnsortedList<T>() {}

    virtual ~SingleList() {}

    //adds a value at the bottom of the list
    virtual void append(T const& value) {}
    //adds a value at the top of the list
    virtual void insert(T const& value);
    
};

template<typename T> 
void SingleList<T>::insert(T const& value)
{
    //append on top of the list if no item or value < root
    if (!this->d_root ||
        value < this->d_root->value)
    {
        SingleNode<T>* node = new SingleNode<T>(value);
        node->next = this->d_root;
        this->d_root = node;
        ++this->d_size;
        return;
    }
    
    //append in sorted order inside the list
    SingleNode<T>* cur = this->d_root;
    while (cur->next && 
           value > cur->next->value) cur = cur->next;

    SingleNode<T>* node = new SingleNode<T>(value);
    if (cur->next) 
    {
        //append between node a and node b, with a < value < b
        node->next = cur->next;
        cur->next = node;
    }
    else
    {
        //append to the bottom of the list
        cur->next = node;
    }
    ++this->d_size;
}



} //my_data_structures

#endif
