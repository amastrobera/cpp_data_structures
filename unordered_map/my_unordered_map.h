// Hash Map
// based on a bucket of 31 cells (dynamic array) 
//          and a doubly linked list for store values (close hashing mode)
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
    DoubleNode<std::pair<Key, Value> >* begin;
    DoubleNode<std::pair<Key, Value> >* end;
};

template<typename Key = std::string >
struct Hash
{
    static unsigned get(Key const& key)
    {
        unsigned hash = 7;
        for (unsigned i = 0; i < key.size(); ++i)
            hash = hash * unordered_map_default_bucket_size + (unsigned)key[i];
        hash %= unordered_map_default_bucket_size;
        return hash;
    }
};


template<typename Key, typename Value, typename HashGen = Hash<Key> >
class UnorderedMap
{
public:
    UnorderedMap();

    ~UnorderedMap();

    inline unsigned size() { return d_size; }

    std::pair<std::pair<Key, Value>*, bool> find(Key const& key);

    std::pair< std::pair<Key, Value>*, bool> insert(
                    std::pair<Key, Value> const& keyVal);

    
private:
    unsigned d_size;
    
    //vector of buckets, starting from 31 buckets and ridimentionable
    Vector< UnorderedMapIterator<Key, Value> > d_buckets;

    //list of items, partially oredered ASC from a bucket's begin ptr to end
    DoubleNode<std::pair<Key, Value> >* d_values;


    unsigned hashFunction(Key const& key);
        
    DoubleNode<std::pair<Key,Value> >* insertNewValue(
                        std::pair<Key, Value> const& keyVal,
                        DoubleNode<std::pair<Key,Value> >*& root);

    void insertTopValue(std::pair<Key, Value> const& keyVal);
    
    void deleteValues();
};


template<typename Key, typename Value, typename HashGen>
UnorderedMap<Key,Value,HashGen>::UnorderedMap() 
: d_size(0), d_buckets(unordered_map_default_bucket_size), d_values(NULL)
{

}

template<typename Key, typename Value, typename HashGen>
UnorderedMap<Key,Value,HashGen>::~UnorderedMap()
{
    deleteValues();
}

template<typename Key, typename Value, typename HashGen>
void UnorderedMap<Key,Value,HashGen>::deleteValues()
{
    DoubleNode<std::pair<Key, Value> >* cur = d_values;
    while (cur)
    {
        DoubleNode<std::pair<Key, Value> >* temp = cur;
        cur = cur->right;
        delete temp;
        --d_size;
    }    
}


template<typename Key, typename Value, typename HashGen>
unsigned UnorderedMap<Key,Value,HashGen>::hashFunction(Key const& key)
{
    return HashGen::get(key);
}


//specialisation for known c++ types
//template<>
//struct Hash<std::string>
//{
//    static unsigned get(std::string const& key)
//    {
//        unsigned hash = 7;
//        for (unsigned i = 0; i < key.size(); ++i)
//            hash = hash * unordered_map_default_bucket_size + (unsigned)key[i];
//        hash %= unordered_map_default_bucket_size;
//        return hash;
//    }
//};

template<>
struct Hash<double>
{
    static unsigned get(double const& key)
    {
        unsigned hash = 7;
        double num = key;
        while (key > 0)
        {
            hash += (unsigned)num%10;
            num /= 10;
        }
        hash %= unordered_map_default_bucket_size;
        return hash;
    }
};


template<>
struct Hash<float>
{
    static unsigned get(float const& key)
    {
        unsigned hash = 7;
        float num = key;
        while (key > 0)
        {
            hash += (unsigned)num%10;
            num /= 10;
        }
        hash %= unordered_map_default_bucket_size;
        return hash;
    }
};

template<>
struct Hash<int>
{
    static unsigned get(int const& key)
    {
        unsigned hash = 7;
        int num = key;
        while (key > 0)
        {
            hash += (unsigned)num%10;
            num /= 10;
        }
        hash %= unordered_map_default_bucket_size;
        return hash;
    }
};

