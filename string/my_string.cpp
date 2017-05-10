#include "my_string.h"

namespace my_data_structures
{

String::String() 
    : d_size(0), d_array(NULL)
{
}


String::String(char const* c_str) 
    : d_size(0), d_array(NULL)
{
    char const* c = c_str;
    while(*c != STRING_END)
    {
        ++d_size;
        ++c;
    }
    d_array = new char[d_size+1];
    d_array[d_size] = STRING_END;
    for (unsigned i = 0; i < d_size; ++i)
        d_array[i] = c_str[i];
}

String::String(String const& copy) 
{
    *this = copy;
}

String::~String()
{
    delete[] d_array;
    d_size = 0;
}


bool String::operator==(String const& compared)
{
    if (d_size != compared.d_size)
        return false;
    for (unsigned i = 0; i < d_size; ++i)
        if (d_array[i] != compared.d_array[i])
            return false;
    return true;
}

bool String::operator!=(String const& compared)
{
    return !(*this == compared);
}

String& String::operator=(String const& assigned)
{
    if (this != &assigned)
    {
        delete[] d_array;
        d_size = assigned.d_size;

        d_array = new char[d_size+1];
        for (unsigned i =0; i < d_size; ++i)
            d_array[i] = assigned.d_array[i];
        d_array[d_size] = STRING_END;
    }
    return *this;
}

String& String::operator+(String const& assigned)
{
    if (assigned.d_size != 0)
        upSize(assigned.d_size, assigned.d_array);
    return *this;
}

String& String::operator+=(String const& compared)
{
    if (this != &compared)
    {
        char* newArray = new char[d_size + compared.d_size + 1];
        for (unsigned i = 0; i < d_size; ++i)
            newArray[i] = d_array[i];

        for (unsigned i = 0; i < compared.d_size; ++i)
            newArray[d_size+i] = compared.d_array[i];
        newArray[d_size + compared.d_size] = STRING_END;

        delete[] d_array;
        d_size += compared.d_size;
        d_array = newArray;
    }
    return *this;
}

String& String::operator+=(char const* c_str)
{
    unsigned int c_len = 0;
    char const* c = c_str;
    while(*c != STRING_END)
    {
        ++c_len;
        ++c;
    }
    if (c_len)
    {
        char* newArray = new char[d_size + c_len + 1];
        for (unsigned i = 0; i < d_size; ++i)
            newArray[i] = d_array[i];

        for (unsigned i = 0; i < c_len; ++i)
            newArray[d_size+i] = c_str[i];
        newArray[d_size + c_len] = STRING_END;

        delete[] d_array;
        d_size += c_len;
        d_array = newArray;
    }
    return *this;
}


char String::operator[](unsigned const k)
{
    if (k >= d_size)
        throw std::runtime_error("out of bounds");
    return d_array[k];
}

char String::operator[](unsigned const k) const
{
    if (k >= d_size)
        throw std::runtime_error("out of bounds");
    return d_array[k];
}

void String::upSize(unsigned int newSize, 
                    char const* c_strCopy)
{
    //copy items into a new array
    if (!newSize)
        newSize = (unsigned int) string_upsize_factor * d_size;
    else
        newSize += d_size;

    char* newArray = new char[newSize+1];
    for (unsigned i = 0; i < d_size; ++i)
        newArray[i] = d_array[i];
    
    if (c_strCopy)
        for (unsigned i = d_size; i < newSize; ++i)
            newArray[i] = c_strCopy[i];
    newArray[newSize] = STRING_END;
    
    //delete the old array and replace with the new one
    delete[] d_array;
    d_array= newArray;
    d_size = newSize;
}


bool operator==(char const* c_compared, String const& assigned)
{
    unsigned c_len = 0;
    char const* c = c_compared;
    while(*c != STRING_END)
    {
        ++c_len;
        ++c;
    }

    if (c_len != assigned.size())
        return false;
    for (unsigned i = 0; i < c_len; ++i)
        if (assigned[i] != c_compared[i])
            return false;
    return true;
}

bool operator!=(char const* c_compared, String const& assigned)
{
    return !(c_compared == assigned);
}


std::ostream& operator<<(std::ostream& os, String const& input)
{
    for (unsigned int i = 0; i < input.size(); ++i)
        os << input[i];
    return os;
}

} //my_data_structures
