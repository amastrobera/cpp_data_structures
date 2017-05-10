// string (dynamic array)
// not thread safe yet

#ifndef NULL
#define NULL 0
#endif

#ifndef STRING_END
#define STRING_END '\0'
#endif

#ifndef STRING_H
#define STRING_H

#include "my_iterator.h"
#include "my_vector.h"
#include <stdexcept>
#include <ostream>

namespace my_data_structures 
{

const double string_upsize_factor = 1.6;

class String
{
public:
    String();

    String(String const& copy);

    String(char const* c_str); 

    ~String();

    inline unsigned size() const { return d_size; } 

    inline bool empty() const { return !d_size;}

    String& operator=(String const& assigned);
   
    char operator[](unsigned const k);

    char operator[](unsigned const k) const;
    
    bool operator==(String const& compared);

    bool operator!=(String const& compared);

    String& operator+=(String const& compared);

    String& operator+=(char const* c_str);

    String& operator+=(char const c_str);

    static String join(Vector<String> const& vec, 
                        char delimiter = ',');

    Vector<String> split(char delimiter=' ',
                         char hardQuotes = '\"',
                         char softQuotes = '\'');

    // //iterators
    // class iterator;
    
    // iterator begin() const { return iterator(d_array); }

    // iterator end() const{ return iterator(d_array + d_size); }
    
private:
    unsigned d_size;

    char* d_array;
    
    void upSize(unsigned int newSize = 0, char const* c_strCopy = NULL);
};


bool operator==(char const* c_compared, String const& compared);

bool operator!=(char const* c_compared, String const& compared);

std::ostream& operator<<(std::ostream& os, String const& input);


// //iterators
// class String::iterator : public Iterator<char>
// {
// public:

//     iterator(char* val) : Iterator<char>(val) {}

// protected:
//     virtual void increment() { ++this->d_item; }
    
//     virtual void decrement() { --this->d_item; }
// };


    
} //my_data_structures

#endif
