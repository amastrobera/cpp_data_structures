// bit array
// not thread safe yet

#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

#include <stdexcept>
#include <string>

namespace my_data_structures 
{

unsigned int const bit_array_default_size = 10; //max size 2^32 (or 64) depending on the architecture 

class BitArray
{
public:
    BitArray(unsigned int size=bit_array_default_size); 

    ~BitArray() {}

    inline unsigned int size() const { return d_size; }

    void set(unsigned int const k, bool value);
    
    bool get(unsigned int const k);

    std::string print();
    
private:
    unsigned int d_size;

    unsigned int d_array;
};

    
} //my_data_structures

#endif
