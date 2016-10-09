// double sorted linked list
// not thread safe

#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include "my_list.h"

#include <limits> //c++11 library used to build sentinel node for end() iterator
                  //this could have been achieved with a substantial refactoring
                  //of the current code: CircularNode(right = left)
                  //and CircularDataNode(value, inherits CircularNode)
                  //and DoubleNode (right and left can be null)
                  // ... but I don't want to do it
#include <stdexcept>
#include <utility>

namespace my_data_structures 
{

//Double linked list: the last and the first are linked in a circle
template<typename T> 
class DoubleList : public List<T>
{
public:
    DoubleList();

    virtual ~DoubleList();

    //does the same as insert, because this is a sorted list 
    virtual void append(T const& value) { insert(value); }
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
    
    //returns pointer/found of the node with the value = value
    //deleting the returned pointer will compromise the who class structure
    std::pair< DoubleNode<T>*, bool > find(T const& value);

    //deletes the first occurrence of a given value
    virtual void remove(T const& value);
    //adds a value at the bottom of the list
    virtual void removeAll(T const& value);

    //iterators
    class iterator;
    
    virtual iterator begin() const { return iterator(d_end->right); }

    virtual iterator end() const { return iterator(d_end); }
    
private:

    DoubleNode<T>* d_root;
    
    DoubleNode<T>* d_end;
};


//iterators
template<typename T>
class DoubleList<T>::iterator : public List<T>::iterator
{
public:

    iterator() : List<T>::iterator(), d_node(NULL) {}
    
    iterator(DoubleNode<T>* node) : List<T>::iterator(&node->value),
                                    d_node(node) {}

protected:

    DoubleNode<T>* d_node;

    virtual void increment()
    {
        if (this->d_node)
        {   //change if the iterator has been initialised
            //once initialised the d_node can never be null, because the list is circular
            this->d_node = this->d_node->right;
            this->d_item = &this->d_node->value;
        }
    }
    
    void decrement()
    {   //same comment as above (increment)
        if (this->d_node)
        {
            this->d_node = this->d_node->left;
            this->d_item = &this->d_node->value;
        }
    }
    
};

template<typename T> 
DoubleList<T>::DoubleList() 
: List<T>(), d_root(NULL), d_end(new DoubleNode<T>(
                                    std::numeric_limits<T>::lowest())) 
{
    d_end->right = d_end->left = d_end;    
}

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
        d_root->right = d_root->left = d_end;
        d_end->right = d_end->left = d_root;
        ++this->d_size;
        return;
    }
    
    //second+ : add it at the left of the root, and reset all links to/from it
    DoubleNode<T>* cur = d_root;
    while (cur->right != d_end &&
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
T const& DoubleList<T>::top() const
{
    if (this->d_size == 0) throw std::runtime_error("empty list");
    return d_root->value;
}

template<typename T> 
T const& DoubleList<T>::bottom() const
{
    if (this->d_size == 0) throw std::runtime_error("empty list");
    return d_end->left->value;
}

template<typename T> 
T& DoubleList<T>::at(unsigned const k)
{
    if (k >= this->d_size) throw std::runtime_error("index out of range");
    DoubleNode<T>* cur = d_root;
    if (k < (unsigned int)this->d_size/2)
        for (unsigned i = 0; i < k; ++i) cur = cur->right;
    else 
        //consider also d_end
        for (unsigned i = this->d_size; i >= k; --i) cur = cur->left;
        
    return cur->value;
}

template<typename T> 
T DoubleList<T>::pop()
{
    if (this->d_size == 0) throw std::runtime_error("empty list");
    T val = d_root->value;
    DoubleNode<T>* tgt = d_root;
    if (this->d_size == 1)
    {//one node only
        d_root = NULL;
        d_end->left = d_end->right = d_end;
        delete tgt;
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
std::pair< DoubleNode<T>*, bool > DoubleList<T>::find(T const& value)
{
    //if empty list, return null
    if (!d_root)
        return std::pair< DoubleNode<T>*, bool >(NULL, false);
    
    //if it is the root, return it
    if (d_root->value == value)
        return std::pair< DoubleNode<T>*, bool >(d_root, true);

    //otherwise loop through the who list until you find the value
    //if you hit the root again, the value is not in the list
    DoubleNode<T>* cur = d_root->right;
    while (cur->right != d_end && cur->value < value) cur = cur->right;
    
    if (cur->value == value)
        return std::pair< DoubleNode<T>*, bool >(cur, true);
    else
        return std::pair< DoubleNode<T>*, bool >(NULL, false);
}
    

template<typename T> 
void DoubleList<T>::remove(T const& value)
{
    if (this->d_size == 0) throw std::runtime_error("empty list");
    
    DoubleNode<T>* cur = d_root;
    while (cur->right != d_end && 
            cur->value != value) cur = cur->right;
    
    if (cur->value == value)
    {
        if (this->d_size == 1)
        {
            d_root = NULL;
            d_end->left = d_end->right = d_end;
        }
        else
        {
            cur->left->right = cur->right;
            cur->right->left = cur->left;
            if (cur == d_root) d_root = d_root->right;
        }
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
    while (cur->right != d_end)
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
        if (this->d_size == 1)
        {
            d_root = NULL;
            d_end->left = d_end->right = d_end;
        }
        else
        {
            cur->left->right = cur->right;
            cur->right->left = cur->left;        
        }
        delete cur;
        --this->d_size;
    }
}


} //my_data_structures

#endif
