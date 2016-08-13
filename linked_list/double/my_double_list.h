// double sorted linked list
// not thread safe

#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include "my_list.h"

#include <stdexcept>

namespace my_data_structures 
{

//Double linked list: the last and the first are linked in a circle
template<typename T> 
class DoubleList : public List<T>
{
public:
    DoubleList() : List<T>(), d_root(NULL) {}

    virtual ~DoubleList();

    //does the same as insert, because this is a sorted list 
    virtual void append(T const& value) { insert(value); }
    //adds a value at the top of the list
    virtual void insert(T const& value);
    
    //returns the item at the beginning
    virtual T& top();
    //returns the item at the end of the list
    virtual T& bottom();
    //returns the k-th item of the list; throws it out of range
    virtual T& at(unsigned const k);
    //returns the item ats the top of the list and deletes it
    virtual T pop();

    //deletes the first occurrence of a given value
    virtual void remove(T const& value);
    //adds a value at the bottom of the list
    virtual void removeAll(T const& value);
    
private:
    DoubleNode<T>* d_root;
    
};


template<typename T> 
DoubleList<T>::~DoubleList()
{
    DoubleNode<T>* cur = d_root;
    while (cur)
    {
        //removing link to the node to be deleted
        if (cur->left) cur->left->right = NULL; 
        //removing the node
        DoubleNode<T>* temp = cur;
        cur = cur->right;
        delete temp;
        --this->d_size;
    }
}

template<typename T> 
void DoubleList<T>::insert(T const& value)
{
    DoubleNode<T>* node = new DoubleNode<T>(value);
    //first node
    if (!d_root)
    { 
        d_root = node;
        d_root->right = d_root->left = d_root;
        ++this->d_size;
        return;
    }
    //second node
    if (d_root->left == d_root)
    {
        node->right = node->left = d_root;
        d_root->right = d_root->left = node;
        if (value < d_root->value) d_root = node;
        ++this->d_size;
        return;
    }
    
    //third+ : add it at the left of the root, and reset all links to/from it
    DoubleNode<T>* cur = d_root;
    while (cur != d_root->left &&
           value >= cur->value) cur = cur->right;
    if (value < cur->value)
    {
        node->right = cur;
        node->left = cur->left;
        cur->left = cur->left->right = node;
        if (cur == d_root) d_root = node;
    }
    else
    {
        node->left = cur;
        node->right = cur->right;
        cur->right = cur->right->left = node;
    }
    ++this->d_size; 
}


template<typename T> 
T& DoubleList<T>::top()
{
    if (this->d_size == 0) throw std::runtime_error("empty list");
    return d_root->value;
}

template<typename T> 
T& DoubleList<T>::bottom()
{
    if (this->d_size == 0) throw std::runtime_error("empty list");
    return (d_root->left) ? d_root->left->value : d_root->value;
}

template<typename T> 
T& DoubleList<T>::at(unsigned const k)
{
    if (k >= this->d_size) throw std::runtime_error("index out of range");
    DoubleNode<T>* cur = d_root;
    if (k < (unsigned int)this->d_size/2)
        for (unsigned i = 0; i < k; ++i) cur = cur->right;
    else 
        for (unsigned i = this->d_size; i > k; --i) cur = cur->left;
        
    return cur->value;
}

template<typename T> 
T DoubleList<T>::pop()
{
    if (this->d_size == 0) throw std::runtime_error("empty list");
    T val = d_root->value;
    DoubleNode<T>* tgt = d_root;
    if (this->d_size == 2)
    {//two nodes only
        d_root = d_root->left;
        delete tgt;
        d_root->left = d_root->right = d_root;
    }
    else if (this->d_size == 1)
    {//one node only
        d_root->left = d_root->right = NULL;
        delete tgt;
        d_root = NULL;
    }
    else
    {//more than two nodes 
        d_root->left->right = d_root->right;
        d_root->right->left = d_root->left;
        d_root = d_root->right;
        delete tgt;
    }
    --this->d_size;
    return val;
}


template<typename T> 
void DoubleList<T>::remove(T const& value)
{
    if (this->d_size == 0) throw std::runtime_error("empty list");
    
    DoubleNode<T>* cur = d_root;
    while (cur->value != value && 
           cur != d_root->left) cur = cur->right;
    
    if (cur->value == value)
    {
        cur->left->right = cur->right;
        cur->right->left = cur->left;

        if (cur == d_root) d_root = d_root->right;

        delete cur;
        --this->d_size;
    }

}

template<typename T> 
void DoubleList<T>::removeAll(T const& value)
{
    if (this->d_size == 0) throw std::runtime_error("empty list");
    
    //delete forward, from the second to the last
    DoubleNode<T>* cur = d_root;
    while (cur != d_root->left)
    {
        if (cur->value == value)
        {
            cur->left->right = cur->right;
            cur->right->left = cur->left;

            if (cur == d_root) d_root = d_root->right;

            delete cur;
            --this->d_size;
        }
        cur = cur->right;
    }
    
    //delete the last one, if it contains the target value
    if (cur->value == value)
    {
        cur->left->right = cur->right;
        cur->right->left = cur->left;

        delete cur;
        --this->d_size;
    }
}


} //my_data_structures

#endif
