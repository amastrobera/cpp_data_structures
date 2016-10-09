// single unsorted linked list (ideal to implement a Stack)
// not thread safe
// not exception safe yet

#ifndef SINGLE_UNSORTED_LINKED_LIST_H
#define SINGLE_UNSORTED_LINKED_LIST_H

#include "my_list.h"

#include <stdexcept>

namespace my_data_structures 
{

//Single linked list
template<typename T> 
class SingleUnsortedList : public List<T>
{
public:
    SingleUnsortedList() : List<T>(), d_root(NULL) {}

    virtual ~SingleUnsortedList();

    //adds a value at the bottom of the list
    virtual void append(T const& value);
    //adds a value at the top of the list
    virtual void insert(T const& value);
    
    //returns the item at the beginning
    virtual T const& top() const;
    //returns the item at the end of the list
    virtual T const& bottom() const;
    //returns the k-th item of the list; throws it out of range
    virtual T& at(unsigned const k);
    //returns the item ats the top of the list and deletes it
    virtual T pop();

    //deletes the first occurrence of a given value
    virtual void remove(T const& value);
    //adds a value at the bottom of the list
    virtual void removeAll(T const& value);
    
    //iterators
    class iterator;
    
    virtual iterator begin() const { return iterator(d_root); }

    virtual iterator end() const { return iterator(); } //NULL = end of list
    
protected:

    SingleNode<T>* d_root;
    
};


//iterators
template<typename T>
class SingleUnsortedList<T>::iterator : public List<T>::iterator
{
public:

    iterator() : List<T>::iterator(), d_node(NULL) {}
    
    iterator(SingleNode<T>* node) : List<T>::iterator(&node->value),
                                    d_node(node) {}

protected:

    SingleNode<T>* d_node;

    virtual void increment()
    {
        if (this->d_node)
        {
            this->d_node = this->d_node->next;
            if (this->d_node)
                this->d_item = &this->d_node->value;
            else
                this->d_item = NULL;
        }
    }
    
};


template<typename T>
SingleUnsortedList<T>::~SingleUnsortedList()
{
    SingleNode<T>* cur = d_root;
    while (cur)
    {
        SingleNode<T>* temp = cur;
        cur = cur->next;
        delete temp;
        --this->d_size;
    }
}

template<typename T> 
void SingleUnsortedList<T>::append(T const& value)
{
    if (!d_root)
    {
        d_root = new SingleNode<T>(value);
        ++this->d_size;
        return;
    }
    SingleNode<T>* cur = d_root;
    while (cur->next) cur = cur->next;
    cur->next = new SingleNode<T>(value);    
    ++this->d_size;
}

template<typename T> 
void SingleUnsortedList<T>::insert(T const& value)
{
    SingleNode<T>* node = new SingleNode<T>(value);
    node->next = d_root;
    d_root = node;
    ++this->d_size;
}

template<typename T> 
T const& SingleUnsortedList<T>::top() const
{
    if (this->d_size == 0) throw std::runtime_error("empty list");
    return d_root->value;
}

template<typename T> 
T const& SingleUnsortedList<T>::bottom() const
{
    if (this->d_size == 0) throw std::runtime_error("empty list");
    SingleNode<T>* cur = d_root;
    while (cur->next) cur = cur->next;    
    return cur->value;
}

template<typename T> 
T& SingleUnsortedList<T>::at(unsigned const k)
{
    if (this->d_size <= k) throw std::runtime_error("out of range");
    SingleNode<T>* cur = d_root;
    for (unsigned i = 0; i < k; ++i) cur = cur->next;
    return cur->value;
}

template<typename T> 
T SingleUnsortedList<T>::pop()
{
    if (this->d_size == 0) throw std::runtime_error("empty list");
    T retVal = d_root->value;
    
    SingleNode<T>* cur = d_root;
    d_root = d_root->next;    
    delete cur;
    --this->d_size;
    return retVal;
}


template<typename T> 
void SingleUnsortedList<T>::remove(T const& value)
{
    if (this->d_size == 0) throw std::runtime_error("empty list");
    
    if (d_root->value == value)
    {
        SingleNode<T>* cur = d_root;
        d_root = d_root->next;
        delete cur;
        --this->d_size;
        return;
    }
    
    SingleNode<T>* cur = d_root;
    while (cur->next && 
           cur->next->value != value) cur = cur->next;
    if (cur->next && 
        cur->next->value == value)
    {
        SingleNode<T>* tgt = cur->next;
        cur->next = cur->next->next;    
        delete tgt;
        --this->d_size;    
    }
}

template<typename T> 
void SingleUnsortedList<T>::removeAll(T const& value)
{
    if (this->d_size == 0) throw std::runtime_error("empty list");
    
    //delete forward, from the second to the last
    SingleNode<T>* cur = d_root;
    while (cur->next)
    {
        if (cur->next->value == value)
        {
            SingleNode<T>* tgt = cur->next;
            cur->next = cur->next->next;    
            delete tgt;
            --this->d_size;
        }
        cur = cur->next;
    }
    
    //delete the first, if its value is the target one
    if (d_root && 
        d_root->value == value)
    {
        SingleNode<T>* cur = d_root;
        d_root = d_root->next;
        delete cur;
        --this->d_size;
    }
}

} //my_data_structures

#endif
