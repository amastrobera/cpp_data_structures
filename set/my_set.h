// Red-Black Tree Set
// not thread safe

#ifndef SET_H
#define SET_H

#include "my_node.h"
#include "my_single_unsorted_list.h" //used as a Stack/Queue for DFS or BFS

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

    //inserts into the tree, sorted and rebalanced properly 
    std::pair< RBNode<T>*, bool> insert(T const& value);
    
    std::pair< RBNode<T>*, bool > find(T const& value);
    
    //todo: return a proper iterator, once the iterator class is ready
    RBNode<T>* first();
    
    RBNode<T>* last();

    //todo: remove function
    
    //temporary test functions, make friend to private test methods
    void print();
    bool isBalanced() { return (d_size <= 3 ) ? true : 
            std::abs((int)maxDepth(d_root->left) - 
                        (int)maxDepth(d_root->right)) < 2;}
    
private:
    unsigned d_size;
    
    RBNode<T>* d_root;

    //todo: what to do with those measures ?
    //max number of levels from node, downwards
    unsigned maxDepth(RBNode<T>* node);
    //number of black nodes from root to node
    unsigned blackDepth(RBNode<T>* node);
    //number of black nodes in the tree
    unsigned blackHeigth();
    
    //rebalancing function for insertion
    bool insertRebalance(
                    RBNode<T>*& childNode);

    unsigned insertRebalanceCase(
                    RBNode<T>* grandParentNode,
                    RBNode<T>* parentNode, 
                    RBNode<T>* uncleNode, 
                    RBNode<T>* childNode) const;

    void recolourNodes(
                    RBNode<T>*& grandParentNode,
                    RBNode<T>*& parentNode, 
                    RBNode<T>*& uncleNode);

    void leftStraigthLine(
                    RBNode<T>*& grandParentNode,
                    RBNode<T>*& parentNode, 
                    RBNode<T>*& childNode);
    
    void rightStraigthLine(
                    RBNode<T>*& grandParentNode,
                    RBNode<T>*& parentNode, 
                    RBNode<T>*& childNode);
    
    void leftRotate(
                    RBNode<T>*& grandParentNode,
                    RBNode<T>*& parentNode);
   
    void rightRotate(
                    RBNode<T>*& grandParentNode,
                    RBNode<T>*& parentNode);

                     
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
std::pair< RBNode<T>*, bool> Set<T>::insert(T const& value)
{
    RBNode<T>* node = new RBNode<T>(value);

    //first node
    if (!d_root) 
    {
        d_root = node;
        ++d_size;
        return std::pair< RBNode<T>*, bool>(node, true);
    }

    //second+ node: find the append point by comparing (ASC) existing nodes
    RBNode<T>* parentNode = d_root;
    bool found = false;
    while (!found)
    {
        if (value == parentNode->value)
        {
            //if key exist already don't insert another one
            return std::pair< RBNode<T>*, bool>(NULL, false);
        }
        else if (value > parentNode->value)
        { //to the right
            if (parentNode->right) // move fwd
                parentNode = parentNode->right;
            else
            { // add node to the right side and rebalance
                node->red = true;
                parentNode->right = node;
                node->parent = parentNode;
                ++d_size;
                found = true;
            }
        }
        else
        { //to the left 
            if (parentNode->left) // move fwd
                parentNode = parentNode->left;
            else
            { //add node on the left side and rebalance
                node->red = true;
                parentNode->left = node;
                node->parent = parentNode;
                ++d_size;
                found = true;
            }
        }
    }
    
    RBNode<T>* rebalanceNode = node;
    while (!insertRebalance(rebalanceNode) && rebalanceNode) 
            rebalanceNode = (rebalanceNode->parent && 
                             rebalanceNode->parent->parent) ? 
                             rebalanceNode->parent->parent : NULL;
    
    return std::pair< RBNode<T>*, bool>(node, true);
}

template<typename T>
bool Set<T>::insertRebalance(RBNode<T>*& childNode)
{
    RBNode<T>* parentNode = 
                (childNode->parent) ? childNode->parent : NULL;

    RBNode<T>* grandParentNode = 
                (parentNode && parentNode->parent) ? parentNode->parent : NULL;

    RBNode<T>* uncleNode = 
                (grandParentNode) ? 
                    ( (grandParentNode->left == parentNode) ? 
                        grandParentNode->right: grandParentNode->left ) : 
                NULL;

    switch (insertRebalanceCase(grandParentNode, 
                                parentNode, 
                                uncleNode, 
                                childNode))
    {
        case 0: //nothing to rebalance
            return true;
            break;//warning safeguard

        case 1: //colour nodes
            recolourNodes(grandParentNode, parentNode, uncleNode);
            break;

        case 2: //make it a case 3 and manage it
            if (parentNode == grandParentNode->left &&
                            childNode == parentNode->right)
                leftStraigthLine(grandParentNode, parentNode, childNode);
            else
                rightStraigthLine(grandParentNode, parentNode, childNode);
            //fallthrough case 3
            
        case 3: //rotate
            if (parentNode == grandParentNode->left &&
                            childNode == parentNode->left)
                rightRotate(grandParentNode, parentNode);
            else
                leftRotate(grandParentNode, parentNode);
            break;
    }
    // in cases 1 and 3, check if the tree is balanced: 
    //return false, if there is a violation of type "red parent, red child"
    if (grandParentNode && grandParentNode->parent && 
                            grandParentNode->parent->red)
        return false;
    else
        return true;
}    

