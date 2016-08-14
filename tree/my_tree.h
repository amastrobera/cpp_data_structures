// Red-Black Tree
// not thread safe

#ifndef RB_TREE_LIST_H
#define RB_TREE_LIST_H

#include "my_node.h"
#include "my_single_unsorted_list.h" //used as a Stack to delete nodes
#include "my_tree.h"

#include <cstdlib>
#include <stdexcept>
#include <utility>

namespace my_data_structures 
{

unsigned const tree_max_depth_imbalance = 2;

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

    unsigned depth(RBNode<T>* node);
    
    void rebalance();
};


template<typename T> 
Tree<T>::~Tree()
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
        
    if ((unsigned)
        abs(depth(d_root->left) - depth(d_root->right)) >
         tree_max_depth_imbalance) 
    {
        rebalance();
    }
}

template<typename T>
unsigned Tree<T>::depth(RBNode<T>* node)
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
void Tree<T>::rebalance()
{

}    


} //my_data_structures

#endif

