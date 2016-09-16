// vector (dynamic array)
// not thread safe yet

#ifndef NULL
#define NULL 0
#endif

#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>

namespace my_data_structures 
{

unsigned const dynamic_array_default_size = 100;
double const dynamic_array_upsize_factor = 1.6;

template<typename T>
class Vector
{
public:
    Vector(unsigned size=dynamic_array_default_size); 

    ~Vector();

    inline unsigned size() const { return d_num; }

    void append(T const& value);
    
    void push(T const& value);
    
    T& top();
    
    T& bottom();
    
    T& operator[](unsigned const k);
    
    T pop();
    
    void removeAt(unsigned const k); //deletes the item at index k
        
private:
    unsigned d_size;
    unsigned d_num;
    T* d_array;
    
    void upSize();
    void downSize();
};


template<typename T>
Vector<T>::Vector(unsigned size) : d_size(size), d_num(0) 
{
    d_array = new T[d_size];
}


template<typename T>
Vector<T>::~Vector()
{
    delete[] d_array;
    d_size = 0;
    d_num = 0;
}

template<typename T>
void Vector<T>::append(T const& value)
{
    if (d_num == d_size) upSize();
    d_array[d_num++] = value;
}


template<typename T>
void Vector<T>::push(T const& value)
{
    if (d_num == d_size) upSize();
    for (unsigned i = d_num; i > 0; --i)
    {
        d_array[i] = d_array[i-1];
    }
    d_array[0] = value;
    ++d_num;
}

template<typename T>
T& Vector<T>::top()
{
    if (d_num == 0) throw std::runtime_error("empty array, no top");
    return d_array[0];
}

template<typename T>
T& Vector<T>::bottom()
{
    if (d_num == 0) throw std::runtime_error("empty array, no bottom");
    return d_array[d_num-1];
}

template<typename T>
T& Vector<T>::operator[](unsigned const k)
{
    if (k >= d_size) throw std::runtime_error("not value for this index");
    return d_array[k];
}

template<typename T>    
T Vector<T>::pop()
{
    T tgt = d_array[0];
    for (unsigned i = 1; i < d_num; ++i)
    {
        d_array[i-1] = d_array[i];
    }
    --d_num;
    return tgt;
}

template<typename T>        
void Vector<T>::removeAt(unsigned const k)
{
    if (k >= d_num) throw std::runtime_error("not value for this index");
    if (k == d_num)
    {
        --d_num;
        return;
    }
    for (unsigned i = k+1; i < d_num; ++i) d_array[i-1] = d_array[i];
    --d_num;
}


template<typename T>
void Vector<T>::upSize()
{
    //copy items into a new array
    unsigned newSize = (unsigned int) dynamic_array_upsize_factor * d_size;
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
