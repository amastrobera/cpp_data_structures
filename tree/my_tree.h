// Red-Black Tree
// not thread safe

#ifndef RB_TREE_LIST_H
#define RB_TREE_LIST_H

#include "my_node.h"
#include "my_single_unsorted_list.h" //used as a Stack to delete nodes
#include "my_tree.h"

#include <stdexcept>

namespace my_data_structures 
{

//Double linked list: the last and the first are linked in a circle
template<typename T> 
class Tree
{
public:
    Tree() : d_size(0), d_root(NULL) {}

    ~Tree();

    inline unsigned size() { return d_size; }

    //adds a value at the top of the list
    void insert(T const& value);
    
    //todo: find, remove, first, last
    
private:
    unsigned d_size;
    RBNode<T>* d_root;
    //todo: rebalance()
};


template<typename T> 
Tree<T>::~Tree()
{
    SingleUnsortedList< RBNode<T>* > stack;
    stack.append(d_root);
    RBNode<T>* cur = stack.pop();
    while (stack.size() || cur)
    {
        if (cur->left) stack.append(cur->left);
        if (cur->right) stack.append(cur->right);
        delete cur;
        cur = NULL;
        --this->d_size;
        if(stack.size()) cur = stack.pop();
    }
}

template<typename T> 
void Tree<T>::insert(T const& value)
{
    RBNode<T>* node = new RBNode<T>(value);
    //first node
    if (!d_root) 
    {
        d_root = node;
        ++this->d_size;
        return;
    }
    //second+ node: find the append point by comparing (ASC) existing nodes
    RBNode<T>* cur = d_root;
    bool found = false;
    while (!found)
    {
        if (value == cur->value)
            found = true;
        else if (value > cur->value)
        {
            if (cur->right)
                cur = cur->right;
            else
            {
                cur->right = node;
                ++this->d_size;
                found = true;
            }
        }
        else
        {
            if (cur->left)
                cur = cur->left;
            else
            {
                cur->left = node;
                ++this->d_size;
                found = true;
            }
        }
    }
}



} //my_data_structures

#endif

