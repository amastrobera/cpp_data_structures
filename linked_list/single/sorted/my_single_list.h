// single sorted linked list
// not thread safe
// not exception safe yet

#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#include "my_single_unsorted_list.h"

#include <stdexcept>
#include <utility>

namespace my_data_structures 
{

//Single, sorted linked list
template<typename T> 
class SingleList : public SingleUnsortedList<T>
{
public:
    SingleList() : SingleUnsortedList<T>() {}

    virtual ~SingleList() {}

    //does the same as insert, because this is a sorted list 
    virtual void append(T const& value) { insert(value); }
    //adds a value, sorted
    virtual void insert(T const& value);

    //returns pointer/found of the node with the value = value
    //deleting the returned pointer will compromise the who class structure
    std::pair< SingleNode<T>*, bool > find(T const& value);
    
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

template<typename T>
std::pair< SingleNode<T>*, bool > SingleList<T>::find(T const& value)
{
    SingleNode<T>* cur = this->d_root;
    while (cur && cur->value < value) cur = cur->next;
    
    if (cur && cur->value == value)
        return std::pair< SingleNode<T>*, bool > (cur, true);
    else
        return std::pair< SingleNode<T>*, bool > (NULL, false);
}


} //my_data_structures

#endif
