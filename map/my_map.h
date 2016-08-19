// Red-Black Tree Map
// not thread safe

#ifndef MAP_H
#define MAP_H

#include "my_node.h"
#include "my_single_unsorted_list.h" //used as a Stack/Queue for DFS or BFS

#include <cmath>
#include <limits>
#include <iostream>
#include <stdexcept>
#include <utility>

namespace my_data_structures 
{

unsigned const map_max_maxDepth_imbalance = 2;

//Double linked list: the last and the first are linked in a circle
template<typename K, typename V>
class Map
{
public:
    Map() : d_size(0), d_root(NULL) {}

    ~Map();

    inline unsigned size() { return d_size; }

    //inserts a value in the tree given key, sorts and rebalances tree
    std::pair< RBNode< std::pair<K,V> >*, bool> insert(
                    std::pair<K, V> const& key);
    
    //returns the item corresponding to key, or it inserts it and returns it
    V& operator[](K const& key);
    
    //returns the item corresponding to key, or throws 
    V& at(K const& key);
    
    std::pair< RBNode< std::pair<K,V> >*, bool> find(K const& key);
    
    //todo: return a proper iterator, once the iterator class is ready
    RBNode< std::pair<K,V> >* first();
    
    RBNode< std::pair<K,V> >* last();

    //todo: remove function
    
    //temporary test functions, make friend to private test methods
    void print();
    bool isBalanced() { return (d_size <= 3 ) ? true : 
            std::abs((int)maxDepth(d_root->left) - 
                        (int)maxDepth(d_root->right)) < 2;}
    
private:
    unsigned d_size;
    
    RBNode< std::pair<K,V> >* d_root;

    //todo: what to do with those measures ?
    //max number of levels from node, downwards
    unsigned maxDepth(
                    RBNode< std::pair<K,V> >* node);
    //number of black nodes from root to node
    unsigned blackDepth(
                    RBNode< std::pair<K,V> >* node);
    //number of black nodes in the tree
    unsigned blackHeigth();
    
    //rebalancing function for insertion
    bool insertRebalance(
                    RBNode< std::pair<K,V> >*& childNode);

    unsigned insertRebalanceCase(
                    RBNode< std::pair<K,V> >* grandParentNode,
                    RBNode< std::pair<K,V> >* parentNode, 
                    RBNode< std::pair<K,V> >* uncleNode, 
                    RBNode< std::pair<K,V> >* childNode) const;

    void recolourNodes(
                    RBNode< std::pair<K,V> >*& grandParentNode,
                    RBNode< std::pair<K,V> >*& parentNode, 
                    RBNode< std::pair<K,V> >*& uncleNode);

    void leftStraigthLine(
                    RBNode< std::pair<K,V> >*& grandParentNode,
                    RBNode< std::pair<K,V> >*& parentNode, 
                    RBNode< std::pair<K,V> >*& childNode);
    
    void rightStraigthLine(
                    RBNode< std::pair<K,V> >*& grandParentNode,
                    RBNode< std::pair<K,V> >*& parentNode, 
                    RBNode< std::pair<K,V> >*& childNode);
    
    void leftRotate(
                    RBNode< std::pair<K,V> >*& grandParentNode,
                    RBNode< std::pair<K,V> >*& parentNode);
   
