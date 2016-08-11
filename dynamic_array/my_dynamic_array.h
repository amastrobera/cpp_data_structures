// dynamic array
// not thread safe yet

#ifndef NULL_H
#define NULL 0
#endif

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdexcept>

namespace my_data_structures 
{

const unsigned dynamic_array_default_size = 100;
const double dynamic_array_resize_factor = 1.6;

template<typename T>
class DynamicArray
{
public:
    DynamicArray(unsigned size=dynamic_array_default_size); 

    ~DynamicArray();

    inline unsigned size() { return d_num; }

    void append(T const& value);
    
    T& operator[](unsigned const k);
    
private:
    unsigned d_size;
    unsigned d_num;
    T* d_array;
    
    void resize();
};


template<typename T>
DynamicArray<T>::DynamicArray(unsigned size) : d_size(size), d_num(0) 
{
    d_array = new T[d_size];
}


template<typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] d_array;
    d_size = 0;
    d_num = 0;
}

template<typename T>
void DynamicArray<T>::append(T const& value)
{
    if (d_num == d_size) resize();
    d_array[d_num++] = value;
}


template<typename T>
T& DynamicArray<T>::operator[](unsigned const k)
{
    if (k >= d_size) throw std::runtime_error("out of range");
    if (k >= d_num) throw std::runtime_error("not value for this index");
    return d_array[k];
}

template<typename T>
void DynamicArray<T>::resize()
{
    //copy items into a new array
    unsigned newSize = (unsigned int) dynamic_array_resize_factor * d_size;
    T* newArray = new T[newSize];
    for (unsigned i = 0; i < d_size; ++i)
    {
        newArray[i] = d_array[i];
    }
    
    //delete the old array and replace with the new one
    delete[] d_array;
    d_array = newArray;
    d_size = newSize;
}


    
} //my_data_structures

#endif
