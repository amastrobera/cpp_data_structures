// Hash Map
// not thread safe

#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include "my_vector.h"  //used for buckets array
#include "my_node.h"    //used for closed hashing list

#include <stdexcept>
#include <utility>

namespace my_data_structures 
{

unsigned const unordered_map_default_bucket_size = 31;

//todo: implement a generic iterator then use here
template<typename Key, typename Value>
struct UnorderedMapIterator
{
    SingleNode<std::pair<Key, Value>>* begin;
    SingleNode<std::pair<Key, Value>>* end;
};


template<typename Key, typename Value>
class UnorderedMap
{
public:
    UnorderedMap();

    ~UnorderedMap();

    inline unsigned size() { return d_size; }

    std::pair< std::pair<Key, Value>*, bool> insert(
                    std::pair<Key, Value> const& keyVal);

    
private:
    unsigned d_size;
    
    Vector< UnorderedMapIterator<Key, Value> > d_buckets;
    
    SingleNode<std::pair<Key, Value>>* d_values;
    
    void updateBucketPointers(unsigned hash, 
                              SingleNode<std::pair<Key, Value>> const* const);
    
    void insertNewValue(std::pair<Key, Value> const& keyVal);
    
    void deleteValues();
};


template<typename Key, typename Value> 
UnorderedMap<Key,Value>::UnorderedMap() 
: d_size(0), d_buckets(unordered_map_default_bucket_size), d_values(NULL)
{

}

template<typename Key, typename Value> 
UnorderedMap<Key,Value>::~UnorderedMap()
{
    deleteValues();
}

template<typename Key, typename Value> 
void UnorderedMap<Key,Value>::deleteValues()
{
    SingleNode<std::pair<Key, Value>>* cur = d_root;
    while (cur)
    {
        SingleNode<std::pair<Key, Value>>* temp = cur;
        cur = cur->next;
        delete temp;
        --d_size;
    }    
}
    

template<typename Key, typename Value> 
std::pair< std::pair<Key, Value>*, bool> UnorderedMap<Key,Value>::insert(
                std::pair<Key, Value> const& keyVal)
{
    //get hash to identify the right buckets
    unsigned hash = 1; //todo: hash-function
    
    //insert value 
    insertNewValue(keyVal); //todo: return true/false for the return value
    
//    updateBucketPointers(hash, &d_values.top());

    ++d_size;
    return std::pair< std::pair<Key, Value>*, bool>(
                d_buckets[hash].begin, true);
}


template<typename Key, typename Value> 
void UnorderedMap<Key,Value>::insertNewValue(
                        std::pair<Key, Value> const& keyVal)
{
    SingleNode<std::pair<Key, Value>>* node = 
                new SingleNode<std::pair<Key, Value>>(keyVal);
    node->next = d_values;
    d_values = node;
}


template<typename Key, typename Value> 
void UnorderedMap<Key,Value>::updateBucketPointers(unsigned hash, 
                          SingleNode<std::pair<Key, Value>> const* const)
{
////no sure it is needed
//    for (unsigned i = 0; i < unordered_map_default_bucket_size; ++i)
//    {
//        if (i != hash && 
//            d_buckets[i].begin && )
//    }
}



} //my_data_structures

#endif

