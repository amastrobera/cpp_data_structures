// Red-Black Tree Set
// not thread safe

#ifndef SET_LIST_H
#define SET_LIST_H

#include "my_node.h"
#include "my_single_unsorted_list.h" //used as a Stack to delete nodes
#include "my_set.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <utility>

namespace my_data_structures 
{

unsigned const set_max_depth_imbalance = 2;

//Double linked list: the last and the first are linked in a circle
template<typename T> 
class Set
{
public:
    Set() : d_size(0), d_root(NULL) {}

    ~Set();

    inline unsigned size() { return d_size; }

    //adds a value at the top of the list
    void insert(T const& value);
    
    std::pair< RBNode<T>*, bool > find(T const& value);
    
    //todo: find, remove, first, last
    
private:
    unsigned d_size;
    RBNode<T>* d_root;

    unsigned depth(RBNode<T>* node);
    
    unsigned blackDepth(RBNode<T>* node);
    
    unsigned blackHeigth();
    
    void rebalance();
};


template<typename T> 
Set<T>::~Set()
{
    SingleUnsortedList< RBNode<T>* > stack;
    stack.insert(d_root);
    RBNode<T>* cur = stack.pop();
    while (stack.size() || cur)
    {
        if (cur->left) stack.insert(cur->left);
        if (cur->right) stack.insert(cur->right);
        delete cur;
        cur = NULL;
        --this->d_size;
        if(stack.size()) cur = stack.pop();
    }
}

template<typename T> 
void Set<T>::insert(T const& value)
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
        //if key exist already don't insert another one
        if (value == cur->value)
            found = true;
        else if (value > cur->value)
        {
            if (cur->right)
                cur = cur->right;
            else
            {
                cur->right = node;
                if (!cur->red) node->red = true;
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
                if (!cur->red) node->red = true;
                ++this->d_size;
                found = true;
            }
        }
    }
        
    if ((unsigned)
        abs(depth(d_root->left) - depth(d_root->right)) >
         set_max_depth_imbalance) 
    {
        rebalance();
    }
}


template<typename T>
std::pair< RBNode<T>*, bool > Set<T>::find(T const& value)
{
    //if empty list, return null
    if (!d_root)
        return std::pair< RBNode<T>*, bool >(NULL, false);
    
    //binary search, return false if nothing found
    RBNode<T>* cur = d_root;
    while (cur)
    {
        if (cur->value == value)
            return std::pair< RBNode<T>*, bool >(cur, true);
        else if (value < cur->value)
            cur = (cur->left) ? cur->left: NULL;
        else
            cur = (cur->right) ? cur->right: NULL;
    }
    return std::pair< RBNode<T>*, bool >(NULL, false);
}


template<typename T>
unsigned Set<T>::blackDepth(RBNode<T>* node)
{
    //count the number of black nodes from the root to node
    unsigned dep = 0;
    SingleUnsortedList< RBNode<T>* > queue;
    queue.append(d_root);
    RBNode<T>* cur = queue.pop();
    while (queue.size() || cur)
    {
        //count number of black nodes 
        if (!cur) ++dep;
        if (cur == node) break; //exit when you the running ptr finds node
        
        //append the next nodes to the queue\, if any
        if (cur->left) queue.append(cur->left);
        if (cur->right) queue.append(cur->right);

        //update the running ptr
        if(queue.size())
            cur = queue.pop();
        else
            cur = NULL;
    }
    return dep;
}
    
template<typename T>
unsigned Set<T>::blackHeigth()
{
    //count the number of black nodes from the root to node
    unsigned dep = 0;
    SingleUnsortedList< RBNode<T>* > queue;
    queue.append(d_root);
    RBNode<T>* cur = queue.pop();
    while (queue.size() || cur)
    {
        //count number of black nodes 
        if (!cur) ++dep;
        
        //append the next nodes to the queue\, if any
        if (cur->left) queue.append(cur->left);
        if (cur->right) queue.append(cur->right);

        //update the running ptr
        if(queue.size())
            cur = queue.pop();
        else
            cur = NULL;
    }
    return dep;
}

template<typename T>
unsigned Set<T>::depth(RBNode<T>* node)
{
    typedef std::pair< RBNode<T>*, unsigned> PairLevel;
    unsigned dep = 0;
    SingleUnsortedList< PairLevel > queue;
    queue.append( PairLevel(node, 0) );
    PairLevel cur = queue.pop();
    while (queue.size() || cur.first)
    {
        if (cur.second > dep) 
            ++dep;
        if (cur.first->left) 
            queue.append(PairLevel(cur.first->left, 
                                    cur.second+1));
        if (cur.first->right) 
            queue.append(PairLevel(cur.first->right, 
                                    cur.second+1));

        if(queue.size())
            cur = queue.pop();
        else
            cur = PairLevel(NULL, 0);
    }
    return dep;
}


template<typename T>
void Set<T>::rebalance()
{
    std::cout << "rebalancing " << std::endl;
}    


} //my_data_structures

#endif

