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


String& String::operator+=(String const& compared)
{
    if (this != &compared)
    {
        char* newArray = new char[d_size + compared.d_size];
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
        char* newArray = new char[d_size + c_len];
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

String& String::operator+=(char const c_str)
{
    unsigned int c_len = 1;
    char* newArray = new char[d_size + c_len];

    for (unsigned i = 0; i < d_size; ++i)
        newArray[i] = d_array[i];


    newArray[d_size] = c_str;
    newArray[d_size + c_len] = STRING_END;

    delete[] d_array;
    d_size += c_len;
    d_array = newArray;

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


Vector<String> String::split(char delimiter, 
                             char hardQuotes,
                             char softQuotes)
{
    Vector<String> temp;
    
    bool openHardQuotes = false;
    bool openSoftQuotes = false;

    unsigned int i = 0;
    String item;
    int missing = d_size;

    while (i < d_size)
    {
        if (d_array[i] == softQuotes )
        {
            openSoftQuotes = !openSoftQuotes;
        }
        else if (d_array[i] == hardQuotes)
        {
            openHardQuotes = !openHardQuotes;
            openSoftQuotes = false;
        }
        
        if (d_array[i] == delimiter && !openHardQuotes && !openSoftQuotes)
        {
            temp.append(item);
            missing -= item.d_size;
            item = "";
        }
        else
        {
            item += d_array[i];
        }
        ++i;
    }

    if (missing && item.d_size)
        temp.append(item); //flush the rest, if any

    return temp;
}

String String::join(Vector<String> const& vec, char delimiter)
{
    String temp;
    unsigned int n = vec.size();
    for (unsigned int i = 0; i < n; ++i)
    {
        temp += vec[i];
        if (i != n-1)
            temp += delimiter;
    }
    return temp;
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
