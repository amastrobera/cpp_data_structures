#include "my_string.h"

#include <cassert>
#include <iostream>
 
void testString()
{
    using my_data_structures::String;
    
    std::cout << "testString ... " << std::endl;

    //init
    std::cout << "    * constructor, empty(), operator==, copy constructor (char)" << std::endl;
    String test1;
    assert (0 == test1.size() && "    >>> failed");
    assert ("" == test1 && "    >>> failed");
    String test2("hello");
    assert (5 == test2.size() && "    >>> failed");
    
    //operator=
    std::cout << "    * opertor=, copy constructor (class)" << std::endl;
    String cppString = "ciao";
    assert ("ciao" == cppString && "    >>> failed");
    String test3(cppString);
    assert ("ciao" == test3 && "    >>> failed");

    //operator+
    std::cout << "    * opertor+" << std::endl;
    cppString += " bello";
    assert ("ciao bello" == cppString && "    >>> failed");
   
    //operator[]
    std::cout << "    * opeator[]" << std::endl;
    assert ('i' == cppString[1] && "    >>> failed[0]");
    assert ('o' == cppString[cppString.size()-1] && "    >>> failed[1]");

    // //iterator
    // std::cout << "    * iterator" << std::endl;
    // String<std::string>::iterator it = dyno.begin();
    // assert ("ciao" == *it && "    >>> failed");
    // ++it;
    // assert ("bello" == *it && "    >>> failed");
    // --it;
    // assert ("ciao" == *it && "    >>> failed");
    // ++it; ++it;
    // assert (dyno.end() == it && "    >>> failed");
    // unsigned i = 0;
    // for (it = dyno.begin(); it != dyno.end(); ++it)
    //     std::cout << "iter(" << ++i << "): " << *it << " >> ";
    // std::cout << std::endl;

    


    
    std::cout << "OK" << std::endl;
}


int main(int argc, char** argv)


{
    testString();
        
    return 0;
}

