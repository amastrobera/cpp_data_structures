#include "my_bit_array.h"

namespace my_data_structures
{

BitArray::BitArray(unsigned int size) 
    : d_size(size), d_array( ~(~(1 << size)) ) 
{
    //nothing
}

BitArray::BitArray(BitArray const& bitArray)
{
    *this = bitArray;
}

BitArray& BitArray::operator=(BitArray const& bitArray)
{
    if (this != &bitArray)
    {
        d_size = bitArray.d_size;
        d_array = bitArray.d_array;
    }
    return *this;
}

void BitArray::set(unsigned int const k, bool value)
{
    if (k < d_size)
    {
        if (value)
            d_array = d_array | (1 << k);
        else
            d_array = d_array & ~(1 << k);
    }
}
    
bool BitArray::get(unsigned int const k)
{
    if (k >= d_size)
        return false;
    return d_array & (1 << k);
}

std::string BitArray::print()
{
    std::string temp;
    for (int i = d_size-1; i >=0; --i)
    {
        temp += ( get(i) ? "1" : "0");
    }
    return temp;
}


} //my_data_structures