template<typename T>
unsigned Set<T>::insertRebalanceCase(
                        RBNode<T>* grandParentNode,
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
void Set<T>::recolourNodes(
                    RBNode<T>*& grandParentNode,
                    RBNode<T>*& parentNode, 
                    RBNode<T>*& uncleNode)
{
    //set parent and uncle nodes black, grandparent red
    parentNode->red = uncleNode->red = false;
    if (grandParentNode != d_root) grandParentNode->red = true;
}

template<typename T>
void Set<T>::leftStraigthLine(
                    RBNode<T>*& grandParentNode,
                    RBNode<T>*& parentNode, 
                    RBNode<T>*& childNode)
{
    grandParentNode->left = childNode;

    RBNode<T>* grandChildNode = childNode->right;
    childNode->parent = grandParentNode;
    childNode->left = parentNode;
    childNode->right = NULL;
    
    parentNode->right = grandChildNode;
    parentNode->parent = childNode;
    
    //swap parent and child 
    RBNode<T>* swapNode;
    swapNode = parentNode;
    parentNode = childNode;
    childNode = swapNode;
}

template<typename T>
void Set<T>::rightStraigthLine(
                    RBNode<T>*& grandParentNode,
                    RBNode<T>*& parentNode, 
                    RBNode<T>*& childNode)
{
    grandParentNode->right = childNode;

    RBNode<T>* grandChildNode = childNode->left;
    childNode->parent = grandParentNode;
    childNode->right = parentNode;
    childNode->left = NULL;
    
    parentNode->left = grandChildNode;
    parentNode->parent = childNode;
    
    //swap parent and child 
    RBNode<T>* swapNode;
    swapNode = parentNode;
    parentNode = childNode;
    childNode = swapNode;
}

template<typename T>
void Set<T>::leftRotate(
                        RBNode<T>*& grandParentNode,
                        RBNode<T>*& parentNode)
{
    RBNode<T>* greatGrandParentNode = grandParentNode->parent;
    
    grandParentNode->parent = parentNode;
    grandParentNode->right = parentNode->left;
    grandParentNode->red = true;

    parentNode->parent = greatGrandParentNode;
    parentNode->left = grandParentNode;
    parentNode->red = false;

    if (grandParentNode == d_root)
        d_root = parentNode;
    else
    {
        if (greatGrandParentNode->left == grandParentNode)
            greatGrandParentNode->left = parentNode;
        else
            greatGrandParentNode->right = parentNode;
    }
}

template<typename T>
void Set<T>::rightRotate(
                        RBNode<T>*& grandParentNode, 
                        RBNode<T>*& parentNode)
{
    RBNode<T>* greatGrandParentNode = grandParentNode->parent;

    grandParentNode->parent = parentNode;
    grandParentNode->left = parentNode->right;
    grandParentNode->red = true;

    parentNode->parent = greatGrandParentNode;
    parentNode->right = grandParentNode;
    parentNode->red = false;

    if (grandParentNode == d_root)
        d_root = parentNode;
    else
    {
        if (greatGrandParentNode->left == grandParentNode)
            greatGrandParentNode->left = parentNode;
        else
            greatGrandParentNode->right = parentNode;
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
//    //count the number of black nodes from the root to node
//    unsigned dep = 0;
//    SingleUnsortedList< RBNode<T>* > queue;
//    queue.append(d_root);
//    RBNode<T>* cur = queue.pop();
//    while (queue.size() || cur)
//    {
//        //count number of black nodes 
//        if (!cur->red) ++dep;
//        if (cur == node) break; //exit when you the running ptr finds node
//        
//        //append the next nodes to the queue\, if any
//        if (cur->left) queue.append(cur->left);
//        if (cur->right) queue.append(cur->right);

//        //update the running ptr
//        if(queue.size())
//            cur = queue.pop();
//        else
//            cur = NULL;
//    }
//    return dep;
return 0;
}
    
template<typename T>
unsigned Set<T>::blackHeigth()
{
//    //count the number of black nodes from the root to node
//    unsigned dep = 0;
//    SingleUnsortedList< RBNode<T>* > queue;
//    queue.append(d_root);
//    RBNode<T>* cur = queue.pop();
//    while (queue.size() || cur)
//    {
//        //count number of black nodes 
//        if (!cur->red) ++dep;
//        
//        //append the next nodes to the queue\, if any
//        if (cur->left) queue.append(cur->left);
//        if (cur->right) queue.append(cur->right);

//        //update the running ptr
//        if(queue.size())
//            cur = queue.pop();
//        else
//            cur = NULL;
//    }
//    return dep;
return 0;
}

template<typename T>
unsigned Set<T>::maxDepth(RBNode<T>* node)
{
    typedef std::pair< RBNode<T>*, unsigned> PairLevel;
    unsigned dep = 0;
    SingleUnsortedList< PairLevel > queue;
    queue.append( PairLevel(node, 1) );
    PairLevel cur;
    while (queue.size())
    {
        cur = queue.pop();
            
        if (cur.second > dep)
            ++dep;
        if (cur.first->left) 
            queue.append(PairLevel(cur.first->left, 
                                    cur.second+1));
        if (cur.first->right) 
            queue.append(PairLevel(cur.first->right, 
                                    cur.second+1));
    }
    return dep;
}


template<typename T>
void Set<T>::print()
{
    SingleUnsortedList< std::pair<RBNode<T>*, unsigned> > queue;
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
            std::cout << "(LR)" ;
        else if (cur.first->left && !cur.first->right) 
            std::cout << "(L)" ;
        else if (!cur.first->left && cur.first->right)
            std::cout << "(R)" ;
        else
            std::cout << "(-)" ;
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

