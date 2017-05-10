#include "my_string.h"
#include "my_vector.h"

#include <cassert>
#include <iostream>
 
void testString()
{
    using my_data_structures::String;
    using my_data_structures::Vector;
    
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

    //operator+=
    std::cout << "    * operator+=" << std::endl;
    cppString += " bello";
    assert ("ciao bello" == cppString && "    >>> failed");

   
    //operator[]
    std::cout << "    * opeator[]" << std::endl;
    assert ('i' == cppString[1] && "    >>> failed[0]");
    assert ('o' == cppString[cppString.size()-1] && "    >>> failed[1]");

    //operator<<
    std::cout << "    * opeator<<" << std::endl;
    std::cout << "       " << cppString << "!" << std::endl;

    //split
    std::cout << "    * split (from vector)" << std::endl;

    std::cout << "      * split simple" << std::endl;
    Vector<String> vec = cppString.split();
    assert (2 == vec.size() && "    >>> failed size");
    assert (("ciao" == vec[0] && "bello" == vec[1]) &&  "    >>> failed value");

    std::cout << "      * split medium" << std::endl;
    String medium("10,\"ciao, bello\",40,\'ue, ue\',\"l\'unione europea, che storia\",35");
    Vector<String> vecMed = medium.split(',', '\"', '\'');
    assert (6 == vecMed.size() && "    >>> failed size");
    assert ("35" == vecMed[5] &&  "    >>> failed value");
    assert ("\"ciao, bello\"" == vecMed[1] && "    >>> failed value");
    assert ("\'ue, ue\'" == vecMed[3] &&  "    >>> failed value");
    assert ("\"l\'unione europea, che storia\"" == vecMed[4]  && "    >>> failed value");
             
    std::cout << "      * split hard" << std::endl;
    String hard("10,\"ciao, bello\",35,\'ciao, bello\',\"ecco fatto, non funziona niente");
    Vector<String> vecHard = hard.split(',');
    assert (5 == vecHard.size() && "    >>> failed size");
    assert ("\"ecco fatto, non funziona niente" == vecHard[4] &&  "    >>> failed value");




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

