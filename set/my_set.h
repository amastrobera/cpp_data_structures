// Red-Black Tree Set
// not thread safe

#ifndef SET_LIST_H
#define SET_LIST_H

#include "my_node.h"
#include "my_single_unsorted_list.h" //used as a Stack/Queue for DFS or BFS
#include "my_set.h"

#include <cmath>
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
    
    //todo: return a proper iterator, once the iterator class is ready
    RBNode<T>* first();
    
    RBNode<T>* last();

    //todo: remove function
    
    //temporary test functions, make friend to private test methods
    void print();
    bool isBalanced() { return (d_size <= 3 ) ? true : 
            std::abs(depth(d_root->left) - depth(d_root->right)) < 2;
                        }
    
private:
    unsigned d_size;
    
    RBNode<T>* d_root;

    //todo: what to do with those measures ?
    //max number of levels from node, downwards
    unsigned depth(RBNode<T>* node);
    //number of black nodes from root to node
    unsigned blackDepth(RBNode<T>* node);
    //number of black nodes in the tree
    unsigned blackHeigth();
    
    //rebalancing function for insertion
    void insertRebalance(RBNode<T>*& greatGrandParentNode,
                         RBNode<T>*& grandParentNode, 
                         RBNode<T>* parentNode, 
                         RBNode<T>* uncleNode, 
                         RBNode<T>* childNode);

    unsigned insertRebalanceCase(RBNode<T>* grandParentNode,
                                 RBNode<T>* parentNode, 
                                 RBNode<T>* uncleNode, 
                                 RBNode<T>* childNode) const;

    void recolourNodes(RBNode<T>*& grandParentNode);

    void leftStraigthLine(RBNode<T>*& grandParentNode);
    
    void rightStraigthLine(RBNode<T>*& grandParentNode);
    
    void leftRotate(RBNode<T>*& greatGrandParentNode, 
                    RBNode<T>*& grandParentNode);
   
    void rightRotate(RBNode<T>*& greatGrandParentNode, 
                     RBNode<T>*& grandParentNode);
                     
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
        --d_size;
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
        ++d_size;
        return;
    }

    //second+ node: find the append point by comparing (ASC) existing nodes
    RBNode<T>* greatGrandParentNode = NULL;
    RBNode<T>* grandParentNode = NULL;
    RBNode<T>* parentNode = d_root;
    RBNode<T>* uncleNode = NULL;
    bool found = false;
    while (!found)
    {
        if (value == parentNode->value)
        {
            //if key exist already don't insert another one
            return;
        }
        else if (value > parentNode->value)
        { //to the right
            if (parentNode->right)
            { // move fwd
                greatGrandParentNode = grandParentNode;
                grandParentNode = parentNode;
                uncleNode = parentNode->left;
                parentNode = parentNode->right;
            }
            else
            { // add node to the right side and rebalance
                node->red = true;
                parentNode->right = node;
                ++d_size;
                insertRebalance(greatGrandParentNode,
                                grandParentNode, 
                                parentNode, 
                                uncleNode, 
                                parentNode->right);
                found = true;
            }
        }
        else
        { //to the left 
            if (parentNode->left)
            { // move fwd
                greatGrandParentNode = grandParentNode;
                grandParentNode = parentNode;
                uncleNode = parentNode->right;
                parentNode = parentNode->left;
            }
            else
            { //add node on the left side and rebalance
                node->red = true;
                parentNode->left = node;
                ++d_size;
                insertRebalance(greatGrandParentNode, 
                                grandParentNode, 
                                parentNode, 
                                uncleNode, 
                                parentNode->left);
                found = true;
            }
        }
    }
}

template<typename T>
void Set<T>::insertRebalance(RBNode<T>*& greatGrandParentNode,
                             RBNode<T>*& grandParentNode,
                             RBNode<T>* parentNode,
                             RBNode<T>* uncleNode,
                             RBNode<T>* childNode)
{
    switch (insertRebalanceCase(grandParentNode, 
                                  parentNode, 
                                  uncleNode, 
                                  childNode))
    {
        case 0: //nothing to rebalance
            break;

        case 1: //colour nodes
            recolourNodes(grandParentNode);
            break;

        case 2: //make it a case 3 and manage it
            if (parentNode == grandParentNode->left &&
                            childNode == parentNode->right)
                leftStraigthLine(grandParentNode);
            else
                rightStraigthLine(grandParentNode);
            //fallthrough case 3
            
        case 3: //rotate
            if (parentNode == grandParentNode->left &&
                            childNode == parentNode->left)
                rightRotate(greatGrandParentNode, 
                            grandParentNode);
            else
                leftRotate(greatGrandParentNode, 
                           grandParentNode);
            break;
    }
}    