template<typename Key, typename Value, typename HashGen>
std::pair<std::pair<Key, Value>*, bool> UnorderedMap<Key,Value,HashGen>::find(
                Key const& key)
{
    //get bucket index
    unsigned hash = HashGen::get(key);
    
    //find the node in the list of a given bucket
    //return null / false if empty list
    if (d_size == 0 ||
        d_buckets[hash].begin == d_buckets[hash].end)
    {
        return std::pair<std::pair<Key, Value>*, bool> (NULL, false);
    }
    
    //loop through the list and find the item with the given key
    DoubleNode<std::pair<Key, Value> >* cur = d_buckets[hash].begin;
    while (cur != d_buckets[hash].end && 
           cur->value.first < key)
        cur = cur->right;
            
    if (cur != d_buckets[hash].end && 
        cur->value.first == key)
        return std::pair<std::pair<Key, Value>*, bool> (&cur->value, true);

    return std::pair<std::pair<Key, Value>*, bool> (NULL, false);
}


template<typename Key, typename Value, typename HashGen>
DoubleNode<std::pair<Key,Value> >* UnorderedMap<Key,Value,HashGen>::insertNewValue(
                      std::pair<Key, Value> const& keyVal,
                      DoubleNode<std::pair<Key,Value> >*& root)
{
    DoubleNode<std::pair<Key, Value> >* node = 
                new DoubleNode<std::pair<Key, Value> >(keyVal);
    DoubleNode<std::pair<Key, Value> >* ret;
    if (keyVal.first < root->value.first)
    {   //key preceeds the current item
        node->left = root->left;
        node->right = root;
        root->left = node;
        if (root == d_values)
        {
            d_values = node; //this is the first value in the list
            ret = d_values;
        }
        else
        {
            root = node;
            ret= root;
        }
    }
    else 
    {   //key follows the current item
        node->left = root;
        root->right = node->right;
        root->right = node;
        ret = node;
    }
    return ret;
}

template<typename Key, typename Value, typename HashGen>
void UnorderedMap<Key,Value,HashGen>::insertTopValue(
                      std::pair<Key, Value> const& keyVal)
{
    DoubleNode<std::pair<Key, Value> >* node = 
                new DoubleNode<std::pair<Key, Value> >(keyVal);
    if (d_values)
    {
        node->right = d_values;
        node->left = d_values->left;
        d_values->left = node;
    }
    d_values = node;
}


template<typename Key, typename Value, typename HashGen>
std::pair< std::pair<Key, Value>*, bool> UnorderedMap<Key,Value,HashGen>::insert(
                std::pair<Key, Value> const& keyVal)
{
    //get hash to identify the right buckets
    unsigned hash = HashGen::get(keyVal.first); 
    
    //insert value 
    //if the list is empty or the bucket is empty, insert the first item 
    if (d_size == 0 || 
        d_buckets[hash].begin == d_buckets[hash].end)
    {
        insertTopValue(keyVal);
        d_buckets[hash].begin = d_values;
        d_buckets[hash].end = d_values->right;
        ++d_size;
        return std::pair< std::pair<Key, Value>*, bool>(
                    &d_buckets[hash].begin->value, true);
    }
    
    //loop through the list and find the item with the given key
    DoubleNode<std::pair<Key, Value> >* cur = d_buckets[hash].begin;
    while (cur->right != d_buckets[hash].end && 
           cur->value.first < keyVal.first)
        cur = cur->right;

    //if the key doesn't exist yet, insert in ASC order
    if (cur->value.first != keyVal.first)
    {   //key preceeds current value
        DoubleNode<std::pair<Key,Value> >* ret = insertNewValue(keyVal, cur);
        ++d_size;
        return std::pair<std::pair<Key, Value>*, bool> (&ret->value, true);
    }
    
    //do not insert duplicates: if this key exists already do nothing            
    return std::pair<std::pair<Key, Value>*, bool> (NULL, false);
}



} //my_data_structures

#endif

