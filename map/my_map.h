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

unsigned const map_max_depth_imbalance = 2;

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
            std::abs(depth(d_root->left) - depth(d_root->right)) < 2;
                        }
    
private:
    unsigned d_size;
    
    RBNode< std::pair<K,V> >* d_root;

    //todo: what to do with those measures ?
    //max number of levels from node, downwards
    unsigned depth(
                    RBNode< std::pair<K,V> >* node);
    //number of black nodes from root to node
    unsigned blackDepth(
                    RBNode< std::pair<K,V> >* node);
    //number of black nodes in the tree
    unsigned blackHeigth();
    
    //rebalancing function for insertion
    void insertRebalance(
                    RBNode< std::pair<K,V> >*& greatGrandParentNode,
                    RBNode< std::pair<K,V> >*& grandParentNode, 
                    RBNode< std::pair<K,V> >* parentNode, 
                    RBNode< std::pair<K,V> >* uncleNode, 
                    RBNode< std::pair<K,V> >* childNode);

    unsigned insertRebalanceCase(
                    RBNode< std::pair<K,V> >* grandParentNode,
                    RBNode< std::pair<K,V> >* parentNode, 
                    RBNode< std::pair<K,V> >* uncleNode, 
                    RBNode< std::pair<K,V> >* childNode) const;

    void recolourNodes(
                    RBNode< std::pair<K,V> >*& grandParentNode);

    void leftStraigthLine(
                    RBNode< std::pair<K,V> >*& grandParentNode);
    
    void rightStraigthLine(
                    RBNode< std::pair<K,V> >*& grandParentNode);
    
    void leftRotate(
                    RBNode< std::pair<K,V> >*& greatGrandParentNode, 
                    RBNode< std::pair<K,V> >*& grandParentNode);
   
    void rightRotate(
                    RBNode< std::pair<K,V> >*& greatGrandParentNode, 
                    RBNode< std::pair<K,V> >*& grandParentNode);
                     
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
        return std::pair< RBNode< std::pair<K,V> >*, bool>(NULL, false);
    }

    //second+ node: find the append point by comparing (ASC) existing nodes
    RBNode< std::pair<K,V> >* greatGrandParentNode = NULL;
    RBNode< std::pair<K,V> >* grandParentNode = NULL;
    RBNode< std::pair<K,V> >* parentNode = d_root;
    RBNode< std::pair<K,V> >* uncleNode = NULL;
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
    
    return std::pair< RBNode< std::pair<K,V> >*, bool>(NULL, false);
}

template<typename K, typename V>
void Map<K,V>::insertRebalance(
                    RBNode< std::pair<K,V> >*& greatGrandParentNode,
                    RBNode< std::pair<K,V> >*& grandParentNode,
                    RBNode< std::pair<K,V> >* parentNode,
                    RBNode< std::pair<K,V> >* uncleNode,
                    RBNode< std::pair<K,V> >* childNode)
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
                    RBNode< std::pair<K,V> >*& grandParentNode)
{
    //set parent and uncle nodes black, grandparent red
    if (grandParentNode->left) grandParentNode->left->red = false;
    if (grandParentNode->right) grandParentNode->right->red = false;
    if (grandParentNode != d_root) grandParentNode->red = true;
}

template<typename K, typename V>
void Map<K,V>::leftStraigthLine(
                    RBNode< std::pair<K,V> >*& grandParentNode)
{
    //make a straight line to the left
    RBNode< std::pair<K,V> >* parentNode = grandParentNode->left;
    RBNode< std::pair<K,V> >* childNode = grandParentNode->left->right;
    grandParentNode->left = childNode;
    childNode->left = parentNode;
    parentNode->right = NULL;
    
    //swap parent and child
    RBNode< std::pair<K,V> >* temp;
    temp = parentNode;
    parentNode = childNode;
    childNode = temp;
}

template<typename K, typename V>
void Map<K,V>::rightStraigthLine(
                    RBNode< std::pair<K,V> >*& grandParentNode)
{
    //make a straight line to the right
    RBNode< std::pair<K,V> >* parentNode = grandParentNode->right;
    RBNode< std::pair<K,V> >* childNode = grandParentNode->right->left;
    grandParentNode->right = childNode;
    childNode->right = parentNode;
    parentNode->left = NULL;
    
    //swap parent and child
    RBNode< std::pair<K,V> >* temp;
    temp = parentNode;
    parentNode = childNode;
    childNode = temp;
}


template<typename K, typename V>
void Map<K,V>::leftRotate(
                    RBNode< std::pair<K,V> >*& greatGrandParentNode, 
                    RBNode< std::pair<K,V> >*& grandParentNode)
{
    //rotation
    RBNode< std::pair<K,V> >* parentNode = grandParentNode->right;
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

template<typename K, typename V>
void Map<K,V>::rightRotate(
                    RBNode< std::pair<K,V> >*& greatGrandParentNode, 
                    RBNode< std::pair<K,V> >*& grandParentNode)
{
    //rotation
    RBNode< std::pair<K,V> >* parentNode = grandParentNode->left;
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


template<typename K, typename V> 
V& Map<K,V>::at(K const& key)
{
    std::pair< RBNode< std::pair<K,V> >*, bool > found = find(key);
    if (!found.second)
        throw std::runtime_error("item does not exist in map");
    return found.first->second;
}

template<typename K, typename V>
V& Map<K,V>::operator[](K const& key)
{
    std::pair< RBNode< std::pair<K,V> >*, bool > found = find(key);
    if (!found.second)
        found = insert(std::pair<K,V>(key,
                       std::numeric_limits<V>::lowest()));
    return found.first->second;
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
    //count the number of black nodes from the root to node
    unsigned dep = 0;
    SingleUnsortedList< RBNode< std::pair<K,V> >* > queue;
    queue.append(d_root);
    RBNode< std::pair<K,V> >* cur = queue.pop();
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
    
template<typename K, typename V>
unsigned Map<K,V>::blackHeigth()
{
    //count the number of black nodes from the root to node
    unsigned dep = 0;
    SingleUnsortedList< RBNode< std::pair<K,V> >* > queue;
    queue.append(d_root);
    RBNode< std::pair<K,V> >* cur = queue.pop();
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

template<typename K, typename V>
unsigned Map<K,V>::depth(RBNode< std::pair<K,V> >* node)
{
    typedef std::pair< RBNode< std::pair<K,V> >*, unsigned> PairLevel;
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