template<typename T>
unsigned Set<T>::insertRebalanceCase(RBNode<T>* grandParentNode,
                                     RBNode<T>* parentNode,
                                     RBNode<T>* uncleNode,
                                     RBNode<T>* childNode) const
{
    if (grandParentNode && !grandParentNode->red)
    {
        if ((uncleNode && uncleNode->red) && 
                parentNode->red && childNode->red)
        {
            return 1;
        }
        else if ((!uncleNode || !uncleNode->red) && 
                                parentNode->red && childNode->red &&
                 ((parentNode == grandParentNode->left &&
                                childNode == parentNode->right) ||
                  (parentNode == grandParentNode->right &&
                                childNode == parentNode->left)) )
        {
            return 2;
        }
        else if ((parentNode->red && childNode->red) &&
                 ((parentNode == grandParentNode->left &&
                                childNode == parentNode->left) ||
                  (parentNode == grandParentNode->right &&
                                childNode == parentNode->right)))
        {
            return 3;
        }
    }

    return 0;
}


template<typename T>
void Set<T>::recolourNodes(RBNode<T>*& grandParentNode)
{
    //set parent and uncle nodes black, grandparent red
    if (grandParentNode->left) grandParentNode->left->red = false;
    if (grandParentNode->right) grandParentNode->right->red = false;
    if (grandParentNode != d_root) grandParentNode->red = true;
}

template<typename T>
void Set<T>::leftStraigthLine(RBNode<T>*& grandParentNode)
{
    //make a straight line to the left
    RBNode<T>* parentNode = grandParentNode->left;
    RBNode<T>* childNode = grandParentNode->left->right;
    grandParentNode->left = childNode;
    childNode->left = parentNode;
    parentNode->right = NULL;
    
    //swap parent and child
    RBNode<T>* temp;
    temp = parentNode;
    parentNode = childNode;
    childNode = temp;
}

template<typename T>
void Set<T>::rightStraigthLine(RBNode<T>*& grandParentNode)
{
    //make a straight line to the right
    RBNode<T>* parentNode = grandParentNode->right;
    RBNode<T>* childNode = grandParentNode->right->left;
    grandParentNode->right = childNode;
    childNode->right = parentNode;
    parentNode->left = NULL;
    
    //swap parent and child
    RBNode<T>* temp;
    temp = parentNode;
    parentNode = childNode;
    childNode = temp;
}


template<typename T>
void Set<T>::leftRotate(RBNode<T>*& greatGrandParentNode, 
                        RBNode<T>*& grandParentNode)
{
    //rotation
    RBNode<T>* parentNode = grandParentNode->right;
    grandParentNode->right = parentNode->left;
    parentNode->left = grandParentNode;
    //swap
    grandParentNode = parentNode;
    //colour change
    grandParentNode->red = false;
    grandParentNode->left->red = grandParentNode->right->red = true;
    if (grandParentNode->left->left) 
        grandParentNode->left->left->red = false;
    //attach new node to the original tree
    if (greatGrandParentNode)
        greatGrandParentNode->right = grandParentNode;
    else if (d_size == 3)
        d_root = grandParentNode;
}

template<typename T>
void Set<T>::rightRotate(RBNode<T>*& greatGrandParentNode, 
                         RBNode<T>*& grandParentNode)
{
    //rotation
    RBNode<T>* parentNode = grandParentNode->left;
    grandParentNode->left = parentNode->right;
    parentNode->right = grandParentNode;
    //swap
    grandParentNode = parentNode;
    //colour change
    grandParentNode->red = false;
    grandParentNode->left->red = grandParentNode->right->red = true;
    if (grandParentNode->right->right)
        grandParentNode->right->right->red = false;
    //attach new node to the original tree
    if (greatGrandParentNode)
        greatGrandParentNode->left = grandParentNode;
    else if (d_size == 3)
        d_root = grandParentNode;
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
RBNode<T>* Set<T>::first()
{
    RBNode<T>* cur = d_root;
    while (cur->left) cur = cur->left;
    return cur;
}

template<typename T>
RBNode<T>* Set<T>::last()
{
    RBNode<T>* cur = d_root;
    while (cur->right) cur = cur->right;
    return cur;
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
        if (!cur->red) ++dep;
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
        if (!cur->red) ++dep;
        
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
void Set<T>::print()
{
    SingleUnsortedList< std::pair<RBNode<T>* , unsigned> > queue;
    std::pair<RBNode<T>* , unsigned> cur(d_root, 0);
    unsigned level = 0;
    while (queue.size() || cur.first)
    {
        if (level < cur.second)
        {
            std::cout << std::endl;
            ++level;
        }
        std::cout << cur.first->value
                  << "(" << ( (cur.first->red)? "r":"b") << ")";
        if (cur.first->left && cur.first->right)
            std::cout << "(2)" ;
        else if ((cur.first->left && !cur.first->right) ||
                 (!cur.first->left && cur.first->right))
            std::cout << "(1)" ;
        else
            std::cout << "(0)" ;
        std::cout << "  ";

        if (cur.first->left)
            queue.append(std::pair<RBNode<T>* , unsigned>
                            (cur.first->left, level+1));
        if (cur.first->right)
            queue.append(std::pair<RBNode<T>* , unsigned>
                            (cur.first->right, level+1));

        if (queue.size() > 0)
            cur = queue.pop();
        else
            cur = std::pair<RBNode<T>* , unsigned>(NULL, 0);
    }
    std::cout << std::endl;
}


} //my_data_structures

#endif