    void rightRotate(
                    RBNode< std::pair<K,V> >*& grandParentNode,
                    RBNode< std::pair<K,V> >*& parentNode);
                     
};


template<typename K, typename V> 
Map<K,V>::~Map()
{
    SingleUnsortedList< RBNode< std::pair<K,V> >* > stack;
    stack.insert(d_root);
    RBNode< std::pair<K,V> >* cur = stack.pop();
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

template<typename K, typename V> 
std::pair< RBNode< std::pair<K,V> >*, bool> Map<K,V>::insert(
                    std::pair<K, V> const& value)
{
    RBNode< std::pair<K,V> >* node = new RBNode< std::pair<K,V> >(value);

    //first node
    if (!d_root) 
    {
        d_root = node;
        ++d_size;
        return std::pair< RBNode< std::pair<K,V> >*, bool>(node, true);
    }

    //second+ node: find the append point by comparing (ASC) existing nodes
    RBNode< std::pair<K,V> >* parentNode = d_root;
    bool found = false;
    while (!found)
    {
        if (value.first == parentNode->value.first)
        {
            //if key exist already don't insert another one
            return std::pair< RBNode< std::pair<K,V> >*, bool>(NULL, false);
        }
        else if (value.first > parentNode->value.first)
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
    
    RBNode< std::pair<K,V> >* rebalanceNode = node;
    while (!insertRebalance(rebalanceNode) && rebalanceNode) 
            rebalanceNode = (rebalanceNode->parent && 
                             rebalanceNode->parent->parent) ? 
                             rebalanceNode->parent->parent : NULL;
    
    return std::pair< RBNode< std::pair<K,V> >*, bool>(node, true);
}

template<typename K, typename V>
bool Map<K,V>::insertRebalance(RBNode< std::pair<K,V> >*& childNode)
{
    RBNode< std::pair<K,V> >* parentNode = 
                (childNode->parent) ? childNode->parent : NULL;

    RBNode< std::pair<K,V> >* grandParentNode = 
                (parentNode && parentNode->parent) ? parentNode->parent : NULL;

    RBNode< std::pair<K,V> >* uncleNode = 
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

template<typename K, typename V>
unsigned Map<K,V>::insertRebalanceCase(
                        RBNode< std::pair<K,V> >* grandParentNode,
                        RBNode< std::pair<K,V> >* parentNode,
                        RBNode< std::pair<K,V> >* uncleNode,
                        RBNode< std::pair<K,V> >* childNode) const
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


template<typename K, typename V>
void Map<K,V>::recolourNodes(
                    RBNode< std::pair<K,V> >*& grandParentNode,
                    RBNode< std::pair<K,V> >*& parentNode, 
                    RBNode< std::pair<K,V> >*& uncleNode)
{
    //set parent and uncle nodes black, grandparent red
    parentNode->red = uncleNode->red = false;
    if (grandParentNode != d_root) grandParentNode->red = true;
}

template<typename K, typename V>
void Map<K,V>::leftStraigthLine(
                    RBNode< std::pair<K,V> >*& grandParentNode,
                    RBNode< std::pair<K,V> >*& parentNode, 
                    RBNode< std::pair<K,V> >*& childNode)
{
    grandParentNode->left = childNode;

    RBNode< std::pair<K,V> >* grandChildNode = childNode->right;
    childNode->parent = grandParentNode;
    childNode->left = parentNode;
    childNode->right = NULL;
    
    parentNode->right = grandChildNode;
    parentNode->parent = childNode;
    
    //swap parent and child 
    RBNode< std::pair<K,V> >* swapNode;
    swapNode = parentNode;
    parentNode = childNode;
    childNode = swapNode;
}

template<typename K, typename V>
void Map<K,V>::rightStraigthLine(
                    RBNode< std::pair<K,V> >*& grandParentNode,
                    RBNode< std::pair<K,V> >*& parentNode, 
                    RBNode< std::pair<K,V> >*& childNode)
{
    grandParentNode->right = childNode;

    RBNode< std::pair<K,V> >* grandChildNode = childNode->left;
    childNode->parent = grandParentNode;
    childNode->right = parentNode;
    childNode->left = NULL;
    
    parentNode->left = grandChildNode;
    parentNode->parent = childNode;
    
    //swap parent and child 
    RBNode< std::pair<K,V> >* swapNode;
    swapNode = parentNode;
    parentNode = childNode;
    childNode = swapNode;
}

template<typename K, typename V>
void Map<K,V>::leftRotate(
                        RBNode< std::pair<K,V> >*& grandParentNode,
                        RBNode< std::pair<K,V> >*& parentNode)
{
    RBNode< std::pair<K,V> >* greatGrandParentNode = grandParentNode->parent;
    
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

template<typename K, typename V>
void Map<K,V>::rightRotate(
                        RBNode< std::pair<K,V> >*& grandParentNode, 
                        RBNode< std::pair<K,V> >*& parentNode)
{
    RBNode< std::pair<K,V> >* greatGrandParentNode = grandParentNode->parent;

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


template<typename K, typename V> 
V& Map<K,V>::at(K const& key)
{
    std::pair< RBNode< std::pair<K,V> >*, bool > found = find(key);
    if (!found.second)
        throw std::runtime_error("item does not exist in map");
    return found.first->value.second;
}

template<typename K, typename V>
V& Map<K,V>::operator[](K const& key)
{
    std::pair< RBNode< std::pair<K,V> >*, bool > found = find(key);
    if (!found.second)
        found = insert(std::pair<K,V>(key,
                       std::numeric_limits<V>::lowest()));
    return found.first->value.second;
}


template<typename K, typename V>
std::pair< RBNode< std::pair<K,V> >*, bool > Map<K,V>::find(K const& key)
{
    //if empty list, return null
    if (!d_root)
        return std::pair< RBNode< std::pair<K,V> >*, bool >(NULL, false);
    
    //binary search, return false if nothing found
    RBNode< std::pair<K,V> >* cur = d_root;
    while (cur)
    {
        if (key == cur->value.first)
            return std::pair< RBNode< std::pair<K,V> >*, bool >(cur, true);
        else if (key < cur->value.first)
            cur = (cur->left) ? cur->left: NULL;
        else
            cur = (cur->right) ? cur->right: NULL;
    }
    return std::pair< RBNode< std::pair<K,V> >*, bool >
            (cur, false);
}

template<typename K, typename V>
RBNode< std::pair<K,V> >* Map<K,V>::first()
{
    RBNode< std::pair<K,V> >* cur = d_root;
    while (cur->left) cur = cur->left;
    return cur;
}

template<typename K, typename V>
RBNode< std::pair<K,V> >* Map<K,V>::last()
{
    RBNode< std::pair<K,V> >* cur = d_root;
    while (cur->right) cur = cur->right;
    return cur;
}


template<typename K, typename V>
unsigned Map<K,V>::blackDepth(RBNode< std::pair<K,V> >* node)
{
//    //count the number of black nodes from the root to node
//    unsigned dep = 0;
//    SingleUnsortedList< RBNode< std::pair<K,V> >* > queue;
//    queue.append(d_root);
//    RBNode< std::pair<K,V> >* cur = queue.pop();
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
    
template<typename K, typename V>
unsigned Map<K,V>::blackHeigth()
{
//    //count the number of black nodes from the root to node
//    unsigned dep = 0;
//    SingleUnsortedList< RBNode< std::pair<K,V> >* > queue;
//    queue.append(d_root);
//    RBNode< std::pair<K,V> >* cur = queue.pop();
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

template<typename K, typename V>
unsigned Map<K,V>::maxDepth(RBNode< std::pair<K,V> >* node)
{
    typedef std::pair< RBNode< std::pair<K,V> >*, unsigned> PairLevel;
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


template<typename K, typename V>
void Map<K,V>::print()
{
    SingleUnsortedList< 
            std::pair<RBNode< std::pair<K,V> >* , 
            unsigned> > queue;
    std::pair<RBNode< std::pair<K,V> >* , unsigned> cur(d_root, 0);
    unsigned level = 0;
    while (queue.size() || cur.first)
    {
        if (level < cur.second)
        {
            std::cout << std::endl;
            ++level;
        }
        std::cout << cur.first->value.first << ":"
                  << cur.first->value.second
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
            queue.append(std::pair<RBNode< std::pair<K,V> >* , unsigned>
                            (cur.first->left, level+1));
        if (cur.first->right)
            queue.append(std::pair<RBNode< std::pair<K,V> >* , unsigned>
                            (cur.first->right, level+1));

        if (queue.size() > 0)
            cur = queue.pop();
        else
            cur = std::pair<RBNode< std::pair<K,V> >* , unsigned>(NULL, 0);
    }
    std::cout << std::endl;
}


} //my_data_structures

#endif

